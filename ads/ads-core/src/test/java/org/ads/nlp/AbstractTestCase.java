package org.ads.nlp;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.fail;

import org.ads.DataSet;
import org.ads.utils.JsonLoader;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;

import java.net.URL;
import java.util.HashMap;
import java.util.Map;

import javax.validation.constraints.NotNull;

public abstract class AbstractTestCase {

  private static Map<String, DataSet> dataSetMap;

  public AbstractTestCase() {
    super();
  }

  protected static void loadDataSetMap(Class<?> clazz) {

    assertNotNull(clazz);

    final DataSet[] array = JsonLoader.loadFromResource(clazz.getName() + ".json",
        DataSet[].class);
    assertNotNull(array);

    dataSetMap = new HashMap<String, DataSet>(array.length);
    for (DataSet element : array) {
      dataSetMap.put(element.getId(), element);
    }

    assertNotNull(dataSetMap);

  }

  @NotNull
  protected DataSet getDataSet(String key) {

    DataSet ioDataSet = dataSetMap.get(key);
    assertNotNull(ioDataSet);

    DataSet.Data[] ioData = ioDataSet.getData();
    assertNotNull(ioData);

    return ioDataSet;

  }

  @NotNull
  protected Document loadHtmlFromUrl(String url) {

    assertNotNull(url);

    Document document = null;
    try {
      document = Jsoup.parse(new URL(url), 5000);
    } catch (Exception exception) {
      fail(exception.getMessage());
    }
    
    assertNotNull(document);

    return document;
    
  }
  
}
