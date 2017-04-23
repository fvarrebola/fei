package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-04", 
    name = "exclude-known-test-apis-and-use-popularity-index", 
    description = "Exclude known test APIs and use popularity index")
public class ExcludeKnownTestApisAndUsePopularityIndexScenarioImpl
    implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().excludeKnownTestApis().usePopularityIndex().build();
  }

}
