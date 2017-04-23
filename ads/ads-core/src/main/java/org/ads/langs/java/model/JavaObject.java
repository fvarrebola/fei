package org.ads.langs.java.model;

import org.ads.orientdb.annotations.IgnoreProperty;
import org.ads.orientdb.annotations.MyEdge;
import org.ads.orientdb.annotations.MyVertex;
import org.ads.orientdb.annotations.MyVertexIndex;
import org.ads.orientdb.annotations.MyVertexProperty;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;

import java.util.ArrayList;
import java.util.List;

/**
 * This class represents a Java object.<br />
 * 
 * @author arrebola
 *
 */
@MyVertex("JavaObject")
@MyVertexIndex(
    fields = { "name", "description" })
@MyEdge("is-part-of")
public class JavaObject {

  @IgnoreProperty
  private JavaLibrary parent;

  @MyVertexProperty
  private String name;

  @MyVertexProperty(
      mandatory = false)
  private String description;

  // @MyVertexProperty(mandatory = false, isLinkedList = true, linkedClass = JavaField.class)
  private List<JavaField> fields;

  // @MyVertexProperty(mandatory = false, isLinkedList = true, linkedClass = JavaMethod.class)
  private List<JavaMethod> methods;

  /**
   * Constructor.<br />
   */
  public JavaObject() {
    super();
    this.fields = new ArrayList<JavaField>();
    this.methods = new ArrayList<JavaMethod>();
  }

  /**
   * Constructor.<br />
   * 
   * @param parent
   *          the {@link JavaLibrary} that represents this object's parent library
   */
  public JavaObject(JavaLibrary parent) {
    this();
    Parameters.requireNonNull(parent);
    this.parent = parent;
  }

  /**
   * Constructor.<br />
   * 
   * @param name
   *          the {@link String} that represents this object's name
   * @param description
   *          the {@link String} that represents this object's description
   */
  public JavaObject(String name, String description) {
    this();
    this.name = name;
    this.description = description;
  }

  /**
   * Gets this object's parent library.<br />
   * 
   * @return the {@link JavaLibrary} that represents this object's parent library
   */
  public JavaLibrary getParent() {
    return parent;
  }

  /**
   * Sets this object's parent library.<br />
   * 
   * @param parent
   *          the {@link JavaLibrary} that represents this object's parent library
   */
  public void setParent(JavaLibrary parent) {
    this.parent = parent;
  }

  /**
   * Gets this object's name.<br />
   * 
   * @return the {@link String} that represents this object's name
   */
  public String getName() {
    return name;
  }

  /**
   * Sets this object's name.<br />
   * 
   * @param name
   *          the {@link String} that represents this object's name
   */
  public void setName(String name) {
    this.name = name;
  }

  /**
   * Gets this object's description.<br />
   * 
   * @return the {@link String} that represents this object's description
   */
  public String getDescription() {
    return description;
  }

  /**
   * Sets this object's description.<br />
   * 
   * @param description
   *          the {@link String} that represents this object's description
   */
  public void setDescription(String description) {
    this.description = description;
  }

  /**
   * Gets the list of fields of this object.<br />
   * 
   * @return the {@link List} of fields {@link JavaField}
   */
  public List<JavaField> getFields() {
    return this.fields;
  }

  /**
   * Sets the list of fields of this object.<br />
   * 
   * @param fields
   *          the {@link List} of fields {@link JavaField}
   */
  public void setFields(List<JavaField> fields) {

    Parameters.requireNonNull(fields);
    this.fields = fields;

  }

  /**
   * Adds a field to this object.<br />
   * 
   * @param field
   *          the {@link JavaField} to add
   * 
   * @return <code>true</code> if the addition was successful, <code>false</code> otherwise
   */
  public boolean addField(JavaField field) {

    Parameters.requireNonNull(field);

    return this.fields.add(field);

  }

  /**
   * Gets the list of methods of this object.<br />
   * 
   * @return the {@link List} of methods {@link JavaMethod}
   */
  public List<JavaMethod> getMethods() {
    return this.methods;
  }

  /**
   * Sets the list of methods of this object.<br />
   * 
   * @param methods
   *          the {@link List} of methods {@link JavaMethod}
   */
  public void setMethods(List<JavaMethod> methods) {

    Parameters.requireNonNull(methods);

    this.methods = methods;

  }

  /**
   * Adds a method to this object.<br />
   * 
   * @param method
   *          the {@link JavaMethod} to add
   * 
   * @return <code>true</code> if the addition was successful, <code>false</code> otherwise
   */
  public boolean addMethod(JavaMethod method) {

    Parameters.requireNonNull(method);

    return this.methods.add(method);

  }

  @Override
  public String toString() {

    return String.format(
        "JAVA_OBJECT = [\n\tname: %s\n\tdescription: %s\n\t%d field(s)\n\t%d methods\n]",
        this.name, CustomStringUtils.abbreviate(this.description),
        this.fields.size(), this.methods.size());

  }

}
