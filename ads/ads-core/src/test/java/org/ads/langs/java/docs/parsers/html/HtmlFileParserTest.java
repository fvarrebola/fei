package org.ads.langs.java.docs.parsers.html;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import org.ads.DataSet;
import org.ads.TestUtils;
import org.ads.langs.java.Version;
import org.ads.langs.java.model.JavaObject;
import org.ads.nlp.AbstractTestCase;
import org.jsoup.nodes.Document;
import org.junit.BeforeClass;
import org.junit.Test;

public class HtmlFileParserTest extends AbstractTestCase {

  private static HtmlFileParser parserV17;
  private static HtmlFileParser parserV18;
  
  @BeforeClass
  public static void beforeClass() {
    try {
      loadDataSetMap(HtmlFileParserTest.class);
    } catch (Exception exception) {
      exception.printStackTrace();
      fail(exception.getMessage());
    }
    
    parserV17 = HtmlFileParserFactory.getInstance(Version.V_1_7);
    parserV18 = HtmlFileParserFactory.getInstance(Version.V_1_8);
    
  }

  @Test
  public void testLocalFile() {
  }

  private void testRemoteFile(HtmlFileParser parser, String dataSetName) throws Exception {

    assertNotNull(parser);
    assertNotNull(dataSetName);

    final DataSet dataSet = getDataSet(dataSetName);
    for (DataSet.Data data : dataSet.getData()) {

      Document document = loadHtmlFromUrl(data.getInput());

      JavaObject object = parser.parseObjectFile(document);
      assertNotNull(object);
      assertNotNull(object.getName());
      assertNotNull(object.getFields());
      assertNotNull(object.getMethods());
      assertEquals(data.getOutput(), String.format("%s, %d, %d", object.getName(), object
          .getFields().size(), object.getMethods().size()));

    }
  }

  private void testRemoteClass(HtmlFileParser parser, String dataSetName) {
    try {
      testRemoteFile(parser, dataSetName);
    } catch (Exception exception) {
      fail(exception.getMessage());
    }
  }

  private void testRemoteInterface(HtmlFileParser parser, String dataSetName) {
    try {
      testRemoteFile(parser, dataSetName);
      fail();
    } catch (Exception exception) {
      assertTrue(TestUtils.isIllegalArgumentException(exception));
    }
  }

  @Test
  public void testRemoteV17Interface() {
    testRemoteInterface(parserV17, "remoteV17Interface");
  }
  
  @Test
  public void testRemoteV17Class() {
    testRemoteClass(parserV17, "remoteV17Class");
  }

  @Test
  public void testRemoteV18Class() {
    testRemoteClass(parserV18, "remoteV18Class");
  }

  @Test
  public void testRemoteV18Interface() {
    testRemoteInterface(parserV18, "remoteV18Interface");
  }
}
