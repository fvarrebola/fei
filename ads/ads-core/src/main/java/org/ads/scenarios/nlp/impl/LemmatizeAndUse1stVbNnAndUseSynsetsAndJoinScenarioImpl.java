package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-05",
    name = "lemmatize-and-use1stvn-and-syns-and-join",
    description = "Lemmatize, use 1st verb and noun, synonyms and join words")
public class LemmatizeAndUse1stVbNnAndUseSynsetsAndJoinScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().lemma().use1stVbAndNn().useSynsets()
        .join().build();
  }

}
