package org.ads.langs.java.docs.parsers.html.impl;

import org.ads.langs.java.docs.parsers.html.HtmlFileParser;
import org.ads.langs.java.model.JavaObject;
import org.ads.utils.Parameters;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

import java.util.List;

public abstract class AbstractHtmlFileParserImpl implements HtmlFileParser {

  protected static final Logger LOGGER = LogManager.getLogger(AbstractHtmlFileParserImpl.class);

  /**
   * Constructor.<br />
   */
  public AbstractHtmlFileParserImpl() {
    super();
  }

  /**
   * Determines if a {@link Jsoup} document represents an interface.<br />
   * 
   * @param document
   *          the {@link Document} to be parsed
   * 
   * @return <code>true</code> if a {@link Jsoup} document represents an interface, otherwise
   *         <code>false</code>
   */
  protected abstract boolean isInterface(Document document);

  /**
   * Parses a {@link Jsoup} document into a {@link JavaObject}.<br />
   * 
   * @param document
   *          the {@link Document} to be parsed
   * 
   * @return the {@link JavaObject} found by the parser
   */
  public abstract JavaObject doParseObjectFile(Document document);

  @Override
  public JavaObject parseObjectFile(Document document) {

    Parameters.requireNonNull(document);

    return doParseObjectFile(document);

  }

  /**
   * Parses a {@link Jsoup} document into a list of classes.<br />
   * The document must have been generated from a {@link #ALL_CLASSES_FRAME_FILE} file.<br />
   * 
   * @param document
   *          the {@link Document} to be parsed
   * 
   * @return the {@link List} of {@link String} found by the parser
   */
  public abstract List<String> doParseClassListFromAllClassesFrameFile(Document document);

  @Override
  public List<String> parseClassListFromAllClassesFrameFile(Document document) {

    Parameters.requireNonNull(document);

    return doParseClassListFromAllClassesFrameFile(document);
  }

}