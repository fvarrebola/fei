package org.ads.scenarios.java.impl;

import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptionsBuilder;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;

@Scenario(
    id = "S-17", 
    name = "use-popularity-index-and-ignore-method-descriptions", 
    description = "Use popularity index and ignore method descriptions")
public class UsePopularityIndexAndIgnoreMethodDescriptionsScenarioImpl
    implements JavaMethodSearchScenario {

  @Override
  public JavaMethodSearchOptions getOptions() {
    return new JavaMethodSearchOptionsBuilder().usePopularityIndex().ignoreMethodDescriptions()
        .build();
  }

}
