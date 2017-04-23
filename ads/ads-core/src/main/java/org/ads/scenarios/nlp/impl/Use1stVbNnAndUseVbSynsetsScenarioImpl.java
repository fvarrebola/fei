package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-19",
    name = "use1stvn-and-vbsyns",
    description = "Use 1st verb and noun and verb synonyms")
public class Use1stVbNnAndUseVbSynsetsScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().use1stVbAndNn().useVbSynsOnly().build();
  }

}
