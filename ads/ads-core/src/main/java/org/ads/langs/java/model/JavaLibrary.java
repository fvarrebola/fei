package org.ads.langs.java.model;

import org.ads.AbstractLibrary;
import org.ads.orientdb.annotations.MyEdge;
import org.ads.orientdb.annotations.MyVertex;
import org.ads.orientdb.annotations.MyVertexProperty;
import org.ads.orientdb.annotations.MyVertexUid;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;

import java.util.ArrayList;
import java.util.List;

/**
 * This class represents a Java library.<br />
 * 
 * @author arrebola
 *
 */
@MyVertex("JavaLibrary")
@MyEdge("depends")
public class JavaLibrary extends AbstractLibrary {

  @MyVertexUid("JavaLibrary.fqn")
  @MyVertexProperty
  private String fqn;

  @MyVertexProperty
  private String groupId;

  @MyVertexProperty
  private String artifactId;

  @MyVertexProperty
  private String version;

  @MyVertexProperty
  private String packaging;

  @MyVertexProperty(mandatory = false, allowNull = true)
  private String classifier;

  @MyVertexProperty
  private String extension;

  @MyVertexProperty(mandatory = false, allowNull = true)
  private String scope;

  private String sourceExists;

  private String javadocExists;

  private Long lastModified;

  private Float popularityIndex;

  private List<JavaLibrary> dependencies;

  /**
   * Private constructor.<br />
   */
  public JavaLibrary() {
    super();
  }

  /**
   * Builds the artifact name and sets it to the FQN property.<br />
   */
  public void buildName() {
    Parameters.requireNonNull(this.groupId, this.artifactId, this.version);
    this.fqn = String.format("%s-%s-%s", this.groupId, this.artifactId, this.version);

  }

  public String getFqn() {
    return this.fqn;
  }

  public void setFqn(String fqn) {
    this.fqn = fqn;
  }

  public String getGroupId() {
    return this.groupId;
  }

  public void setGroupId(String groupId) {
    this.groupId = groupId;
  }

  public String getArtifactId() {
    return this.artifactId;
  }

  public void setArtifactId(String artifactId) {
    this.artifactId = artifactId;
  }

  public String getVersion() {
    return this.version;
  }

  public void setVersion(String version) {
    this.version = version;
  }

  public String getClassifier() {
    return classifier;
  }

  public void setClassifier(String classifier) {
    this.classifier = classifier;
  }

  public String getPackaging() {
    return this.packaging;
  }

  public void setPackaging(String packaging) {
    this.packaging = packaging;
  }

  public String getExtension() {
    return extension;
  }

  public void setExtension(String extension) {
    this.extension = extension;
  }

  public String getScope() {
    return scope;
  }

  public void setScope(String scope) {
    this.scope = scope;
  }

  public String getSourceExists() {
    return sourceExists;
  }

  public void setSourceExists(String sourceExists) {
    this.sourceExists = sourceExists;
  }

  public String getJavadocExists() {
    return javadocExists;
  }

  public void setJavadocExists(String javadocExists) {
    this.javadocExists = javadocExists;
  }

  public Long getLastModified() {
    return lastModified;
  }

  public Float getPopularityIndex() {
    return popularityIndex;
  }

  public void setPopularityIndex(Float popularityIndex) {
    this.popularityIndex = popularityIndex;
  }

  public void setLastModified(Long lastModified) {
    this.lastModified = lastModified;
  }

  public List<JavaLibrary> getDependencies() {
    return this.dependencies;
  }

  /**
   * Sets this library dependencies.<br />
   * 
   * @param dependencies
   *          the {@link List} of {@link JavaLibrary} that represents this library's dependencies
   */
  public void setDependencies(List<JavaLibrary> dependencies) {

    Parameters.requireNonNull(dependencies);

    this.dependencies = dependencies;
  }

  /**
   * Adds a dependency.<br />
   * 
   * @param dependency
   *          the {@link JavaLibrary} that represents a dependency
   *          
   * @return <code>true</code> if the operation is successful, <code>false</code> otherwise
   */
  public boolean addDependency(JavaLibrary dependency) {

    Parameters.requireNonNull(dependency);

    if (CustomObjectUtils.isNull(this.dependencies)) {
      this.dependencies = new ArrayList<JavaLibrary>();
    }

    return this.dependencies.add(dependency);
  }

  @Override
  public String toString() {

    StringBuilder builder = new StringBuilder();

    builder.append("\nArtifact: ");
    if (CustomStringUtils.isEmpty(this.fqn)) {
      builder.append(String.format("%s-%s-%s", this.groupId, this.artifactId, this.version));
    } else {
      builder.append(String.format("%s\n", this.fqn));
    }

    return builder.toString();

  }

}
