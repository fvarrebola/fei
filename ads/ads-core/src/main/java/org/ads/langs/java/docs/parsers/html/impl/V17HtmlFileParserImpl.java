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
import java.util.function.Consumer;

/**
 * The 1.7 Javadoc file parser.<br />
 * 
 * @author arrebola
 *
 */
public class V17HtmlFileParserImpl extends AbstractHtmlFileParserImpl {

  private static final String PARAMETERES_DT = "Parameters:";
  private static final String RETURNS_DT = "Returns:";

  protected String cssQuerySelectorSeparatorChar = "_";

  /**
   * Constructor.<br />
   */
  public V17HtmlFileParserImpl() {
    super();
  }

  @Override
  protected boolean isInterface(Document document) {

    boolean isInterface = false;

    if (CustomObjectUtils.isNull(document)) {
      return isInterface;
    }

    final Element h2 = document.select("h2").first();
    if (CustomObjectUtils.isNotNull(h2)) {
      final String title = h2.attr("title");
      if (CustomStringUtils.containsIgnoreCase(title, "interface")) {
        isInterface = true;
      }
    }

    return isInterface;

  }

  @Override
  public List<String> doParseClassListFromAllClassesFrameFile(Document document) {

    List<String> objects = new ArrayList<String>();

    document.select("li a").forEach(new Consumer<Element>() {
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
  private static JavaParameter parseJavaParameter(Element element) {

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
  private static JavaType parseJavaType(Element element) {

    JavaType type = null;

    if (CustomObjectUtils.isNull(element)) {
      return type;
    }

    type = new JavaType();
    type.setDescription(CustomStringUtils.cleanup(element.text()));

    return type;

  }

  /**
   * Parses a {@link JavaMethod} from a collection of {@link Jsoup} {@link Elements}.<br />
   * This method assumes <code>details</code> element's collection holds no less than three items.
   * <br />
   * 
   * @param details
   *          the {@link Jsoup} {@link Elements}
   * 
   * @return the {@link JavaMethod} found
   */
  protected static JavaMethod parseJavaMethod(Elements details) {

    JavaMethod method = new JavaMethod();

    method.setName(JsoupUtils.getTextFromNthChild(details, 0));
    method.setSignature(JsoupUtils.getTextFromNthChild(details, 1));
    method.setDescription(JsoupUtils.getTextFromNthChild(details, 2));

    if (details.size() != 4) {
      return method;
    }

    Iterator<Element> iterator = details.last().children().iterator();
    while (iterator.hasNext()) {

      Element child = iterator.next();
      if (!JsoupUtils.isDt(child)) {
        continue;
      }

      final String text = child.text();
      if (PARAMETERES_DT.equals(text)) {
        while (iterator.hasNext()) {
          Element element = iterator.next();
          if (JsoupUtils.isDt(element)) {
            break;
          }
          JavaParameter parameter = parseJavaParameter(element);
          if (CustomObjectUtils.isNotNull(parameter)) {
            method.addParameter(parameter);
          }
        }
      } else if (RETURNS_DT.equals(text) && iterator.hasNext()) {
        method.setReturnType(parseJavaType(iterator.next()));
      }

    }

    return method;

  }

  @Override
  public JavaObject doParseObjectFile(Document document) {

    final Element ul = document.select("ul.inheritance").last();
    if (CustomObjectUtils.isNull(ul)) {
      if (isInterface(document)) {
        LOGGER.info("This is probably an interface and right now this is not supported.");
      }
      throw new IllegalArgumentException("\"ul.inheritance\" last element not found");
    }

    final String name = CustomStringUtils.cleanup(JsoupUtils.getTextFromFirstChild(ul.children()));
    if (CustomStringUtils.isEmpty(name)) {
      throw new IllegalArgumentException("Object name cannot be empty.");
    }

    final String description = CustomStringUtils
        .cleanup(JsoupUtils.getTextFromFirstChild(document.select("pre + div.block")));
    if (CustomStringUtils.isEmpty(name)) {
      LOGGER.warn("{} object's description is empty.", name);
    }

    JavaObject object = new JavaObject(name, description);

    // field_detail
    document.select("a[name=field" + cssQuerySelectorSeparatorChar + "detail] ~ ul li").forEach(
        new Consumer<Element>() {
          @Override
          public void accept(Element element) {

            Elements details = element.children();
            if (details.size() == 3) {
              JavaField field = new JavaField();
              field.setName(JsoupUtils.getTextFromNthChild(details, 0));
              field.setSignature(JsoupUtils.getTextFromNthChild(details, 1));
              field.setDescription(JsoupUtils.getTextFromNthChild(details, 2));
              object.addField(field);
            }

          }
        });

    // method consumer to be used in constructors and ordinary method definitions
    Consumer<Element> methodConsumer = new Consumer<Element>() {
      @Override
      public void accept(Element method) {
        Elements details = method.children();
        if (details.size() >= 3 && JsoupUtils.isOfGivenTag(details.first(), "h4")) {
          object.addMethod(parseJavaMethod(details));
        }
      }
    };

    // constructor_detail
    document.select("a[name=constructor" + cssQuerySelectorSeparatorChar + "detail] ~ ul li")
        .forEach(
            methodConsumer);

    // method_detail
    document.select("a[name=method" + cssQuerySelectorSeparatorChar + "detail] ~ ul li").forEach(
        methodConsumer);

    return object;

  }

}
