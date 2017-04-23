package org.ads.langs.java.dao.impl;

public class JavaMethodSearchOptions {

  private boolean excludeKnownTestApis;
  private boolean usePopularityIndex;
  private boolean useApacheApis;
  private boolean useJdkApi;
  private boolean ignoreMethodNames;
  private boolean ignoreMethodDescriptions;

  private int limit;
  private int page;
  private int pageSize;

  public JavaMethodSearchOptions() {
    super();
  }

  public boolean isExcludeKnownTestApis() {
    return excludeKnownTestApis;
  }

  public void setExcludeKnownTestApis(boolean excludeKnownTestApis) {
    this.excludeKnownTestApis = excludeKnownTestApis;
  }

  public boolean isUsePopularityIndex() {
    return usePopularityIndex;
  }

  public void setUsePopularityIndex(boolean usePopularityIndex) {
    this.usePopularityIndex = usePopularityIndex;
  }

  public boolean isUseApacheApis() {
    return useApacheApis;
  }

  public void setUseApacheApis(boolean useApacheApis) {
    this.useApacheApis = useApacheApis;
  }

  public boolean isUseJdkApi() {
    return useJdkApi;
  }

  public void setUseJdkApi(boolean useJdkApi) {
    this.useJdkApi = useJdkApi;
  }

  public boolean isIgnoreMethodNames() {
    return ignoreMethodNames;
  }

  public void setIgnoreMethodNames(boolean ignoreMethodNames) {
    this.ignoreMethodNames = ignoreMethodNames;
  }

  public boolean isIgnoreMethodDescriptions() {
    return ignoreMethodDescriptions;
  }

  public void setIgnoreMethodDescriptions(boolean ignoreMethodDescriptions) {
    this.ignoreMethodDescriptions = ignoreMethodDescriptions;
  }

  public int getLimit() {
    return limit;
  }

  public void setLimit(int limit) {
    this.limit = limit;
  }

  public int getPage() {
    return page;
  }

  public void setPage(int page) {
    this.page = page;
  }

  public int getPageSize() {
    return pageSize;
  }

  public void setPageSize(int pageSize) {
    this.pageSize = pageSize;
  }

}
