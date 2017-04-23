package org.ads.langs.java.maven.queries;

import org.ads.langs.java.maven.MvnClassifiers;
import org.ads.langs.java.maven.MvnPackaging;
import org.ads.langs.java.maven.SearchClause;
import org.apache.maven.index.MAVEN;

/**
 * Query to search for javadoc artifacts only.<br />
 * 
 * @author arrebola
 *
 */
public class JavadocArtifactsQuery extends AbstractQuery {

  /**
   * Constructor.<br />
   */
  public JavadocArtifactsQuery() {
    super();
    clauses.add(new SearchClause.MustOccur(MAVEN.PACKAGING, MvnPackaging.jar.name()));
    clauses.add(new SearchClause.MustOccur(MAVEN.EXTENSION, MvnPackaging.jar.extension()));
    clauses.add(new SearchClause.MustOccur(MAVEN.CLASSIFIER, MvnClassifiers.JAVADOC.classifier()));
  }

}
