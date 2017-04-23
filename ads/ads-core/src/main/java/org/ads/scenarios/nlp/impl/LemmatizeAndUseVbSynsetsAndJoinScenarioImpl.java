package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-12",
    name = "lemmatize-vbsyns-and-stem-and-join",
    description = "Lemmatize, use verb synonyms and join words")
public class LemmatizeAndUseVbSynsetsAndJoinScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().lemma().useVbSynsOnly().join().build();
  }

}
