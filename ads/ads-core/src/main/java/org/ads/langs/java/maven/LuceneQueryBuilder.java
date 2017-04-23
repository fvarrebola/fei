package org.ads.langs.java.maven;

import org.ads.langs.java.maven.queries.Query;
import org.ads.utils.Parameters;
import org.apache.lucene.search.BooleanQuery;
import org.apache.maven.index.Indexer;

import java.util.Objects;
import java.util.function.Consumer;

/**
 * Helper class to build Lucene queries.<br />
 * 
 * @author arrebola
 *
 */
public final class LuceneQueryBuilder {

  private Indexer indexer;
  private BooleanQuery query;

  /**
   * Private constructor.<br />
   */
  private LuceneQueryBuilder() {
    super();
  }

  /**
   * Constructor.<br />
   * 
   * @param indexer
   *          {@link Indexer} that represents the Maven indexer component
   */
  public LuceneQueryBuilder(Indexer indexer) {

    this();

    Parameters.requireNonNull(indexer);

    this.indexer = indexer;
    this.query = new BooleanQuery();

  }

  /**
   * Adds a search clause to the underlying query.<br />
   * 
   * @return {@link LuceneQueryBuilder} that represents the query builder
   */
  public LuceneQueryBuilder add(SearchClause clause) {

    Parameters.requireNonNull(clause);

    this.query.add(this.indexer.constructQuery(clause.getField(), clause.getExpression()),
        clause.getOccur());

    return this;

  }

  /**
   * Adds all search clauses to the underlying query.<br />
   * 
   * @param clauses
   *          the clauses to be added
   * 
   * @return {@link LuceneQueryBuilder} that represents the query builder
   */
  public LuceneQueryBuilder add(SearchClause... clauses) {

    Objects.requireNonNull(clauses);

    for (SearchClause clause : clauses) {
      add(clause);
    }

    return this;

  }

  /**
   * Adds all search clauses to the underlying query.<br />
   * 
   * @param query
   *          the {@link Query} that wraps the search clauses to be added
   * 
   * @return {@link LuceneQueryBuilder} that represents the query builder
   */
  public LuceneQueryBuilder add(Query query) {

    Parameters.requireNonNull(query);

    query.getClauses().forEach(new Consumer<SearchClause>() {
      @Override
      public void accept(SearchClause clause) {
        add(clause);
      }
    });

    return this;

  }

  /**
   * Gets the query.<br />
   * 
   * @return the {@link BooleanQuery} that represents the query
   */
  public BooleanQuery getQuery() {
    return query;
  }

}
