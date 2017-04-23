package org.ads.langs.java.docs.parsers.html;

import org.ads.langs.java.Version;
import org.ads.langs.java.docs.parsers.html.impl.EmptyHtmlFileParserImpl;
import org.ads.langs.java.docs.parsers.html.impl.V15HtmlFileParserImpl;
import org.ads.langs.java.docs.parsers.html.impl.V17HtmlFileParserImpl;
import org.ads.langs.java.docs.parsers.html.impl.V18HtmlFileParserImpl;
import org.ads.utils.Parameters;

/**
 * The <code>allclasses-frame.html</code> file parser factory.<br />
 * 
 * @author arrebola
 *
 */
public final class HtmlFileParserFactory {

  /**
   * Gets the overview tree file parser implementation that supports a given javadoc version.<br />
   * 
   * @param version
   *          the {@link Version} version
   * 
   * @return the {@link HtmlFileParser} implementation
   */
  public static HtmlFileParser getInstance(Version version) {

    Parameters.requireNonNull(version);

    HtmlFileParser parserImpl = null;

    /*
     * if (JavadocVersion.V_1_0.equals(version)) { parserImpl = new V10FileParserImpl(); } else if
     * (JavadocVersion.V_1_1.equals(version)) { parserImpl = new V11FileParserImpl(); } else if
     * (JavadocVersion.V_1_2.equals(version)) { parserImpl = new V12FileParserImpl(); } else if
     * (JavadocVersion.V_1_3.equals(version)) { parserImpl = new V13FileParserImpl(); } else if
     * (JavadocVersion.V_1_4.equals(version)) { parserImpl = new V14FileParserImpl(); } else
     */
    if (Version.V_1_5.equals(version)) {
      parserImpl = new V15HtmlFileParserImpl();
    } else if (Version.V_1_6.equals(version)) {
      parserImpl = new V15HtmlFileParserImpl();
    } else if (Version.V_1_7.equals(version)) {
      parserImpl = new V17HtmlFileParserImpl();
    } else if (Version.V_1_8.equals(version)) {
      parserImpl = new V18HtmlFileParserImpl();
    } else {
      parserImpl = new EmptyHtmlFileParserImpl();
    }

    return parserImpl;

  }

}
