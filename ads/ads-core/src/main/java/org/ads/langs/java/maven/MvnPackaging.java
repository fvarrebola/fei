package org.ads.langs.java.maven;

public enum MvnPackaging {

  jar("jar"), pom("xml");

  private String extension;

  private MvnPackaging(String extension) {
    this.extension = extension;
  }

  public String extension() {
    return this.extension;
  }
}
