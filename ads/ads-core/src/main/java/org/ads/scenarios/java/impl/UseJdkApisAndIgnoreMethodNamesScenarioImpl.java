package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-15", 
    name = "use-jdk-api-and-ignore-method-names", 
    description = "Use JDK APIs and ignore method names")
public class UseJdkApisAndIgnoreMethodNamesScenarioImpl implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().ignoreMethodNames().useJdkApi().build();
  }

}
