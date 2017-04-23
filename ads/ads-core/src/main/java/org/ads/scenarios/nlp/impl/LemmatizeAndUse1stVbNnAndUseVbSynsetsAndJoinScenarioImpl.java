package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-07",
    name = "lemmatize-and-use1stvn-and-vbsyns-and-join",
    description = "Lemmatize, use 1st verb and noun, verb synonyms and join words")
public class LemmatizeAndUse1stVbNnAndUseVbSynsetsAndJoinScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().lemma().use1stVbAndNn().useVbSynsOnly()
        .join().build();
  }

}
