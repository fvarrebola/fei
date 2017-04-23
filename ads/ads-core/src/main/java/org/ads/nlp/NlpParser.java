package org.ads.nlp;

import java.net.URL;
import java.util.stream.IntStream;

import org.ads.nlp.ex.NlpException;
import org.ads.nlp.wordnet.JwnlWordNetHelper;
import org.ads.utils.ConverterUtils;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;
import org.apache.commons.lang3.ArrayUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import net.didion.jwnl.data.POS;
import opennlp.tools.postag.POSModel;
import opennlp.tools.postag.POSTagger;
import opennlp.tools.postag.POSTaggerME;
import opennlp.tools.tokenize.WhitespaceTokenizer;

/**
 * This class concentrates all NLP techniques that can be applied to the end
 * user input.<br />
 * So far, there's support to POS tagging and stemming through OpenNLP
 * library.<br />
 * There's also support to synonym search through JWNL WordNet library.<br />
 * 
 * @author arrebola
 *
 */
public class NlpParser {

  private static final String REPLACEMENT_REGEXP = "[()]";
  private static final String UNSAFE_CHARS_REGEXP = "[^\\w^\\d^\\s^\\.]";
  private static final String MAXENT_MODEL = "config/opennlp/models/en-pos-maxent.bin";

  private POSTagger tagger;
  // private Stemmer stemmer;

  private JwnlWordNetHelper wordnet;

  private static NlpParser instance;

  private static final Logger LOGGER = LogManager.getLogger(NlpParser.class);

  /**
   * Constructor.<br />
   */
  private NlpParser() {
    super();
  }

  /**
   * Gets the instance of this class.<br />
   * 
   * @return instance of {@link NlpParser}
   * 
   * @throws NlpException
   *           in case initialization fails
   */
  public static NlpParser getInstance() throws NlpException {
    synchronized (NlpParser.class) {
      if (instance == null) {
        instance = new NlpParser();
        instance.initialize();
      }
    }
    return instance;
  }

  /**
   * Initializes the tagger by loading the opennlp models.<br />
   * 
   * @throws NlpException
   *           in case initialization fails
   */
  private void initialize() throws NlpException {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Initializing user input POS tagger using model {}...", MAXENT_MODEL);
    }

    final URL modelUrl = NlpParser.class.getClassLoader().getResource(MAXENT_MODEL);
    if (CustomObjectUtils.isNull(modelUrl)) {
      throw new NlpException("Failed to read model '" + MAXENT_MODEL + "'");
    }

    try {
      POSModel model = new POSModel(modelUrl);
      this.tagger = new POSTaggerME(model);
    } catch (Exception exception) {
      LOGGER.error("Failed to initialize the user input pos tagger.", exception);
    }

    // this.stemmer = new PorterStemmer();

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("POS tagger successfully initialized.");
    }

    this.wordnet = JwnlWordNetHelper.getInstance();

  }

  /**
   * Parses the user input.<br />
   * We use the maximum entropy tagging offered by {@link POSTaggerME}
   * implementation. But before the actual tagging, the input text is tokenized
   * using the {@link WhitespaceTokenizer}. Optionally, the input text can also
   * be stemmed and lemmatized.<br />
   * 
   * @param input
   *          the {@link String} that represents the user input
   * @param options
   *          the {@link NlpParserOptions} that represents the parsing options
   * 
   * @return the {@link UserInput} that represents the parsed user input
   */
  public UserInput parse(String input, NlpParserOptions options) {

    Parameters.requireNonNull(input, options);

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Parsing user input \"{}\" using options = {}.", input, options);
    }

    UserInput userInput = new UserInput();
    userInput.setPrimaryInput(input);

    String safeInput = input;
    if (options.isRemoveUnsafeChars()) {
      safeInput = CustomStringUtils.removePattern(
          CustomStringUtils.replacePattern(input, REPLACEMENT_REGEXP, CustomStringUtils.SPACE), UNSAFE_CHARS_REGEXP);
    }

    // tokenize the input string and remove unnecessary white spaces
    final String[] tokenized = WhitespaceTokenizer.INSTANCE.tokenize(safeInput);
    userInput.setTokenized(CustomStringUtils.joinUsingSpace(tokenized));

    String[] sentence = tokenized;
    int length = sentence.length;

    // POS tagging
    final String[] tags = this.tagger.tag(sentence);
    userInput.setTags(CustomStringUtils.joinUsingSpace(tags));

    final PennTreebankPosTags[] posTags = new PennTreebankPosTags[length];
    final POS[] jwnlPosTags = new POS[length];
    IntStream.range(0, length).forEach(idx -> {
      if (!CustomStringUtils.DOT.equals(tags[idx])) {
        posTags[idx] = PennTreebankPosTags.valueOf(tags[idx]);
        jwnlPosTags[idx] = ConverterUtils.toJwnlPos(posTags[idx]);
      }
    });

    // lemma
    if (options.isLemma()) {
      final String[] lemmatized = new String[length];
      IntStream.range(0, length).forEach(idx -> {
        lemmatized[idx] = this.wordnet.getLemma(tokenized[idx], jwnlPosTags[idx]);
      });
      userInput.setLemmatized(CustomStringUtils.joinUsingSpace(lemmatized));
      userInput.addSyn(userInput.getLemmatized());
      sentence = lemmatized;
    }

    // use only the first verb and noun
    final String[] firstVerbAndNoun = new String[2];
    boolean foundVerb = false;
    boolean foundNoun = false;
    for (int idx = 0; idx < length && !(foundVerb && foundNoun); idx++) {
      if (PennTreebankPosTags.isVerb(posTags[idx]) && !foundVerb) {
        firstVerbAndNoun[0] = sentence[idx];
        foundVerb = true;
      } else if (PennTreebankPosTags.isNoun(posTags[idx]) && foundVerb && !foundNoun) {
        firstVerbAndNoun[1] = sentence[idx];
        foundNoun = true;
      }
    }

    if (options.isUse1stVbNn()) {
      if (foundVerb && foundNoun) {
        sentence = firstVerbAndNoun;
      } else {
        sentence = ArrayUtils.EMPTY_STRING_ARRAY;
      }
      length = sentence.length;
    }

    if (length > 0) {
      userInput.addSyn(CustomStringUtils.joinUsingSpace(sentence));
      if (options.isUseSynsets()) {
        for (int idx = 0; idx < length; idx++) {
          if (options.isUseVbSynsOnly() && !PennTreebankPosTags.isVerb(posTags[idx])) {
            continue;
          }
          for (String syn : this.wordnet.getSynonyms(sentence[idx], jwnlPosTags[idx])) {
            String[] synInput = sentence.clone();
            synInput[idx] = syn;
            userInput.addSyn(CustomStringUtils.joinUsingSpace(synInput));
          }
        }
      }
    }

    if (options.isJoin()) {
      userInput.getSyns().forEach(syn -> {
        userInput.addFinalInput(CustomStringUtils.removeSpaces(syn));
      });
    } else {
      userInput.setFinalInputs(userInput.getSyns());
    }

    return userInput;

  }

  /**
   * Parses the user input using the default options.<br />
   * 
   * @param input
   *          the {@link String} that represents the user input
   * 
   * @return the {@link UserInput} that represents the parsed user input
   */
  public UserInput parse(String input) {
    return parse(input, new NlpParserOptions());
  }

}