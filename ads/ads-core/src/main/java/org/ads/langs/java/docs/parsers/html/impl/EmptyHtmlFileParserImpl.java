package org.ads.langs.java.docs.parsers.html.impl;

import org.ads.langs.java.model.JavaObject;
import org.jsoup.nodes.Document;

import java.util.ArrayList;
import java.util.List;

/**
 * An empty <code>allclasses-frame.html</code> file parser.<br />
 * 
 * @author arrebola
 *
 */
public class EmptyHtmlFileParserImpl extends AbstractHtmlFileParserImpl {

  /**
   * Constructor.<br />
   */
  public EmptyHtmlFileParserImpl() {
    super();
  }

  @Override
  protected boolean isInterface(Document document) {
    return true;
  }

  @Override
  public JavaObject doParseObjectFile(Document document) {
    return new JavaObject();
  }

  @Override
  public List<String> doParseClassListFromAllClassesFrameFile(Document document) {
    return new ArrayList<String>();
  }

}
