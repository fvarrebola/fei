package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-14", 
    name = "use-jdk-api-and-ignore-method-descriptions", 
    description = "Use JDK APIs and ignore method descriptions")
public class UseJdkApisAndIgnoreMethodDescriptionsScenarioImpl implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().ignoreMethodDescriptions().useJdkApi().build();
  }

}
