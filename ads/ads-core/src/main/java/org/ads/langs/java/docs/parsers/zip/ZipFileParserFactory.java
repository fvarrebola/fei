package org.ads.langs.java.docs.parsers.zip;

import org.ads.langs.java.docs.parsers.zip.impl.GenericZipFileParserImpl;
import org.ads.langs.java.docs.parsers.zip.impl.JdkZipFileParserImpl;
import org.ads.utils.Parameters;

/**
 * The ZIP file parser factory.<br />
 * 
 * @author arrebola
 *
 */
public final class ZipFileParserFactory {

  public enum ParserTypes {
    GENERIC, JDK;
  }

  /**
   * Gets the ZIP file parser implementation that supports a given type.<br />
   * 
   * @param type
   *          the {@link ParserTypes} type
   * 
   * @return the {@link ZipFileParser} implementation
   */
  public static ZipFileParser getInstance(ParserTypes type) {

    Parameters.requireNonNull(type);

    ZipFileParser parserImpl = null;

    if (ParserTypes.GENERIC.equals(type)) {
      parserImpl = new GenericZipFileParserImpl();
    } else if (ParserTypes.JDK.equals(type)) {
      parserImpl = new JdkZipFileParserImpl();
    } else {
      throw new IllegalArgumentException("Unknown parser type '" + type + "'.");
    }

    return parserImpl;

  }

  /**
   * Gets the default ZIP file parser implementation .<br />
   * 
   * @return the {@link ZipFileParser} implementation
   */
  public static ZipFileParser getInstance() {
    return getInstance(ParserTypes.GENERIC);

  }

}
