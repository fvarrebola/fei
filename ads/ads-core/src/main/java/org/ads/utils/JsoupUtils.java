package org.ads.utils;

import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

public class JsoupUtils {

  private static String A = "a";
  private static String DD = "dd";
  private static String DL = "dl";
  private static String DT = "dt";
  private static String H3 = "h3";
  private static String PRE = "pre";

  /**
   * Determines if an element's tag matches the tag name given.<br />
   * 
   * @param element
   *          the {@link Element} to check
   * @param tagName
   *          the {@link String} that represents the tag name
   * 
   * @return <code>true</code> if the given element is a {@value #DT}; <code>false</code> otherwise
   */
  public static boolean isOfGivenTag(Element element, String tagName) {

    Parameters.requireNonNull(element);
    Parameters.requireNonEmpty(tagName);

    return tagName.equals(element.tagName());

  }

  /**
   * Determines if an element is a {@value #A}.<br />
   * 
   * @param element
   *          the {@link Element}
   * 
   * @return <code>true</code> if the given element is a {@value #A}; <code>false</code> otherwise
   */
  public static boolean isA(Element element) {
    return isOfGivenTag(element, A);
  }

  /**
   * Determines if an element is a {@value #DD}.<br />
   * 
   * @param element
   *          the {@link Element} to check
   * 
   * @return <code>true</code> if the given element is a {@value #DD}; <code>false</code> otherwise
   */
  public static boolean isDd(Element element) {
    return isOfGivenTag(element, DD);
  }

  /**
   * Determines if an element is a {@value #DL}.<br />
   * 
   * @param element
   *          the {@link Element}
   * 
   * @return <code>true</code> if the given element is a {@value #DL}; <code>false</code> otherwise
   */
  public static boolean isDl(Element element) {
    return isOfGivenTag(element, DL);
  }

  /**
   * Determines if an element is a {@value #DT}.<br />
   * 
   * @param element
   *          the {@link Element}
   * 
   * @return <code>true</code> if the given element is a {@value #DT}; <code>false</code> otherwise
   */
  public static boolean isDt(Element element) {
    return isOfGivenTag(element, DT);
  }

  /**
   * Determines if an element is a {@value #H3}.<br />
   * 
   * @param element
   *          the {@link Element}
   * 
   * @return <code>true</code> if the given element is a {@value #H3}; <code>false</code> otherwise
   */
  public static boolean isH3(Element element) {
    return isOfGivenTag(element, H3);
  }

  /**
   * Determines if an element is a {@value #PRE}.<br />
   * 
   * @param element
   *          the {@link Element}
   * 
   * @return <code>true</code> if the given element is a {@value #PRE}; <code>false</code> otherwise
   */
  public static boolean isPre(Element element) {
    return isOfGivenTag(element, PRE);
  }

  /**
   * Clean the text from an element by normalizing white spaces.<br />
   * 
   * @param element
   *          the {@link Element} to be normalized
   * 
   * @return {@link String}that represents the normalized text
   */
  public static String getCleanText(Element element) {

    Parameters.requireNonNull(element);

    return CustomStringUtils.cleanup(element.text());

  }

  /**
   * Gets the text of a child element according to the given index.<br />
   * 
   * @param children
   *          the {@link Elements} collection
   * @param index
   *          the index
   * 
   * @return the {@link String} that represents the text data
   */
  public static String getTextFromNthChild(Elements children, int index) {

    Parameters.requireNonNull(children);

    String text = CustomStringUtils.EMPTY;
    if (index < children.size()) {
      final Element element = children.get(index);
      if (CustomObjectUtils.isNotNull(element)) {
        text = getCleanText(element);
      }
    }

    return text;

  }

  /**
   * Gets the text of the first element of a collection.<br />
   * 
   * @param children
   *          the {@link Elements} elements collection
   * 
   * @return the {@link String} that represents the text data
   */
  public static String getTextFromFirstChild(Elements children) {
    return getTextFromNthChild(children, 0);
  }

}
