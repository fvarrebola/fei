package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-09", 
    name = "use-apache-apis-and-ignore-method-names", 
    description = "Use Apache APIs and ignore method names")
public class UseApacheApisAndIgnoreMethodNamesScenarioImpl implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().useApacheApis().ignoreMethodNames().build();
  }

}
