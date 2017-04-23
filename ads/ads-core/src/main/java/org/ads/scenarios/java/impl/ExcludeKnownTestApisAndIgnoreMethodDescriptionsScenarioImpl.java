package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-02", 
    name = "exclude-known-test-apis-and-ignore-method-descriptions", 
    description = "Exclude known test APIs and ignore method descriptions")
public class ExcludeKnownTestApisAndIgnoreMethodDescriptionsScenarioImpl
    implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().excludeKnownTestApis().ignoreMethodDescriptions()
        .build();
  }

}
