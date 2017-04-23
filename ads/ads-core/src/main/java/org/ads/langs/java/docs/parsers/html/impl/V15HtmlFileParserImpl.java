package org.ads.langs.java.docs.parsers.html.impl;

import org.ads.langs.java.model.JavaField;
import org.ads.langs.java.model.JavaMethod;
import org.ads.langs.java.model.JavaObject;
import org.ads.langs.java.model.JavaParameter;
import org.ads.langs.java.model.JavaType;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.JsoupUtils;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.function.Consumer;

/**
 * The 1.6 Javadoc file parser.<br />
 * The 1.6 implementation stacks fields, constructors and methods all in one place, with no
 * particular organization. Being so, we have to select all a, h3, pre and dl elements.<br />
 * 
 * @author arrebola
 */
public class V15HtmlFileParserImpl extends AbstractHtmlFileParserImpl {

  private static final String NAME_ATTRIB = "name";

  private static final String FIELD_DETAIL_NAME_ATTRIB_VALUE = "field_detail";
  private static final String CONSTRUCTOR_DETAIL_NAME_ATTRIB_VALUE = "constructor_detail";
  private static final String METHOD_DETAIL_NAME_ATTRIB_VALUE = "method_detail";

  private static final String PARAMETERES_DT = "Parameters:";
  private static final String RETURNS_DT = "Returns:";

  /**
   * Constructor.<br />
   */
  public V15HtmlFileParserImpl() {
    super();
  }

  @Override
  protected boolean isInterface(Document document) {
    return true;
  }

  @Override
  public List<String> doParseClassListFromAllClassesFrameFile(Document document) {

    List<String> objects = new ArrayList<String>();

    document.select("tr td font a").forEach(new Consumer<Element>() {
      @Override
      public void accept(Element element) {
        objects.add(element.attr("href"));
      }
    });

    return objects;

  }

  /**
   * Parses a {@link JavaParameter} from a {@link Jsoup} {@link Element}.
   * 
   * @param details
   *          the {@link Jsoup} {@link Element}
   * 
   * @return the {@link JavaParameter} found
   */
  protected static JavaParameter parseJavaParameter(Element element) {

    JavaParameter parameter = null;

    if (CustomObjectUtils.isNull(element)) {
      return parameter;
    }

    final String text = element.text();
    if (CustomStringUtils.isEmpty(text)) {
      return parameter;
    }

    final int end = CustomStringUtils.indexOf(text, CustomStringUtils.DASH);
    if (end > 2) {
      parameter = new JavaParameter();
      parameter.setName(CustomStringUtils.cleanup(CustomStringUtils.substring(text, 0, end)));
      parameter
          .setDescription(CustomStringUtils.cleanup(CustomStringUtils.substring(text, end + 1)));
    }

    return parameter;

  }

  /**
   * Parses a {@link JavaType} from a {@link Jsoup} {@link Element}.
   * 
   * @param details
   *          the {@link Jsoup} {@link Element}
   * 
   * @return the {@link JavaType} found
   */
  protected static JavaType parseJavaType(Element element) {

    JavaType type = null;

    if (CustomObjectUtils.isNull(element)) {
      return type;
    }

    type = new JavaType();
    type.setDescription(CustomStringUtils.cleanup(element.text()));

    return type;

  }

  private static boolean isFieldDetailSection(Element element) {
    return FIELD_DETAIL_NAME_ATTRIB_VALUE.equals(element.attr(NAME_ATTRIB));
  }

  private static boolean isMethodDetailSection(Element element) {
    final String attribValue = element.attr(NAME_ATTRIB);
    return (CONSTRUCTOR_DETAIL_NAME_ATTRIB_VALUE.equals(attribValue)
        || METHOD_DETAIL_NAME_ATTRIB_VALUE.equals(attribValue));
  }

  /**
   * Parses the {@link List} of {@link JavaField} fields from a {@link ListIterator} of
   * {@link Jsoup} {@link Element} elements.<br />
   * 
   * @param iterator
   *          the {@link ListIterator} of {@link Jsoup} {@link Element} elements
   * 
   * @return the {@link List} of {@link JavaField} fields found
   */
  protected static List<JavaField> parseJavaFields(ListIterator<Element> iterator) {

    List<JavaField> fields = new ArrayList<JavaField>();

    while (iterator.hasNext()) {

      Element element = iterator.next();

      if (JsoupUtils.isA(element) && isMethodDetailSection(element)) {
        iterator.previous();
        break;
      }

      if (!JsoupUtils.isH3(element)) {
        continue;
      }

      JavaField field = new JavaField();
      field.setName(JsoupUtils.getCleanText(element));

      if (iterator.hasNext()) {
        Element pre = iterator.next();
        if (JsoupUtils.isPre(pre)) {
          field.setSignature(JsoupUtils.getCleanText(pre));
        }
      }

      boolean found = false;
      while (iterator.hasNext() && !found) {
        Element dl = iterator.next();
        if (JsoupUtils.isDl(dl)) {
          field.setDescription(JsoupUtils.getTextFromFirstChild(dl.children()));
          found = true;
        }
      }

      fields.add(field);

    }

    return fields;

  }

  /**
   * Parses the second level DL element of a method detail info into a {@link JavaMethod}.<br />
   * 
   * @param dl
   *          the {@link Element} to be parsed
   * @param method
   *          the {@link JavaMethod}
   */
  protected static void parseSecondLevelDlIntoJavaMethod(Element dl, JavaMethod method) {

    Elements children = dl.children();

    if (children.isEmpty()) {
      return;
    }

    Iterator<Element> iterator = dl.children().iterator();
    while (iterator.hasNext()) {

      Element element = iterator.next();
      if (!JsoupUtils.isDt(element)) {
        continue;
      }

      final String text = element.text();
      if (PARAMETERES_DT.equals(text)) {
        while (iterator.hasNext()) {
          Element dd = iterator.next();
          if (!JsoupUtils.isDd(dd)) {
            break;
          }
          JavaParameter parameter = parseJavaParameter(dd);
          if (CustomObjectUtils.isNotNull(parameter)) {
            method.addParameter(parameter);
          }
        }
      } else if (RETURNS_DT.equals(text) && iterator.hasNext()) {
        method.setReturnType(parseJavaType(iterator.next()));
      }

    }

  }

  protected static void parseDdIntoJavaMethod(Element dd, JavaMethod method) {

    Elements children = dd.children();

    if (children.select("dl").isEmpty()) {
      method.setDescription(JsoupUtils.getCleanText(dd));
      return;
    }

    Iterator<Element> iterator = children.iterator();
    while (iterator.hasNext()) {
      Element element = iterator.next();
      if (JsoupUtils.isDl(element)) {
        parseSecondLevelDlIntoJavaMethod(element, method);
      } else {
        method.setDescription(JsoupUtils.getCleanText(element));
      }
    }

  }

  /**
   * Parses the first level DL element of a method detail info into a {@link JavaMethod}.<br />
   * 
   * @param dl
   *          the {@link Element} to be parsed
   * @param method
   *          the {@link JavaMethod}
   */
  protected static void parseFirstLevelDlIntoJavaMethod(Element dl, JavaMethod method) {

    Elements children = dl.children();

    if (children.isEmpty()) {
      return;
    }

    Iterator<Element> iterator = children.iterator();
    while (iterator.hasNext()) {
      parseDdIntoJavaMethod(iterator.next(), method);
    }

  }

  /**
   * Parses the {@link List} of {@link JavaMethod} methods from a {@link ListIterator} of
   * {@link Jsoup} {@link Element} elements.<br />
   * 
   * @param iterator
   *          the {@link ListIterator} of {@link Jsoup} {@link Element} elements
   * 
   * @return the {@link List} of {@link JavaMethod} methods found
   */
  protected static List<JavaMethod> parseJavaMethods(ListIterator<Element> iterator) {

    List<JavaMethod> methods = new ArrayList<JavaMethod>();

    while (iterator.hasNext()) {

      Element element = iterator.next();

      if (!JsoupUtils.isH3(element)) {
        continue;
      }

      JavaMethod method = new JavaMethod();
      method.setName(JsoupUtils.getCleanText(element));

      if (iterator.hasNext()) {
        Element pre = iterator.next();
        if (JsoupUtils.isPre(pre)) {
          method.setSignature(JsoupUtils.getCleanText(pre));
        }
      }

      boolean found = false;
      while (iterator.hasNext() && !found) {
        Element dl = iterator.next();
        if (JsoupUtils.isDl(dl)) {
          parseFirstLevelDlIntoJavaMethod(dl, method);
          found = true;
        }
      }

      methods.add(method);

    }

    return methods;

  }

  @Override
  public JavaObject doParseObjectFile(Document document) {

    final Element b = document.select("pre b").first();
    if (CustomObjectUtils.isNull(b)) {
      if (isInterface(document)) {
        LOGGER.info("This is probably an interface and right now this is not supported.");
      }
      throw new IllegalArgumentException("\"pre b\" first element not found");
    }

    final String name = CustomStringUtils.cleanup(b.text());
    if (CustomStringUtils.isEmpty(name)) {
      throw new IllegalArgumentException("Object name cannot be empty.");
    }

    final String description = CustomStringUtils
        .cleanup(JsoupUtils.getTextFromFirstChild(document.select("dl + p")));
    if (CustomStringUtils.isEmpty(name)) {
      LOGGER.warn("{} object's description is empty.", name);
    }

    JavaObject object = new JavaObject(name, description);

    Elements elements = document.select("a, h3, pre, dl");
    ListIterator<Element> iterator = elements.listIterator();
    while (iterator.hasNext()) {
      Element element = iterator.next();
      if (JsoupUtils.isA(element)) {
        if (isFieldDetailSection(element)) {
          object.setFields(parseJavaFields(iterator));
        } else if (isMethodDetailSection(element)) {
          object.setMethods(parseJavaMethods(iterator));
        }
      }
    }

    return object;

  }

}
