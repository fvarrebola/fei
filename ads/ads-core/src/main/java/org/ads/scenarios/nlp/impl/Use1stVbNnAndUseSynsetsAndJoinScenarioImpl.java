package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-16",
    name = "use1stvn-and-syns-and-join",
    description = "Use 1st verb and noun, synonyms and join words")
public class Use1stVbNnAndUseSynsetsAndJoinScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().use1stVbAndNn().useSynsets().join()
        .build();
  }

}
