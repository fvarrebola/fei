package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-13",
    name = "lemmatize-and-vbsyns",
    description = "Lemmatize and use verb synonyms")
public class LemmatizeAndUseVbSynsetsScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().lemma().useVbSynsOnly().build();
  }

}
