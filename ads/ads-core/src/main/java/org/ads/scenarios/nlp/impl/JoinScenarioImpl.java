package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-02",
    name = "join",
    description = "Join words")
public class JoinScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().join().build();
  }

}
