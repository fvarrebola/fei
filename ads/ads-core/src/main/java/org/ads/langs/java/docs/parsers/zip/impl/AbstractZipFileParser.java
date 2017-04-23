package org.ads.langs.java.docs.parsers.zip.impl;

import org.ads.langs.java.Version;
import org.ads.langs.java.docs.JavadocVersionClassifier;
import org.ads.langs.java.docs.parsers.html.HtmlFileParser;
import org.ads.langs.java.docs.parsers.html.HtmlFileParserFactory;
import org.ads.langs.java.docs.parsers.zip.ZipFileParser;
import org.ads.langs.java.maven.LuceneQueryBuilder;
import org.ads.langs.java.maven.MavenArtifactResolver;
import org.ads.langs.java.maven.MavenSearchManager;
import org.ads.langs.java.maven.MvnClassifiers;
import org.ads.langs.java.maven.SearchClause;
import org.ads.langs.java.maven.ex.MavenException;
import org.ads.langs.java.model.JavaLibrary;
import org.ads.langs.java.model.JavaMethod;
import org.ads.langs.java.model.JavaObject;
import org.ads.utils.CustomFilenameUtils;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;
import org.apache.commons.io.FilenameUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.maven.index.ArtifactInfo;
import org.apache.maven.index.MAVEN;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.function.Consumer;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

/**
 * Abstract ZIP file parser.<br />
 * 
 * @author arrebola
 *
 */
public abstract class AbstractZipFileParser implements ZipFileParser {

  private boolean searchNonStdLocations;
  protected String root;

  private static final Logger LOGGER = LogManager.getLogger(AbstractZipFileParser.class);

  /**
   * Constructor.<br />
   */
  public AbstractZipFileParser() {
    super();
  }

  /**
   * Constructor.<br />
   * 
   * @param root
   *          the {@link String} that represents the starting path to be considered while parsing
   *          the ZIP file
   */
  public AbstractZipFileParser(String root) {
    this();

    Parameters.requireNonEmpty(root);

    this.root = root;
  }

  /**
   * Constructor.<br />
   * 
   * @param root
   *          the {@link String} that represents the starting path to be considered while parsing
   *          the ZIP file
   * @param searchNonStdLocations
   *          indicates whether to search for non-standard locations of the
   *          {@link ZipFileParser#ALL_CLASSES_FRAME_FILE} file
   */
  public AbstractZipFileParser(String root, boolean searchNonStdLocations) {
    this(root);
    this.searchNonStdLocations = searchNonStdLocations;
  }

  /**
   * Searches a {@link ZipFile} for the {@link ZipEntry} that corresponds to the
   * {@link HtmlFileParser#ALL_CLASSES_FRAME_FILE} file.<br />
   * 
   * @param zipFile
   *          the {@link ZipFile} to search
   * 
   * @return the {@link ZipFile} that corresponds to the
   *         {@link HtmlFileParser#ALL_CLASSES_FRAME_FILE} file or <code>null</code> if such entry
   *         cannot be found
   */
  private static ZipEntry searchNonStandardLocations(ZipFile zipFile) {

    ZipEntry treeFile = null;

    boolean found = false;
    Enumeration<? extends ZipEntry> entries = zipFile.entries();
    while (entries.hasMoreElements() && !found) {

      ZipEntry entry = entries.nextElement();
      if (entry.isDirectory()) {
        continue;
      }

      final String entryName = entry.getName();
      if (CustomStringUtils.endsWith(entryName, ALL_CLASSES_FRAME_FILE)) {
        treeFile = entry;
        found = true;
      }
    }

    return treeFile;

  }

  @Override
  public List<JavaObject> parseFile(ZipFile zipFile) {

    Parameters.requireNonNull(zipFile);

    List<JavaObject> objects = new ArrayList<JavaObject>();

    final String allClassesFrameFile = (CustomStringUtils.isEmpty(this.root)
        ? ALL_CLASSES_FRAME_FILE : (this.root + "/" + ALL_CLASSES_FRAME_FILE));

    ZipEntry zipEntry = zipFile.getEntry(allClassesFrameFile);
    if (CustomObjectUtils.isNull(zipEntry) && this.searchNonStdLocations) {
      zipEntry = searchNonStandardLocations(zipFile);
    }

    if (CustomObjectUtils.isNull(zipEntry)) {
      LOGGER.error("Could not find file {}.", allClassesFrameFile);
      return objects;
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Parsing file {}...", FilenameUtils.getName(zipFile.getName()));
    }

    final String entryName = zipEntry.getName();
    try (InputStream is = zipFile.getInputStream(zipEntry)) {

      final Document document = Jsoup.parse(is, CustomStringUtils.UTF_8, entryName);

      final Version version = JavadocVersionClassifier.getMostLikely(document, zipFile);
      if (LOGGER.isInfoEnabled()) {
        LOGGER.info("Javadoc most likely version is {}.", version);
      }

      final HtmlFileParser parser = HtmlFileParserFactory.getInstance(version);

      final List<String> candidateClasses = parser.parseClassListFromAllClassesFrameFile(document);
      for (String candidate : candidateClasses) {

        final String candidatePath = (CustomStringUtils.isEmpty(this.root) ? candidate
            : (this.root + "/" + candidate));

        final ZipEntry candidateEntry = zipFile.getEntry(candidatePath);
        if (CustomObjectUtils.isNull(candidateEntry)) {
          LOGGER.warn("Could not find zip entry for class {}.", candidateEntry);
          continue;
        }

        final String zipEntryDn = CustomFilenameUtils.getZipEntryDn(zipFile, candidateEntry);

        try (InputStream candidateInputStream = zipFile.getInputStream(candidateEntry)) {

          if (LOGGER.isDebugEnabled()) {
            LOGGER.debug("Parsing ZIP entry {}...", zipEntryDn);
          }

          final Document candidateDocument = Jsoup.parse(candidateInputStream,
              CustomStringUtils.UTF_8, candidatePath);
          objects.add(parser.parseObjectFile(candidateDocument));

          if (LOGGER.isDebugEnabled()) {
            LOGGER.debug("ZIP entry {} sucessfully parsed.", zipEntryDn);
          }

        } catch (Exception exception) {
          LOGGER.warn("Skipping {} ({})...", candidateEntry, exception.getMessage());
        }

      }

      if (LOGGER.isInfoEnabled()) {
        LOGGER.info("File {} was successfully parsed.", zipFile.getName());
      }

    } catch (IOException exception) {
      LOGGER.error("Failed to parse file.", exception);
    }

    return objects;

  }

  @Override
  public List<JavaObject> parseFile(File file) {

    Parameters.requireNonNull(file);

    List<JavaObject> objects = new ArrayList<JavaObject>();

    try (ZipFile zipFile = new ZipFile(file)) {
      objects = parseFile(zipFile);
    } catch (Exception exception) {
      LOGGER.error("Failed to parse file.", exception);
    }

    return objects;

  }

  /**
   * Parses all the Java objects (as in {@link JavaObject} class) found in a given file.<br />
   * 
   * @param file
   *          the {@link File}
   * 
   * @return the {@link List} of {@link JavaObject} found in the given file
   */
  private List<JavaObject> parseAllJavaObjectsFromFile(File file) {

    Parameters.requireNonNull(file);

    List<JavaObject> objects = new ArrayList<JavaObject>();

    try {
      objects = parseFile(new ZipFile(file));
    } catch (Exception exception) {
      LOGGER.error("Failed to parse file.", exception);
    }

    return objects;

  }

  /**
   * Parses all the Java methods (as in {@link JavaMethod} class) found in a given file.<br />
   * 
   * @param file
   *          the {@link File}
   * 
   * @return the {@link List} of {@link JavaMethod} found in the given file
   */
  // TODO: remove
  @SuppressWarnings("unused")
  private List<JavaMethod> parseAllJavaMethodsFromFile(File file) {

    Parameters.requireNonNull(file);

    List<JavaMethod> methods = new ArrayList<JavaMethod>();

    try {
      parseAllJavaObjectsFromFile(file).forEach(new Consumer<JavaObject>() {
        @Override
        public void accept(JavaObject object) {
          methods.addAll(object.getMethods());
        }
      });
    } catch (Exception exception) {
      LOGGER.error("Failed to parse file.", exception);
    }

    return methods;

  }

  /**
   * Searches for the Java objects defined in the given Java artifact.<br />
   * 
   * @param groupId
   *          the @link{String} that represents the artifact group id
   * @param artifactId
   *          the @link{String} that represents the artifact id
   * @param version
   *          the @link{String} that represents the artifact version
   * @param exact
   *          indicates if the search should be exact
   * 
   * @return the {@link List} of {@link JavaObject} that represents the Java objects
   */
  public List<JavaObject> search(String groupId, String artifactId, String version, boolean exact,
      int limit, int page, int pageSize) throws MavenException {

    MavenSearchManager search = MavenSearchManager.getInstance();

    LuceneQueryBuilder builder = search.getQueryBuilder();

    if (CustomStringUtils.isNotEmpty(groupId)) {
      builder.add(new SearchClause.MustOccur(MAVEN.GROUP_ID, groupId, exact));
    }

    if (CustomStringUtils.isNotEmpty(artifactId)) {
      builder.add(new SearchClause.MustOccur(MAVEN.ARTIFACT_ID, artifactId, exact));
    }

    if (CustomStringUtils.isNotEmpty(version)) {
      builder.add(new SearchClause.MustOccur(MAVEN.VERSION, version, exact));
    }

    List<JavaObject> objects = new ArrayList<JavaObject>();
    MavenArtifactResolver resolver = MavenArtifactResolver.getInstance();
    Consumer<ArtifactInfo> consumer = new Consumer<ArtifactInfo>() {
      @Override
      public void accept(ArtifactInfo artifactInfo) {
        if (MvnClassifiers.JAVADOC.classifier().equals(artifactInfo.getClassifier())) {
          try {
            objects.addAll(parseFile(resolver.getFile(artifactInfo)));
          } catch (Exception exception) {
            LOGGER.error("Failed to parse Java objects from artifact.", exception);
          }
        }
      }
    };

    search.searchIterator(builder.getQuery(), consumer, limit, page, pageSize);

    return objects;

  }

  /**
   * Searches for the Java objects defined in the given Java library.<br />
   * 
   * @param library
   *          the @link{JavaLibrary} to be searched
   * 
   * @return the {@link List} of {@link JavaObject} that represents the Java objects
   */
  public List<JavaObject> search(JavaLibrary library) {

    Parameters.requireNonNull(library);

    List<JavaObject> objects = new ArrayList<JavaObject>();

    try {

      MavenSearchManager search = MavenSearchManager.getInstance();

      LuceneQueryBuilder builder = search.getQueryBuilder();
      builder.add(new SearchClause.MustOccur(MAVEN.GROUP_ID, library.getGroupId()));
      builder.add(new SearchClause.MustOccur(MAVEN.ARTIFACT_ID, library.getArtifactId()));
      builder.add(new SearchClause.MustOccur(MAVEN.VERSION, library.getVersion()));

      MavenArtifactResolver resolver = MavenArtifactResolver.getInstance();
      Consumer<ArtifactInfo> consumer = new Consumer<ArtifactInfo>() {
        @Override
        public void accept(ArtifactInfo artifactInfo) {
          if (MvnClassifiers.JAVADOC.classifier().equals(artifactInfo.getClassifier())) {
            try {
              objects.addAll(parseFile(resolver.getFile(artifactInfo)));
            } catch (Exception exception) {
              LOGGER.error("Failed to parse Java objects from artifact.", exception);
            }
          }
        }
      };

      search.searchIterator(builder.getQuery(), consumer);

    } catch (MavenException exception) {
      LOGGER.error("Failed to parse Java objects from library.", exception);
    }

    return objects;

  }

}
