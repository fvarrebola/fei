package org.ads.langs.java.maven.queries;

import org.ads.langs.java.maven.SearchClause;

import java.util.HashSet;
import java.util.Set;

/**
 * Abstract query.<br />
 * 
 * @author arrebola
 *
 */
public abstract class AbstractQuery implements Query {

  protected Set<SearchClause> clauses;

  /**
   * Constructor.<br />
   */
  public AbstractQuery() {
    super();
    this.clauses = new HashSet<SearchClause>();
  }

  /**
   * Gets the search clauses.<br />
   * 
   * @return the {@link Set} of {@link SearchClause} search clauses
   */
  public final Set<SearchClause> getClauses() {
    return this.clauses;
  }
}
