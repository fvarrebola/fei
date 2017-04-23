package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-01",
    name = "default",
    description = "Default NLP scenario")
public class DefaultNlpScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().build();
  }

}
