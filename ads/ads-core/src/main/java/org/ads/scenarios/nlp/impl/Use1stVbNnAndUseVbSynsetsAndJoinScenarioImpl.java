package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-18",
    name = "use1stvn-and-vbsyns-and-join",
    description = "Use 1st verb and noun, verb synonyms and join words")
public class Use1stVbNnAndUseVbSynsetsAndJoinScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().use1stVbAndNn().useVbSynsOnly().join()
        .build();
  }

}
