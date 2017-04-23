package org.ads.langs.java.model;

import org.ads.orientdb.annotations.MyEdge;
import org.ads.orientdb.annotations.MyVertex;
import org.ads.orientdb.annotations.MyVertexProperty;
import org.ads.orientdb.annotations.MyVertexUid;
import org.ads.utils.Parameters;

import java.util.ArrayList;
import java.util.List;

/**
 * This class represents a Java package.<br />
 * 
 * @author arrebola
 *
 */
@MyVertex("JavaPackage")
@MyEdge("is-part-of")
public class JavaPackage {

  @MyVertexUid("JavaPackage.fqn")
  @MyVertexProperty
  private String fqn;

  @MyVertexProperty
  private String name;

  @MyVertexProperty
  private String description;

  private List<JavaObject> objects;

  /**
   * Constructor.<br />
   */
  public JavaPackage() {
    super();
    this.objects = new ArrayList<JavaObject>();
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public String getDescription() {
    return description;
  }

  public void setDescription(String description) {
    this.description = description;
  }

  /**
   * Gets the list of objects of this package.<br />
   * 
   * @return the {@link List} of objects {@link JavaObject}
   */
  public List<JavaObject> getObjects() {
    return this.objects;
  }

  /**
   * Sets the list of objects.<br />
   * 
   * @param objects
   *          the {@link List} of objects {@link JavaObject}
   */
  public void setClasses(List<JavaObject> objects) {

    Parameters.requireNonNull(objects);

    this.objects = objects;
  }

  /**
   * Adds a objects to this package.<br />
   * 
   * @param object
   *          the {@link JavaObject} to add
   * 
   * @return <code>true</code> if the addition was successful, <code>false</code> otherwise
   */
  public boolean addClass(JavaObject object) {

    Parameters.requireNonNull(object);

    return this.objects.add(object);

  }

}
