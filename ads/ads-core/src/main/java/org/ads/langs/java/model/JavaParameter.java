package org.ads.langs.java.model;

import org.ads.orientdb.annotations.MyEdge;
import org.ads.orientdb.annotations.MyVertex;
import org.ads.orientdb.annotations.MyVertexProperty;
import org.ads.utils.CustomStringUtils;

/**
 * This class represents a Java method parameter.<br />
 * 
 * @author arrebola
 *
 * @see JavaMethod
 */
@MyVertex("JavaParameter")
@MyEdge("is-part-of")
public class JavaParameter {

  @MyVertexProperty
  private String name;

  @MyVertexProperty(mandatory = false)
  private String description;

  private JavaType type;

  /**
   * Constructor.<br />
   */
  public JavaParameter() {
    super();
  }

  /**
   * Constructor.<br />
   * 
   * @param name
   *          the {@link String} that represents this parameter's name
   * @param description
   *          the {@link String} that represents this parameter's description
   */
  public JavaParameter(String name, String description) {
    this();
    this.name = name;
    this.description = description;
  }

  /**
   * Gets this parameter's name.<br />
   * 
   * @return the {@link String} that represents this parameter's name
   */
  public String getName() {
    return name;
  }

  /**
   * Sets this parameter's name.<br />
   * 
   * @param name
   *          the {@link String} that represents this parameter's name
   */
  public void setName(String name) {
    this.name = name;
  }

  /**
   * Gets this parameter's description.<br />
   * 
   * @return the {@link String} that represents this parameter's description
   */
  public String getDescription() {
    return description;
  }

  /**
   * Sets this parameter's description.<br />
   * 
   * @param description
   *          the {@link String} that represents this parameter's description
   */
  public void setDescription(String description) {
    this.description = description;
  }

  /**
   * Gets this parameter's type.<br />
   * 
   * @return the {@link JavaType} that represents this parameter's type
   */
  public JavaType getType() {
    return type;
  }

  /**
   * Sets this parameter's type.<br />
   * 
   * @param type
   *          the {@link JavaType} that represents this parameter's type
   */
  public void setType(JavaType type) {
    this.type = type;
  }

  @Override
  public String toString() {

    StringBuilder builder = new StringBuilder();
    builder.append("JAVA_PARAMETER = [\n\tname: ").append(this.name);
    builder.append("\n\tdescription: ").append(CustomStringUtils.abbreviate(this.description));
    builder.append("\n]");

    return builder.toString();

  }
}
