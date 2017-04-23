package org.ads.langs.java.maven;

public enum MvnClassifiers {

    EMPTY(""), 
    JAVADOC("javadoc"), 
    SOURCES("sources"), 
    CONFIG("config"), 
    TESTS("tests"),
    APP("app"),
    BUNDLE("bundle"),
    CLASSES("classes"),
    CLI("cli"),
    FACELETS_TLDDOC("facelets-tlddoc"),
    H2("h2"),
    HADOOP20("hadoop20"),
    HADOOP020("hadoop020"),
    HADOOP23("hadoop23"),
    HADOOP023("hadoop023"),
    HADOOP1("hadoop1"),
    HADOOP100("hadoop100"),
    HADOOP2("hadoop2"),
    HADOOP200("hadoop200"),
    JAR_WITH_DEPENDENCIES("jar-with-dependencies"),
    JDK14RETRO("jdk14retro"),
    JOB("job"),
    NODEPS("nodeps"),
    SCALADOC("scaladoc"),
    SERVER("server"),
    SHADED("shaded"),
    SOURCE("source"),
    TEST_JAVADOC("test-javadoc"),
    TEST_SOURCES("test-sources"),
    TLDDOC("tlddoc"),
    TOMCAT_SOURCES("tomcat-sources"),
    TOMCAT("tomcat"),
    UBER("uber");

  private final String classifier;

  /**
   * Constructor.<br />
   * 
   * @param classifier
   *          the {@link String} that represents the classifier
   */
  private MvnClassifiers(String classifier) {
    this.classifier = classifier;
  }

  /**
   * Returns the classifier of this enum.<br />
   * 
   * @return the {@link String} that represents the classifier
   */
  public String classifier() {
    return this.classifier;
  }

}
