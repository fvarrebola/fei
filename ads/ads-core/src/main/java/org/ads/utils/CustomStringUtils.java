package org.ads.utils;

import org.apache.commons.lang3.StringUtils;

public class CustomStringUtils extends StringUtils {

  public static final String UNKNOWN = "?";
  public static final String TRUE = "true";
  public static final String FALSE = "false";

  public static final String PIPE = "|";

  public static final String YES = "Yes";
  public static final String NO = "No";

  public static final String STAR = "*";
  public static final String LOTS_OF_STARS = repeat(STAR, 120);

  public static final String DASH = "-";
  public static final String LOTS_OF_DASHES = repeat(DASH, 120);

  public static final String DOT = ".";

  public static final String UNDERLINE = "_";

  public static final String NA = "NA";

  public static final String UTF_8 = "UTF-8";

  /**
   * Abbreviation width.<br />
   */
  private static final int WIDTH = 64;

  /**
   * Removes all occurrences of line breaks, which includes the carriage return and line feed
   * characters ('\r' and '\n').<br />
   * 
   * @param str
   *          the source {@link String} to search
   * 
   * @return the {@link String} with the line breaks removed if found
   */
  public static String removeLineBreaks(String str) {

    Parameters.requireNonNull(str);

    return remove(remove(str, '\r'), '\n');

  }

  /**
   * Abbreviates a {@link String} using ellipses up to {@value #WIDTH} characters.<br />
   * 
   * @param str
   *          the {@link String} to check
   * 
   * @return abbreviated {@link String}
   */
  public static Object abbreviate(String str) {
    return abbreviate(str, WIDTH);
  }

  /**
   * Cleans up a {@link String} removing its line breaks and trailing spaces.<br />
   * 
   * @param str
   *          the {@link String} to clean
   * 
   * @return cleaned {@link String}
   */
  public static String cleanup(String str) {
    return CustomStringUtils.normalizeSpace(str);
  }

  /**
   * Joins the elements of the provided array into a single String containing the provided list of
   * elements.<br />
   * 
   * @param array
   *          the array of values to join together, may be null
   * 
   * @return the joined String, null if null array input
   */
  public static String joinUsingSpace(Object[] array) {
    return join(array, SPACE);
  }

  /**
   * Removes all occurrences of a space from within the source string..<br />
   * 
   * @param str
   *          the source String to search, may be null
   * 
   * @return the substring with spaces removed if found
   */
  public static String removeSpaces(String str) {
    return remove(str, SPACE);
  }
}
