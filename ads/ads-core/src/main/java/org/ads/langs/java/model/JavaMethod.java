package org.ads.langs.java.model;

import org.ads.orientdb.annotations.IgnoreProperty;
import org.ads.orientdb.annotations.MyEdge;
import org.ads.orientdb.annotations.MyVertex;
import org.ads.orientdb.annotations.MyVertexIndex;
import org.ads.orientdb.annotations.MyVertexProperty;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;

import java.util.ArrayList;
import java.util.List;

@MyVertex("JavaMethod")
@MyVertexIndex(fields = { "name", "description" })
@MyEdge("is-part-of")
public class JavaMethod {

  @IgnoreProperty
  private String library;

  @IgnoreProperty
  private String object;

  @IgnoreProperty
  private JavaObject parent;

  @MyVertexProperty
  private String name;

  @MyVertexProperty(mandatory = false)
  private String signature;

  @MyVertexProperty(mandatory = false)
  private String description;

  // @MyVertexProperty
  private JavaType returnType;

  @MyVertexProperty(mandatory = false, isLinkedList = true, linkedClass = JavaParameter.class)
  private List<JavaParameter> parameters;

  /**
   * Constructor.<br />
   */
  public JavaMethod() {
    super();
  }

  /**
   * Constructor.<br />
   * 
   * @param parent
   *          the {@link JavaObject} that represents this method's parent object
   */
  public JavaMethod(JavaObject parent) {
    this();
    Parameters.requireNonNull(parent);
    this.parent = parent;
  }

  /**
   * Constructor.<br />
   */
  public JavaMethod(String name, String signature, String description) {
    this();
    this.name = name;
    this.signature = signature;
    this.description = description;
  }

  /**
   * Gets this method's parent library.<br />
   * 
   * @return the {@link JavaObject} that represents this method's parent library
   */
  public String getLibrary() {
    return library;
  }

  /**
   * Sets this method's parent library name.<br />
   * 
   * @param library
   *          the {@link String} that represents this method's parent library name
   */
  public void setLibrary(String library) {
    this.library = library;
  }

  /**
   * Gets this method's parent object name.<br />
   * 
   * @return the {@link String} that represents this method's parent object name
   */
  public String getObject() {
    return object;
  }

  /**
   * Sets this method's parent object name.<br />
   * 
   * @param object
   *          the {@link String} that represents this method's parent object name
   */
  public void setObject(String object) {
    this.object = object;
  }

  /**
   * Gets this method's parent object.<br />
   * 
   * @return the {@link JavaObject} that represents this method's parent object
   */
  public JavaObject getParent() {
    return parent;
  }

  /**
   * Sets this method's parent object.<br />
   * 
   * @param parent
   *          the {@link JavaObject} that represents this method's parent object
   */
  public void setParent(JavaObject parent) {
    this.parent = parent;
  }

  /**
   * Gets this method's name.<br />
   * 
   * @return the {@link String} that represents this method's name
   */
  public String getName() {
    return name;
  }

  /**
   * Sets this method's name.<br />
   * 
   * @param name
   *          the {@link String} that represents this method's name
   */
  public void setName(String name) {
    this.name = name;
  }

  /**
   * Gets this method's signature.<br />
   * 
   * @return the {@link String} that represents this method's signature
   */
  public String getSignature() {
    return signature;
  }

  /**
   * Sets this method's description.<br />
   * 
   * @param signature
   *          the {@link String} that represents this method's signature
   */
  public void setSignature(String signature) {
    this.signature = signature;
  }

  /**
   * Gets this method's description.<br />
   * 
   * @return the {@link String} that represents this method's description
   */
  public String getDescription() {
    return description;
  }

  /**
   * Sets this method's description.<br />
   * 
   * @param description
   *          the {@link String} that represents this method's description
   */
  public void setDescription(String description) {
    this.description = description;
  }

  /**
   * Gets this method's return type.<br />
   * 
   * @return the {@link JavaType} that represents this method's return type
   */
  public JavaType getReturnType() {
    return returnType;
  }

  /**
   * Sets this method's return type.<br />
   * 
   * @param returnType
   *          the {@link JavaType} that represents this method's return type
   */
  public void setReturnType(JavaType returnType) {

    Parameters.requireNonNull(returnType);

    this.returnType = returnType;

  }

  /**
   * Gets the list of parameters of this method.<br />
   * 
   * @return the {@link List} of fields {@link JavaParameter}
   */
  public List<JavaParameter> getParameters() {
    return parameters;
  }

  /**
   * Sets the list of parameters of this method.<br />
   * 
   * @param parameters
   *          the {@link List} of fields {@link JavaParameter}
   */
  public void setParameters(List<JavaParameter> parameters) {

    Parameters.requireNonNull(parameters);

    this.parameters = parameters;

  }

  /**
   * Adds a parameter to this method.<br />
   * 
   * @param parameter
   *          the {@link JavaParameter} to add
   * 
   * @return <code>true</code> if the addition was successful, <code>false</code> otherwise
   */
  public boolean addParameter(JavaParameter parameter) {

    Parameters.requireNonNull(parameter);

    if (CustomObjectUtils.isNull(this.parameters)) {
      this.parameters = new ArrayList<JavaParameter>();
    }

    return this.parameters.add(parameter);

  }

  @Override
  public String toString() {

    StringBuilder builder = new StringBuilder();

    builder.append("[library: ").append(this.library);
    builder.append(", object: ").append(this.object);
    builder.append(", name: ").append(this.name);
    builder.append(", signature: ").append(this.signature);
    builder.append(", description: ").append(CustomStringUtils.abbreviate(this.description));
    builder.append("]");

    return builder.toString();
  }

}
