package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-22",
    name = "syns",
    description = "Use synonyms")
public class UseSynsetsScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().useSynsets().build();
  }

}
