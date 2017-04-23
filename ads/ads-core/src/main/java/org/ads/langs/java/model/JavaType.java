package org.ads.langs.java.model;

import org.ads.utils.CustomStringUtils;

/**
 * This class represents a Java type.<br />
 * 
 * @author arrebola
 *
 */
public class JavaType {

  private String name;
  private String description;

  /**
   * Constructor.<br />
   */
  public JavaType() {
    super();
  }

  /**
   * Csontructor.<br />
   * 
   * @param name
   *          the {@link String} that represents this Java type's name
   * @param description
   *          the {@link String} that represents this Java type's description
   */
  public JavaType(String name, String description) {
    super();
  }

  /**
   * Gets this Java type's name.<br />
   * 
   * @return the {@link String} that represents this Java type's name
   */
  public String getName() {
    return name;
  }

  /**
   * Sets this Java type's name.<br />
   * 
   * @param name
   *          the {@link String} that represents this Java type's name
   */
  public void setName(String name) {
    this.name = name;
  }

  /**
   * Gets this Java type's description.<br />
   * 
   * @return the {@link String} that represents this Java type's description
   */
  public String getDescription() {
    return this.description;
  }

  /**
   * Sets this Java type's description.<br />
   * 
   * @param description
   *          the {@link String} that represents this Java type's description
   */
  public void setDescription(String description) {
    this.description = description;
  }

  @Override
  public String toString() {

    StringBuilder builder = new StringBuilder();
    builder.append("[name: ").append(this.name);
    builder.append(", description: ").append(CustomStringUtils.isNotEmpty(this.description)
        ? CustomStringUtils.abbreviate(this.description) : CustomStringUtils.NA);
    builder.append("]");

    return builder.toString();

  }

}
