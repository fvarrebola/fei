package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-03", 
    name = "exclude-known-test-apis-and-ignore-method-names", 
    description = "Exclude known test APIs and ignore method names")
public class ExcludeKnownTestApisAndIgnoreMethodNamesScenarioImpl
    implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().excludeKnownTestApis().ignoreMethodNames().build();
  }

}
