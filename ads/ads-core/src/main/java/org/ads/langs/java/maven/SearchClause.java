package org.ads.langs.java.maven;

import org.ads.utils.Parameters;
import org.apache.lucene.search.BooleanClause.Occur;
import org.apache.maven.index.Field;
import org.apache.maven.index.SearchType;
import org.apache.maven.index.expr.SearchExpression;
import org.apache.maven.index.expr.SearchTypedStringSearchExpression;

/**
 * An astract search clause.<br />
 * 
 * @author arrebola
 *
 */
public abstract class SearchClause {

  private Field field;
  private SearchExpression expression;
  private boolean exact;
  private Occur occur;

  /**
   * Constructor.<br />
   * 
   * @param field
   *          the {@link Field} that represents the index field
   * @param term
   *          the {@link String} that represents the term
   * @param exact
   *          <code>true</code> indicates to use exact searches, <code>false</code> indicates
   *          "scored" searches
   * @param occur
   *          the {@link Occur} that represents how a clause are to occur in documents
   */
  public SearchClause(Field field, String term, boolean exact, Occur occur) {
    super();

    Parameters.requireNonNull(field, term, occur);

    this.field = field;
    this.expression = new SearchTypedStringSearchExpression(term,
        (exact ? SearchType.EXACT : SearchType.SCORED));
    this.exact = exact;
    this.occur = occur;

  }

  public Field getField() {
    return field;
  }

  public SearchExpression getExpression() {
    return expression;
  }

  public boolean isExact() {
    return exact;
  }

  public Occur getOccur() {
    return occur;
  }

  /**
   * When a search clause must occur.<br />
   * 
   * @author arrebola
   *
   */
  public static class MustOccur extends SearchClause {
    public MustOccur(Field field, String term) {
      super(field, term, true, Occur.MUST);
    }

    public MustOccur(Field field, String term, boolean exact) {
      super(field, term, exact, Occur.MUST);
    }
  }

  /**
   * When a search clause must not occur.<br />
   * 
   * @author arrebola
   *
   */
  public static class MustNotOccur extends SearchClause {
    public MustNotOccur(Field field, String term) {
      super(field, term, true, Occur.MUST_NOT);
    }

    public MustNotOccur(Field field, String term, boolean exact) {
      super(field, term, exact, Occur.MUST_NOT);
    }
  }

  /**
   * When a search clause should occur.<br />
   * 
   * @author arrebola
   *
   */
  public static class ShouldOccur extends SearchClause {
    public ShouldOccur(Field field, String term) {
      super(field, term, true, Occur.SHOULD);
    }

    public ShouldOccur(Field field, String term, boolean exact) {
      super(field, term, exact, Occur.SHOULD);
    }
  }

}
