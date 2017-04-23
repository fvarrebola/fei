package org.ads.scenarios.nlp;

import org.ads.scenarios.Scenario;
import org.ads.scenarios.nlp.impl.DefaultNlpScenarioImpl;
import org.ads.scenarios.nlp.impl.JoinScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndUse1stVbNnAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndUse1stVbNnAndUseSynsetsAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndUse1stVbNnAndUseSynsetsScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndUse1stVbNnAndUseVbSynsetsAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndUse1stVbNnAndUseVbSynsetsScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndUse1stVbNnScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndUseSynsetsAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndUseSynsetsScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndUseVbSynsetsAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeAndUseVbSynsetsScenarioImpl;
import org.ads.scenarios.nlp.impl.LemmatizeScenarioImpl;
import org.ads.scenarios.nlp.impl.Use1stVbNnAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.Use1stVbNnAndUseSynsetsAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.Use1stVbNnAndUseSynsetsScenarioImpl;
import org.ads.scenarios.nlp.impl.Use1stVbNnAndUseVbSynsetsAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.Use1stVbNnAndUseVbSynsetsScenarioImpl;
import org.ads.scenarios.nlp.impl.Use1stVbNnScenarioImpl;
import org.ads.scenarios.nlp.impl.UseSynsetsAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.UseSynsetsScenarioImpl;
import org.ads.scenarios.nlp.impl.UseVbSynsetsAndJoinScenarioImpl;
import org.ads.scenarios.nlp.impl.UseVbSynsetsScenarioImpl;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.ObjectFactory;

public class NlpScenarioFactory extends ObjectFactory<NlpScenario> {

  @Override
  protected void doInitialize() {
    register(DefaultNlpScenarioImpl.class);
    register(JoinScenarioImpl.class);
    register(LemmatizeAndJoinScenarioImpl.class);
    register(LemmatizeAndUse1stVbNnAndJoinScenarioImpl.class);
    register(LemmatizeAndUse1stVbNnAndUseSynsetsAndJoinScenarioImpl.class);
    register(LemmatizeAndUse1stVbNnAndUseSynsetsScenarioImpl.class);
    register(LemmatizeAndUse1stVbNnAndUseVbSynsetsAndJoinScenarioImpl.class);
    register(LemmatizeAndUse1stVbNnAndUseVbSynsetsScenarioImpl.class);
    register(LemmatizeAndUse1stVbNnScenarioImpl.class);
    register(LemmatizeScenarioImpl.class);
    register(LemmatizeAndUseSynsetsScenarioImpl.class);
    register(LemmatizeAndUseSynsetsAndJoinScenarioImpl.class);
    register(LemmatizeAndUseVbSynsetsAndJoinScenarioImpl.class);
    register(LemmatizeAndUseVbSynsetsScenarioImpl.class);
    register(Use1stVbNnAndJoinScenarioImpl.class);
    register(Use1stVbNnAndUseSynsetsAndJoinScenarioImpl.class);
    register(Use1stVbNnAndUseSynsetsScenarioImpl.class);
    register(Use1stVbNnAndUseVbSynsetsAndJoinScenarioImpl.class);
    register(Use1stVbNnAndUseVbSynsetsScenarioImpl.class);
    register(Use1stVbNnScenarioImpl.class);
    register(UseSynsetsAndJoinScenarioImpl.class);
    register(UseSynsetsScenarioImpl.class);
    register(UseVbSynsetsAndJoinScenarioImpl.class);
    register(UseVbSynsetsScenarioImpl.class);
  }

  @Override
  protected String doGetClassKey(Class<? extends NlpScenario> clazz) {

    final Scenario annotation = clazz.getAnnotation(Scenario.class);
    if (CustomObjectUtils.isNull(annotation)) {
      throw new IllegalArgumentException();
    }

    return annotation.id();

  }

}
