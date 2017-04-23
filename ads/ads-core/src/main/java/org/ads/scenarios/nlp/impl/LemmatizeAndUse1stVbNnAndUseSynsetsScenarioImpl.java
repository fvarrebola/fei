package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-06",
    name = "lemmatize-and-use1stvn-and-syns-and-stem",
    description = "Lemmatize, use 1st verb and noun and synonyms")
public class LemmatizeAndUse1stVbNnAndUseSynsetsScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().lemma().use1stVbAndNn().useSynsets()
        .build();
  }

}
