package org.ads.utils;

import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.select.Elements;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

import javax.validation.constraints.Null;

/**
 * Programming language simple classifier.<br />
 * 
 * @author arrebola
 *
 */
public class ProgrammingLanguageSimpleClassifier {

  /*
   * private static String CODE_HTML_TAG = "code";
   * 
   * private static int countClassesThatCouldContainCode(Document document) { Elements elements =
   * document.getElementsByAttributeValueContaining("class", CODE_HTML_TAG); return (elements !=
   * null ? elements.size() : 0); }
   * 
   * private static int countCodeElements(Document document) { Elements elements =
   * document.getElementsByTag(CODE_HTML_TAG); return (elements != null ? elements.size() : 0); }
   */

  /**
   * Gets the most likely programming language referenced by the given {@link Jsoup} document.<br />
   * Classification is quite simple and it is done based on statistics that consider the number of
   * HTML elements that meet specific criteria.<br />
   * 
   * @param document
   *          the {@link Jsoup} document
   *          
   * @return the {@link ProgrammingLanguages}
   */
  @Null
  public ProgrammingLanguages getMostLikely(Document document) {

    Parameters.requireNonNull(document);

    Map<ProgrammingLanguages, Float> statistics = new HashMap<ProgrammingLanguages, Float>();
    final int totalElementsCount = document.getAllElements().size();
    for (ProgrammingLanguages lang : ProgrammingLanguages.values()) {
      for (String keyword : ProgrammingLanguages.aliases(lang)) {
        Elements elements = document.getElementsContainingText(keyword);
        if (elements == null) {
          continue;
        }
        statistics.put(lang, (elements.size() / (totalElementsCount * 1.0f)));
      }
    }

    if (statistics.isEmpty()) {
      throw new IllegalArgumentException();
    }

    ProgrammingLanguages language = null;

    Float max = 0.0f;
    Set<Map.Entry<ProgrammingLanguages, Float>> entrySet = statistics.entrySet();
    for (Map.Entry<ProgrammingLanguages, Float> entry : entrySet) {
      if (entry.getValue().compareTo(max) > 0) {
        language = entry.getKey();
        max = entry.getValue();
      }
    }

    return language;

  }

}
