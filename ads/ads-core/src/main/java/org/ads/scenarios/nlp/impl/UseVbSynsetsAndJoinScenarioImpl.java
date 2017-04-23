package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-23",
    name = "vbsyns-and-join",
    description = "Use verb synonyms and join words")
public class UseVbSynsetsAndJoinScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().useVbSynsOnly().join().build();
  }

}
