package org.ads.langs.java.docs.parsers.html.impl;

/**
 * The 1.8 Javadoc file parser.<br />
 * Note that the 1.8 version implementation behaves almost the same as version 1.7.<br />
 * 
 * @author arrebola
 * 
 * @see V17HtmlFileParserImpl
 */
public class V18HtmlFileParserImpl extends V17HtmlFileParserImpl {

  /**
   * Constructor.<br />
   */
  public V18HtmlFileParserImpl() {
    super();
    cssQuerySelectorSeparatorChar = ".";
  }

}