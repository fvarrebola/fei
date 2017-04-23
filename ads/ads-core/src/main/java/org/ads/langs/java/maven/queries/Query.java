package org.ads.langs.java.maven.queries;

import org.ads.langs.java.maven.SearchClause;

import java.util.Set;

public interface Query {

  public abstract Set<SearchClause> getClauses();

}
