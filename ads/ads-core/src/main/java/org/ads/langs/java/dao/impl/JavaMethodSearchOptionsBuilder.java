package org.ads.langs.java.dao.impl;

public class JavaMethodSearchOptionsBuilder {

  private JavaMethodSearchOptions options;

  public JavaMethodSearchOptionsBuilder() {
    super();
    this.options = new JavaMethodSearchOptions();
  }

  public JavaMethodSearchOptionsBuilder excludeKnownTestApis() {
    this.options.setExcludeKnownTestApis(true);
    return this;
  }

  public JavaMethodSearchOptionsBuilder ignoreMethodDescriptions() {
    this.options.setIgnoreMethodDescriptions(true);
    return this;
  }

  public JavaMethodSearchOptionsBuilder ignoreMethodNames() {
    this.options.setIgnoreMethodNames(true);
    return this;
  }

  public JavaMethodSearchOptionsBuilder usePopularityIndex() {
    this.options.setUsePopularityIndex(true);
    return this;
  }

  public JavaMethodSearchOptionsBuilder useJdkApi() {
    this.options.setUseJdkApi(true);
    return this;
  }

  public JavaMethodSearchOptionsBuilder useApacheApis() {
    this.options.setUseApacheApis(true);
    return this;
  }

  public JavaMethodSearchOptions build() {
    return this.options;
  }

}
