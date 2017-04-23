package org.ads.langs.java.model;

import org.ads.orientdb.annotations.MyEdge;
import org.ads.orientdb.annotations.MyVertex;
import org.ads.orientdb.annotations.MyVertexIndex;
import org.ads.orientdb.annotations.MyVertexProperty;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;

import java.util.ArrayList;
import java.util.List;

/**
 * This class represents a Java object field.<br />
 * 
 * @author arrebola
 *
 * @see JavaObject
 */
@MyVertex("JavaField")
@MyVertexIndex(fields = { "name", "description" })
@MyEdge("is-part-of")
public class JavaField {

  @MyVertexProperty
  private String name;

  @MyVertexProperty
  private String signature;

  @MyVertexProperty(mandatory = false)
  private String description;

  @MyVertexProperty
  private JavaType type;

  private List<JavaModifier> modifiers;

  /**
   * Constructor.<br />
   */
  public JavaField() {
    super();
    this.modifiers = new ArrayList<JavaModifier>();
  }

  /**
   * Constructor.<br />
   * 
   * @param name
   *          the {@link String} that represents this field's name
   * @param signature
   *          the {@link String} that represents this field's signature
   * @param description
   *          the {@link String} that represents this field's description
   */
  public JavaField(String name, String signature, String description) {
    this();
    this.name = name;
    this.signature = signature;
    this.description = description;
  }

  /**
   * Gets this field's name.<br />
   * 
   * @return the {@link String} that represents this field's name
   */
  public String getName() {
    return name;
  }

  /**
   * Sets this field's name.<br />
   * 
   * @param name
   *          the {@link String} that represents this field's name
   */
  public void setName(String name) {
    this.name = name;
  }

  /**
   * Gets this field's signature.<br />
   * 
   * @return the {@link String} that represents this field's signature
   */
  public String getSignature() {
    return signature;
  }

  /**
   * Sets this field's description.<br />
   * 
   * @param signature
   *          the {@link String} that represents this field's signature
   */
  public void setSignature(String signature) {
    this.signature = signature;
  }

  /**
   * Gets this field's description.<br />
   * 
   * @return the {@link String} that represents this field's description
   */
  public String getDescription() {
    return description;
  }

  /**
   * Sets this field's description.<br />
   * 
   * @param description
   *          the {@link String} that represents this field's description
   */
  public void setDescription(String description) {
    this.description = description;
  }

  /**
   * Gets this field's type.<br />
   * 
   * @return the {@link JavaType} that represents this field's type
   */
  public JavaType getType() {
    return type;
  }

  /**
   * Sets this field's type.<br />
   * 
   * @param type
   *          the {@link JavaType} that represents this field's type
   */
  public void setType(JavaType type) {

    Parameters.requireNonNull(type);

    this.type = type;
  }

  /**
   * Gets the list of modifiers of this field.<br />
   * 
   * @return the {@link List} of modifiers {@link JavaModifier}
   */
  public List<JavaModifier> getModifiers() {
    return modifiers;
  }

  /**
   * Sets the list of modifiers of this field.<br />
   * 
   * @param modifiers
   *          the {@link List} of modifiers {@link JavaModifier}
   */
  public void setModifiers(List<JavaModifier> modifiers) {

    Parameters.requireNonNull(modifiers);

    this.modifiers = modifiers;
  }

  /**
   * Adds a modifier to this field.<br />
   * 
   * @param modifier
   *          the {@link JavaModifier} to add
   * 
   * @return <code>true</code> if the addition was successful, <code>false</code> otherwise
   */
  public boolean addModifier(JavaModifier modifier) {

    Parameters.requireNonNull(modifier);

    return this.modifiers.add(modifier);

  }

  @Override
  public String toString() {

    StringBuilder builder = new StringBuilder();
    builder.append("JAVA_FIELD = [\n\tname: ").append(this.name);
    builder.append("\n\ttype: ").append(this.type);
    builder.append("\n\tdescription: ").append(CustomStringUtils.abbreviate(this.description));
    builder.append("\n]");

    return builder.toString();

  }
}
