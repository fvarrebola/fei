package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-08", 
    name = "use-apache-apis-and-ignore-mehod-descriptions", 
    description = "Use Apache APIs and ignore method descriptions")
public class UseApacheApisAndIgnoreMethodDescriptionsScenarioImpl
    implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().useApacheApis().ignoreMethodDescriptions().build();
  }

}
