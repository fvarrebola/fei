package org.ads.langs.java.maven.queries;

import org.ads.langs.java.maven.MvnClassifiers;
import org.ads.langs.java.maven.MvnPackaging;
import org.ads.langs.java.maven.SearchClause;
import org.apache.maven.index.MAVEN;

/**
 * Abstract query to return all artifacts classified as "classes".<br />
 * 
 * @author arrebola
 *
 */
public class ClassesArtifactsQuery extends AbstractQuery {

  /**
   * Constructor.<br />
   */
  public ClassesArtifactsQuery() {
    super();

    clauses.add(new SearchClause.MustOccur(MAVEN.PACKAGING, MvnPackaging.jar.name()));
    clauses.add(new SearchClause.MustOccur(MAVEN.EXTENSION, MvnPackaging.jar.extension()));
    clauses.add(new SearchClause.MustOccur(MAVEN.CLASSIFIER, MvnClassifiers.CLASSES.classifier()));
  }
}
