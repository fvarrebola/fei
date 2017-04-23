package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-09",
    name = "lemmatize-and-use1stvn",
    description = "Lemmatize and use 1st verb and noun")
public class LemmatizeAndUse1stVbNnScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().lemma().use1stVbAndNn().build();
  }

}
