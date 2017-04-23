package org.ads.scenarios.java;

import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.impl.DefaultSearchScenarioImpl;
import org.ads.scenarios.java.impl.ExcludeKnownTestApisAndIgnoreMethodDescriptionsScenarioImpl;
import org.ads.scenarios.java.impl.ExcludeKnownTestApisAndIgnoreMethodNamesScenarioImpl;
import org.ads.scenarios.java.impl.ExcludeKnownTestApisAndUsePopularityIndexScenarioImpl;
import org.ads.scenarios.java.impl.ExcludeKnownTestApisScenarioImpl;
import org.ads.scenarios.java.impl.IgnoreMethodDescriptionsScenarioImpl;
import org.ads.scenarios.java.impl.IgnoreMethodNamesScenarioImpl;
import org.ads.scenarios.java.impl.UseApacheApisAndIgnoreMethodDescriptionsScenarioImpl;
import org.ads.scenarios.java.impl.UseApacheApisAndIgnoreMethodNamesScenarioImpl;
import org.ads.scenarios.java.impl.UseApacheApisAndPopularityIndexAndIgnoreMethodDescriptionsScenarioImpl;
import org.ads.scenarios.java.impl.UseApacheApisAndPopularityIndexAndIgnoreMethodNamesScenarioImpl;
import org.ads.scenarios.java.impl.UseApacheApisAndPopularityIndexScenarioImpl;
import org.ads.scenarios.java.impl.UseApacheApisScenarioImpl;
import org.ads.scenarios.java.impl.UseJdkApisAndIgnoreMethodDescriptionsScenarioImpl;
import org.ads.scenarios.java.impl.UseJdkApisAndIgnoreMethodNamesScenarioImpl;
import org.ads.scenarios.java.impl.UseJdkApisScenarioImpl;
import org.ads.scenarios.java.impl.UsePopularityIndexAndIgnoreMethodDescriptionsScenarioImpl;
import org.ads.scenarios.java.impl.UsePopularityIndexAndIgnoreMethodNamesScenarioImpl;
import org.ads.scenarios.java.impl.UsePopularityIndexScenarioImpl;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.ObjectFactory;

public class JavaMethodSearchScenarioFactory extends ObjectFactory<JavaMethodSearchScenario> {

  @Override
  protected void doInitialize() {
    register(DefaultSearchScenarioImpl.class);
    register(ExcludeKnownTestApisAndIgnoreMethodDescriptionsScenarioImpl.class);
    register(ExcludeKnownTestApisAndIgnoreMethodNamesScenarioImpl.class);
    register(ExcludeKnownTestApisAndUsePopularityIndexScenarioImpl.class);
    register(ExcludeKnownTestApisScenarioImpl.class);
    register(IgnoreMethodDescriptionsScenarioImpl.class);
    register(IgnoreMethodNamesScenarioImpl.class);
    register(UseApacheApisAndIgnoreMethodDescriptionsScenarioImpl.class);
    register(UseApacheApisAndIgnoreMethodNamesScenarioImpl.class);
    register(UseApacheApisAndPopularityIndexAndIgnoreMethodDescriptionsScenarioImpl.class);
    register(UseApacheApisAndPopularityIndexAndIgnoreMethodNamesScenarioImpl.class);
    register(UseApacheApisAndPopularityIndexScenarioImpl.class);
    register(UseApacheApisScenarioImpl.class);
    register(UseJdkApisAndIgnoreMethodDescriptionsScenarioImpl.class);
    register(UseJdkApisAndIgnoreMethodNamesScenarioImpl.class);
    register(UseJdkApisScenarioImpl.class);
    register(UsePopularityIndexAndIgnoreMethodDescriptionsScenarioImpl.class);
    register(UsePopularityIndexAndIgnoreMethodNamesScenarioImpl.class);
    register(UsePopularityIndexScenarioImpl.class);
  }

  @Override
  protected String doGetClassKey(Class<? extends JavaMethodSearchScenario> clazz) {

    final Scenario annotation = clazz.getAnnotation(Scenario.class);
    if (CustomObjectUtils.isNull(annotation)) {
      throw new IllegalArgumentException();
    }

    return annotation.id();

  }

}
