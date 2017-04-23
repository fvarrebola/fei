package org.ads.nlp;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

import org.ads.DataSet;
import org.ads.nlp.NlpParserOptions.NlpParserOptionsBuilder;
import org.ads.utils.CustomStringUtils;
import org.junit.BeforeClass;
import org.junit.Test;

public class NlpParserTest extends AbstractTestCase {

  private static NlpParser parser;

  @BeforeClass
  public static void beforeClass() {
    try {
      parser = NlpParser.getInstance();
      loadDataSetMap(NlpParserTest.class);
    } catch (Exception exception) {
      fail(exception.getMessage());
    }
  }

  @Test
  public void testParsingWithoutOptions() {
    final DataSet dataSet = getDataSet("default");
    for (DataSet.Data data : dataSet.getData()) {
      final UserInput parsed = parser.parse(data.getInput());
      assertEquals(data.getOutput(), CustomStringUtils.joinUsingSpace(parsed.getFinalInputs().toArray()));
    }
  }

  @Test
  public void testSafeParsing() {
    NlpParserOptionsBuilder builder = new NlpParserOptionsBuilder().safe();
    final DataSet dataSet = getDataSet("quotes-removal");
    for (DataSet.Data data : dataSet.getData()) {
      final UserInput parsed = parser.parse(data.getInput(), builder.build());
      assertEquals(data.getOutput(), parsed.getTokenized());
    }
  }

  @Test
  public void testPosTagging() {
    NlpParserOptionsBuilder builder = new NlpParserOptionsBuilder();
    final DataSet dataSet = getDataSet("pos-tagging");
    for (DataSet.Data data : dataSet.getData()) {
      final UserInput parsed = parser.parse(data.getInput(), builder.build());
      assertEquals(data.getOutput(), parsed.getTags());
    }
  }

  @Test
  public void testUse1stVbAndNn() {
    NlpParserOptionsBuilder builder = new NlpParserOptionsBuilder().use1stVbAndNn();
    final DataSet dataSet = getDataSet("1st-VB-and-NN");
    for (DataSet.Data data : dataSet.getData()) {
      final UserInput parsed = parser.parse(data.getInput(), builder.build());
      assertEquals(data.getOutput(),
          CustomStringUtils.joinUsingSpace(parsed.getFinalInputs().toArray()));
    }
  }

  @Test
  public void testUseSynsets() {
    NlpParserOptionsBuilder builder = new NlpParserOptionsBuilder().useSynsets();
    final DataSet dataSet = getDataSet("synsets");
    for (DataSet.Data data : dataSet.getData()) {
      final UserInput parsed = parser.parse(data.getInput(), builder.build());
      assertEquals(data.getOutput(),
          CustomStringUtils.join(parsed.getFinalInputs().toArray(), ", "));
    }
  }

  @Test
  public void testUseVbSynsets() {
    NlpParserOptionsBuilder builder = new NlpParserOptionsBuilder().useSynsets().useVbSynsOnly();
    final DataSet dataSet = getDataSet("vb-synsets");
    for (DataSet.Data data : dataSet.getData()) {
      final UserInput parsed = parser.parse(data.getInput(), builder.build());
      assertEquals(data.getOutput(),
          CustomStringUtils.join(parsed.getFinalInputs().toArray(), ", "));
    }
  }

  @Test
  public void testUseVbSynsetsWithoutSettingSynsetsUse() {
    NlpParserOptionsBuilder builder = new NlpParserOptionsBuilder().useVbSynsOnly();
    final DataSet dataSet = getDataSet("vb-synsets");
    for (DataSet.Data data : dataSet.getData()) {
      final UserInput parsed = parser.parse(data.getInput(), builder.build());
      assertEquals(data.getOutput(),
          CustomStringUtils.join(parsed.getFinalInputs().toArray(), ", "));
    }
  }

  @Test
  public void testLemmas() {
    NlpParserOptionsBuilder builder = new NlpParserOptionsBuilder().lemma();
    final DataSet dataSet = getDataSet("lemma");
    for (DataSet.Data data : dataSet.getData()) {
      final UserInput parsed = parser.parse(data.getInput(), builder.build());
      assertEquals(data.getOutput(), CustomStringUtils.join(parsed.getFinalInputs().toArray(),
          ", "));
    }
  }

  @Test
  public void testJoin() {
    NlpParserOptionsBuilder builder = new NlpParserOptionsBuilder().join();
    final DataSet dataSet = getDataSet("join");
    for (DataSet.Data data : dataSet.getData()) {
      final UserInput parsed = parser.parse(data.getInput(), builder.build());
      assertEquals(data.getOutput(), CustomStringUtils.join(parsed.getFinalInputs().toArray()));
    }
  }
}
