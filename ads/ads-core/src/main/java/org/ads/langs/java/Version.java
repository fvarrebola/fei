package org.ads.langs.java;

import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;

/**
 * Enum of java versions.<br />
 * 
 * @author arrebola
 *
 */
public enum Version {

    UNDEFINED("?"),
    V_1_0("1.0"), 
    V_1_1("1.1"), 
    V_1_2("1.2"), 
    V_1_3("1.3"), 
    V_1_4("1.4"), 
    V_1_5("1.5"), 
    V_1_6("1.6"), 
    V_1_7("1.7"), 
    V_1_8("1.8");

  private String version;

  /**
   * Constructor.<br />
   * 
   * @param version
   *          {@link String} that represents the version
   */
  Version(String version) {
    this.version = version;
  }

  /**
   * Parses a version.<br />
   * 
   * @param versionAsString
   *          {@link String} that represents the version to be parsed
   * @return the {@link Version}
   */
  public static Version parse(String versionAsString) {

    Parameters.requireNonEmpty(versionAsString);

    final int length = Version.values().length;
    for (int idx = 0; idx < length; idx++) {
      Version version = Version.values()[idx];
      if (CustomStringUtils.equals(versionAsString, version.version)) {
        return version;
      }
    }

    throw new IllegalArgumentException("Unknown version '" + versionAsString + "'.");

  }

}
