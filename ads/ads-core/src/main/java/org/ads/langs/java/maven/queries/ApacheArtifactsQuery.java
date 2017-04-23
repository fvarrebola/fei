package org.ads.langs.java.maven.queries;

import org.ads.langs.java.maven.MvnPackaging;
import org.ads.langs.java.maven.SearchClause;
import org.apache.maven.index.MAVEN;

/**
 * Query to return all artifacts containing the term <i>apache</i> in the groupId field.<br />
 * Artifacts containing terms like <i>test</i>, <i>sample</i> and <i>example</i> in the artifactId
 * field are ignored. <br />
 * 
 * @author arrebola
 *
 */
public final class ApacheArtifactsQuery extends AbstractQuery {

  /**
   * Constructor.<br />
   */
  public ApacheArtifactsQuery() {
    super();

    clauses.add(new SearchClause.MustOccur(MAVEN.PACKAGING, MvnPackaging.jar.name()));
    clauses.add(new SearchClause.MustOccur(MAVEN.EXTENSION, MvnPackaging.jar.extension()));
    clauses.add(new SearchClause.MustNotOccur(MAVEN.ARTIFACT_ID, "test", false));
    clauses.add(new SearchClause.MustNotOccur(MAVEN.ARTIFACT_ID, "sample", false));
    clauses.add(new SearchClause.MustNotOccur(MAVEN.ARTIFACT_ID, "example", false));

    clauses.add(new SearchClause.MustOccur(MAVEN.GROUP_ID, "apache", false));

  }

}
