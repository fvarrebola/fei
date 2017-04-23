package org.ads.nlp.wordnet;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;
import java.util.zip.GZIPInputStream;

import javax.validation.constraints.NotNull;

import org.ads.Constants;
import org.ads.nlp.NlpParser;
import org.ads.nlp.ex.NlpException;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.Parameters;
import org.apache.commons.compress.archivers.ArchiveEntry;
import org.apache.commons.compress.archivers.tar.TarArchiveInputStream;
import org.apache.commons.compress.utils.IOUtils;
import org.apache.commons.io.FileUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import net.didion.jwnl.JWNL;
import net.didion.jwnl.JWNLException;
import net.didion.jwnl.data.IndexWord;
import net.didion.jwnl.data.POS;
import net.didion.jwnl.data.Synset;
import net.didion.jwnl.data.Word;
import net.didion.jwnl.dictionary.Dictionary;
import net.didion.jwnl.dictionary.MorphologicalProcessor;

public class JwnlWordNetHelper {

  private static final String CONFIG_FILE = "config/wordnet/jwnl-config.xml";
  private static final int DEFAULT_LIMIT = 2;

  private Dictionary dictionary;

  private static JwnlWordNetHelper instance;

  private static final Logger LOGGER = LogManager.getLogger(JwnlWordNetHelper.class);

  /**
   * Constructor.<br />
   */
  private JwnlWordNetHelper() {
    super();
  }

  /**
   * Gets the instance of this class.<br />
   * 
   * @return instance of {@link JwnlWordNetHelper}
   * 
   * @throws NlpException
   *           in case initialization fails
   */
  public static JwnlWordNetHelper getInstance() throws NlpException {
    synchronized (NlpParser.class) {
      if (instance == null) {
        instance = new JwnlWordNetHelper();
        instance.initialize();
      }
    }
    return instance;
  }

  private static void extractTarGz(Path from, Path to) throws IOException {

    if (!from.toFile().isFile() || !to.toFile().isDirectory()) {
      throw new IllegalArgumentException();
    }

    final String filename = from.getFileName().toString();
    if (!filename.endsWith(".tar.gz")) {
      throw new IllegalArgumentException();
    }

    final Path tarFile = to.resolve(filename.substring(0, filename.length() - 3));
    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Gunzip {} to {}...", from, to);
    }
    try (InputStream gzInputStream = new GZIPInputStream(new FileInputStream(from.toFile()));
        OutputStream gzOutputStream = new FileOutputStream(tarFile.toFile())) {
      IOUtils.copy(gzInputStream, gzOutputStream);
    }

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Untar {}...", tarFile);
    }
    try (TarArchiveInputStream tarInputStream = new TarArchiveInputStream(new FileInputStream(tarFile.toFile()))) {
      ArchiveEntry entry = null;
      while ((entry = tarInputStream.getNextEntry()) != null) {
        Path entryPath = to.resolve(entry.getName());
        if (entry.isDirectory()) {
          Files.createDirectory(entryPath);
        } else {
          try (OutputStream os = new FileOutputStream(entryPath.toFile())) {
            IOUtils.copy(tarInputStream, os);
          }
        }
      }
    }

  }

  private static void assertWordnetFiles() {

    final String URL = "http://wordnetcode.princeton.edu/wn3.1.dict.tar.gz";
    final String PATH = "/tmp/wordnet";
    final String FILENAME = "wn3.1.dict.tar.gz";

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Checking WordNet files at directory {}...", PATH);
    }

    Path basePath = Paths.get(PATH);
    if (!Files.exists(basePath)) {
      try {
        Files.createDirectories(basePath);
      } catch (IOException ex) {
        throw new RuntimeException(ex);
      }
    }

    final Path controlFilePath = basePath.resolve(".got-wordnet-files");
    if (Files.exists(controlFilePath)) {
      return;
    }

    try {

      Path file = basePath.resolve(FILENAME);

      if (LOGGER.isInfoEnabled()) {
        LOGGER.info("Extracting file {} to {}", file, basePath);
      }
      
      FileUtils.copyURLToFile(new URL(URL), file.toFile());
      extractTarGz(file, basePath);
      Files.createFile(controlFilePath);

    } catch (Exception ex) {
      LOGGER.error("Failed to download and extract WordNet dictionary.", ex);
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("WordNet files seem ok.");
    }

  }

  /**
   * Initializes the helper by installing WordNet 3.1 dictionary.<br />
   * 
   * @throws NlpException
   *           in case initialization fails
   */
  private void initialize() throws NlpException {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Initializing JWNL WordNet helper using configuration file {}...", CONFIG_FILE);
    }

    final InputStream inputStream = JwnlWordNetHelper.class.getClassLoader().getResourceAsStream(CONFIG_FILE);
    if (CustomObjectUtils.isNull(inputStream)) {
      throw new NlpException("Failed to read configuration file '" + CONFIG_FILE + "'");
    }

    assertWordnetFiles();

    try {
      JWNL.initialize(inputStream);
    } catch (JWNLException exception) {
      throw new NlpException(exception);
    }

    this.dictionary = Dictionary.getInstance();

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("JWNL WordNet helper successfully initialized.");
    }

  }

  /**
   * Gets the lemmas for a given word derivation and its POS
   * (<i>part-of-speech</i>) tag.<br />
   * 
   * @param derivation
   *          the {@link String} that represents the word derivation
   * @param pos
   *          the {@link POS} for the given lemma
   * @param limit
   *          the limit of synonyms to retrieve
   * 
   * @return the {@link Set} of {@link String} that represent the lemma set for
   *         the given derivation
   */
  @NotNull
  public Set<String> getLemmas(String derivation, POS pos, int limit) {

    Parameters.requireNonNull(derivation);

    Set<String> lemmaSet = new TreeSet<String>();

    if (CustomObjectUtils.isNull(pos)) {
      return lemmaSet;
    }

    if (limit < 1) {
      limit = DEFAULT_LIMIT;
    }

    final MorphologicalProcessor processor = this.dictionary.getMorphologicalProcessor();

    try {

      @SuppressWarnings("unchecked")
      final List<String> baseForms = processor.lookupAllBaseForms(pos, derivation);
      if (CustomObjectUtils.isNull(baseForms)) {
        return lemmaSet;
      }

      int added = 0;
      final int count = baseForms.size();
      for (int idx = 0; (idx < count) && (added < limit); idx++) {
        lemmaSet.add(baseForms.get(idx));
        added++;
      }

    } catch (JWNLException exception) {
      LOGGER.error("Failed to get lemmas.", exception);
    }

    return lemmaSet;

  }

  /**
   * Gets the lemmas for a given word derivation and its POS
   * (<i>part-of-speech</i>) tag.<br />
   * 
   * @param derivation
   *          the {@link String} that represents the word derivation
   * @param pos
   *          the {@link POS} for the given lemma
   * 
   * @return the {@link Set} of {@link String} that represent the lemma set for
   *         the given derivation
   */
  @NotNull
  public Set<String> getLemmas(String derivation, POS pos) {
    return getLemmas(derivation, pos, Constants.DEFAULT_LIMIT);
  }

  /**
   * Gets the lemmas for a given word derivation and its POS
   * (<i>part-of-speech</i>) tag.<br />
   * 
   * @param derivation
   *          the {@link String} that represents the word derivation
   * @param pos
   *          the {@link POS} for the given lemma
   * 
   * @return the {@link Set} of {@link String} that represent the lemma set for
   *         the given derivation
   */
  @NotNull
  public String getLemma(String derivation, POS pos) {

    final Set<String> lemmaSet = getLemmas(derivation, pos, Constants.DEFAULT_LIMIT);
    if (lemmaSet.isEmpty()) {
      return derivation;
    }

    return lemmaSet.stream().findFirst().get();

  }

  /**
   * Gets the synonyms for a given lemma and its POS (<i>part-of-speech</i>)
   * tag.<br />
   * 
   * @param lemma
   *          the {@link String} that represents the lemma
   * @param pos
   *          the {@link POS} for the given lemma
   * @param limit
   *          the limit of synonyms to retrieve
   * 
   * @return the {@link Set} of {@link String} that represent the synonyms set
   *         for the given lemma
   */
  @NotNull
  public Set<String> getSynonyms(String lemma, POS pos, int limit) {

    Parameters.requireNonNull(lemma, pos);

    Set<String> synSet = new TreeSet<String>();

    if (limit < 1) {
      limit = DEFAULT_LIMIT;
    }

    try {

      final IndexWord indexWord = this.dictionary.lookupIndexWord(pos, lemma);
      if (CustomObjectUtils.isNull(indexWord)) {
        return synSet;
      }

      // getSense(?) - index starts at 1!
      int added = 0;
      final int count = indexWord.getSenseCount();
      for (int idx = 1; (idx < count + 1) && (added < limit); idx++) {
        final Synset sense = indexWord.getSense(idx);
        final Word[] words = sense.getWords();
        if (CustomObjectUtils.isNull(words)) {
          continue;
        }
        for (Word w : sense.getWords()) {
          synSet.add(w.getLemma());
        }
        added++;
      }

    } catch (JWNLException exception) {
      LOGGER.error("Failed to get synonyms.", exception);
    }

    return synSet;

  }

  /**
   * Gets the synonyms for a given lemma and its POS (<i>part-of-speech</i>)
   * tag.<br />
   * 
   * @param lemma
   *          the {@link String} that represents the lemma
   * @param pos
   *          the {@link POS} for the given lemma
   * 
   * @return the {@link Set} of {@link String} that represent the synonyms for
   *         the given lemma
   */
  @NotNull
  public Set<String> getSynonyms(String lemma, POS pos) {
    return getSynonyms(lemma, pos, DEFAULT_LIMIT);
  }

}
