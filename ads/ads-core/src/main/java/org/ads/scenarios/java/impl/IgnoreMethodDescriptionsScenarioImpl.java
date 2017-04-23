package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-06", 
    name = "ignore-method-descriptions", 
    description = "Ignore method descriptions")
public class IgnoreMethodDescriptionsScenarioImpl implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().ignoreMethodDescriptions().build();
  }

}
