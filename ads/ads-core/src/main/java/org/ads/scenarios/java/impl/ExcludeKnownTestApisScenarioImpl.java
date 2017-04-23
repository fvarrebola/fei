package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(id = "S-05", name = "exclude-known-test-apis", description = "Exclude known test APIs")
public class ExcludeKnownTestApisScenarioImpl implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().excludeKnownTestApis().build();
  }

}
