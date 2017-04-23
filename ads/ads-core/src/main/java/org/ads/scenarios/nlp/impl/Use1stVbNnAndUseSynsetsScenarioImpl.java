package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-17",
    name = "use1stvn-and-syns",
    description = "Use 1st verb and noun and synonyms")
public class Use1stVbNnAndUseSynsetsScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().use1stVbAndNn().useSynsets().build();
  }

}
