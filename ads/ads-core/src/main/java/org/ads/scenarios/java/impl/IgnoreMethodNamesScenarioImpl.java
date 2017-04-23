package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(id = "S-07", name = "ignore-method-names", description = "Ignore method names")
public class IgnoreMethodNamesScenarioImpl implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().ignoreMethodNames().build();
  }

}
