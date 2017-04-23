package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-08",
    name = "lemmatize-use1stvn-and-vbsyns",
    description = "Lemmatize, use 1st verb and noun and verb synonyms")
public class LemmatizeAndUse1stVbNnAndUseVbSynsetsScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().lemma().use1stVbAndNn().useVbSynsOnly()
        .build();
  }

}
