package org.ads.langs.java.docs.parsers.html.impl;

import org.ads.langs.java.model.JavaObject;
import org.jsoup.nodes.Document;

import java.util.List;

/**
 * The 1.3 Javadoc file parser.<br />
 * 
 * @author arrebola
 */
public class V13HtmlFileParserImpl extends AbstractHtmlFileParserImpl {

  /**
   * Constructor.<br />
   */
  public V13HtmlFileParserImpl() {
    super();
  }

  @Override
  protected boolean isInterface(Document document) {
    throw new UnsupportedOperationException();
  }

  @Override
  public List<String> doParseClassListFromAllClassesFrameFile(Document document) {
    throw new UnsupportedOperationException();
  }

  @Override
  public JavaObject doParseObjectFile(Document document) {
    throw new UnsupportedOperationException();
  }
}
