package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-11", 
    name = "use-apache-apis-and-popularity-index-and-ignore-method-names", 
    description = "Use Apache APIs, popularity index and ignore method names")
public class UseApacheApisAndPopularityIndexAndIgnoreMethodNamesScenarioImpl
    implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().useApacheApis().usePopularityIndex()
        .ignoreMethodNames().build();
  }

}
