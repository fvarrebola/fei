package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-18", 
    name = "use-popularity-index-and-ignore-method-names", 
    description = "Use popularity index and ignore method names")
public class UsePopularityIndexAndIgnoreMethodNamesScenarioImpl
    implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().usePopularityIndex().ignoreMethodNames().build();
  }

}
