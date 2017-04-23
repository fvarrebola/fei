package org.ads.langs.java.docs.parsers.html;

import org.ads.langs.java.model.JavaObject;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

import java.util.List;

/**
 * Interface for the <code>allclasses-frame.html</code> file parsers.<br />
 * 
 * @author arrebola
 *
 */
public interface HtmlFileParser {

  /**
   * Parses a {@link Jsoup} document into a list of classes.<br />
   * The document must have been generated from a {@link #ALL_CLASSES_FRAME_FILE} file.<br />
   * 
   * @param document
   *          the {@link Document} to be parsed
   * 
   * @return the {@link List} of {@link String} found by the parser
   */
  public abstract List<String> parseClassListFromAllClassesFrameFile(Document document);

  /**
   * Parses a {@link Jsoup} document into a {@link JavaObject}.<br />
   * 
   * @param document
   *          the {@link Document} to be parsed
   * 
   * @return the {@link JavaObject} found by the parser
   */
  public abstract JavaObject parseObjectFile(Document document);

}
