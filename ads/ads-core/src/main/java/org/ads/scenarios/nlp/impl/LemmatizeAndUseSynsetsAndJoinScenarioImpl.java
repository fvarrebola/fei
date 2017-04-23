package org.ads.scenarios.nlp.impl;

import org.ads.nlp.NlpParserOptions;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.NlpScenario;

@Scenario(
    id = "NLP-10",
    name = "lemmatize-and-usesyns-and-join",
    description = "Lemmatize, use synonyms, stem and join words")
public class LemmatizeAndUseSynsetsAndJoinScenarioImpl implements NlpScenario {

  @Override
  public NlpParserOptions getOptions() {
    return new NlpParserOptions.NlpParserOptionsBuilder().lemma().useSynsets().join().build();
  }

}
