package org.ads.orientdb.utils;

import org.ads.Constants;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class OrientDbQuery {

  /**
   * SELECT clause projection.<br />
   * 
   * @author arrebola
   *
   */
  static class Projection {
    String name;
    String alias;

    /**
     * Constructor.<br />
     * 
     * @param name
     *          the {@link String} that represents the projection name
     */
    Projection(String name) {
      super();
      this.name = name;
    }

    /**
     * Constructor.<br />
     * 
     * @param name
     *          the {@link String} that represents the projection name
     * @param alias
     *          the {@link String} that represents the projection alias
     */
    Projection(String name, String alias) {
      this(name);
      this.alias = alias;
    }

    @Override
    public String toString() {
      return String.format("%s %s", this.name,
          CustomStringUtils.isNotEmpty(this.alias) ? (" as " + this.alias) : "");
    }
  }

  /**
   * LET clause definition.<br />
   * 
   * @author arrebola
   *
   */
  static class Definition {
    String name;
    String value;

    /**
     * Constructor.<br />
     * 
     * @param name
     *          the {@link String} that represents the definition name
     * @param value
     *          the {@link String} that represents the definition value
     */
    Definition(String name, String value) {
      super();
      this.name = name;
      this.value = value;
    }

    @Override
    public String toString() {
      return String.format("$%s = %s", this.name, this.value);
    }
  }

  /**
   * A generic where clause.<br />
   * 
   * @author arrebola
   *
   */
  public static class Clause {

    protected String field;
    protected String condition;

    /**
     * Constructor.<br />
     */
    protected Clause() {
      super();
    }

    /**
     * Constructor.<br />
     * 
     * @param field
     *          the the {@link String} that represents the field name
     */
    protected Clause(String field) {
      this();
      this.field = field;
    }

    /**
     * Constructor.<br />
     * 
     * @param field
     *          the the {@link String} that represents the field name
     * @param condition
     *          the {@link String} that represents the field condition
     */
    public Clause(String field, String condition) {
      this(field);
      this.condition = condition;
    }

    @Override
    public String toString() {
      return String.format("%s %s", this.field, this.condition);
    }
  }

  /**
   * Abstract "IN" where clause.<br />
   * 
   * @author arrebola
   *
   */
  abstract static class AbstractInClause extends Clause {

    /**
     * Constructor.<br />
     * 
     * @param field
     *          the {@link String} that represents the field
     * @param values
     *          the {@link String} array of fields
     */
    AbstractInClause(String field, String[] values, boolean negate) {
      super();

      Parameters.requireNonEmpty(field);
      Parameters.requireNonEmpty(values);

      List<String> wrapped = new ArrayList<String>();
      for (String value : values) {
        wrapped.add(CustomStringUtils.wrap(value, "\""));
      }

      this.field = field;
      this.condition = String.format("%s IN %s", (negate ? "NOT" : ""),
          Arrays.toString(wrapped.toArray()));
    }
  }

  /**
   * An "IN" where clause.<br />
   * In OrientDB "IN" clauses have the following format: <br />
   * <b>FIELD IN ["value1", "value_2", ...]</b>
   * 
   * @author arrebola
   *
   */
  public static class InClause extends AbstractInClause {

    /**
     * Constructor.<br />
     * 
     * @param field
     *          the {@link String} that represents the field
     * @param values
     *          the {@link String} array of fields
     */
    public InClause(String field, String[] values) {
      super(field, values, false);
    }
  }

  /**
   * A "NOT IN" where clause.<br />
   * In OrientDB "IN" clauses have the following format: <br />
   * <b>FIELD IN ["value1", "value_2", ...]</b>
   * 
   * @author arrebola
   *
   */
  public static class NotInClause extends AbstractInClause {

    /**
     * Constructor.<br />
     * 
     * @param field
     *          the {@link String} that represents the field
     * @param values
     *          the {@link String} array of fields
     */
    public NotInClause(String field, String[] values) {
      super(field, values, true);
    }
  }

  /**
   * A "LUCENE" where clause.<br />
   * In OrientDB Lucene clauses have the following format: <br />
   * <b>[FIELD_1, FIELD_2, ...] LUCENE (FIELD_1:value, FIELD_2:value, ...)</b>
   * 
   * @author arrebola
   *
   */
  public static class LuceneClause extends Clause {

    /**
     * Constructor.<br />
     * 
     * @param fields
     *          the {@link String} array of fields
     * @param value
     *          the {@link String} that represents the value
     */
    public LuceneClause(String[] fields, String value) {
      super();
      Parameters.requireNonEmpty(fields);
      Parameters.requireNonEmpty(value);

      List<String> wrapped = new ArrayList<String>();
      for (String field : fields) {
        wrapped.add(String.format("%s:%s", field, value));
      }

      this.field = Arrays.toString(fields);
      this.condition = String.format("LUCENE \"(%s)\"",
          CustomStringUtils.joinUsingSpace(wrapped.toArray()));

    }
  }

  /**
   * Known statement types.<br />
   * 
   * @author arrebola
   *
   */
  static enum StatementTypes {

    SELECT("SELECT"), FROM("FROM"), WHERE("WHERE"), LET("LET"), ORDER_BY("ORDER BY"), GROUP_BY(
        "GROUP BY"), UNWIND("UNWIND"), LIMIT("LIMIT"), TIMEOUT("TIMEOUT");

    String keyword;

    StatementTypes(String keyword) {
      this.keyword = keyword;
    }

  }

  /**
   * Abstract statement.<br />
   * 
   * @author arrebola
   *
   */
  abstract static class Statement<T> {

    protected StatementTypes type;
    protected List<T> items;

    /**
     * Constructor.
     * 
     * @param type
     *          the {@link StatementTypes}
     */
    Statement(StatementTypes type) {
      super();
      this.type = type;
      this.items = new ArrayList<T>();
    }

    public boolean isEmpty() {
      return this.items.isEmpty();
    }

    public boolean isNotEmpty() {
      return (!isEmpty());
    }

    public boolean add(T item) {
      return this.items.add(item);
    }

    @Override
    public String toString() {
      StringBuilder builder = new StringBuilder();
      builder.append(String.format("%s ", this.type.keyword));
      final int length = this.items.size();
      for (int idx = 0; idx < length; idx++) {
        builder.append(String.format("%s%s ", this.items.get(idx), (idx == length - 1) ? "" : ","));
      }
      return builder.toString();
    }
  }

  /**
   * SELECT statement.<br />
   * 
   * @author arrebola
   *
   */
  static class Select extends Statement<Projection> {
    Select() {
      super(StatementTypes.SELECT);
    }
  }

  /**
   * FROM statement.<br />
   * 
   * @author arrebola
   *
   */
  static class From extends Statement<String> {
    From() {
      super(StatementTypes.FROM);
    }
  }

  /**
   * LET statement.<br />
   * 
   * @author arrebola
   *
   */
  static class Let extends Statement<Definition> {
    Let() {
      super(StatementTypes.LET);
    }
  }

  /**
   * WHERE statement.<br />
   * 
   * @author arrebola
   *
   */
  static class Where extends Statement<Clause> {

    /**
     * Logical operator.<br />
     * 
     * @author arrebola
     *
     */
    static enum LogicalOperators {
      AND("AND"), OR("OR"), NAND("AND NOT"), NOR("OR NOT");
      String keyword;

      LogicalOperators(String keyword) {
        this.keyword = keyword;
      }
    }

    private List<LogicalOperators> operators;

    /**
     * Constructor.
     */
    Where() {
      super(StatementTypes.WHERE);
      this.operators = new ArrayList<LogicalOperators>();
    }

    @Override
    public boolean add(Clause item) {
      if (!this.items.isEmpty()) {
        this.items.clear();
      }
      return items.add(item);
    }

    public boolean add(Clause item, LogicalOperators operator) {
      return (this.items.isEmpty() ? items.add(item)
          : (this.operators.add(operator) && items.add(item)));
    }

    @Override
    public String toString() {

      StringBuilder builder = new StringBuilder();

      final int length = this.items.size();
      if (length == 0 || (this.operators.size() != length - 1)) {
        return builder.toString();
      }

      builder.append(String.format("%s ", this.type.keyword));
      builder.append(String.format("%s ", this.items.get(0)));

      for (int idx = 1; idx < length; idx++) {
        final LogicalOperators operator = this.operators.get(idx - 1);
        final Clause clause = this.items.get(idx);
        builder.append(String.format("%s %s ", operator.keyword, clause));
      }

      return builder.toString();
    }

  }

  /**
   * GROUP BY statement.<br />
   * 
   * @author arrebola
   *
   */
  class GroupBy extends Statement<String> {
    /**
     * Constructor.
     */
    GroupBy() {
      super(StatementTypes.GROUP_BY);
    }
  }

  /**
   * ORDER BY statement.<br />
   * 
   * @author arrebola
   *
   */
  class OrderBy extends Statement<String> {
    /**
     * Constructor.
     */
    OrderBy() {
      super(StatementTypes.ORDER_BY);
    }
  }

  /**
   * UNWIND statement.<br />
   * 
   * @author arrebola
   *
   */
  class Unwind extends Statement<String> {
    /**
     * Constructor.
     */
    Unwind() {
      super(StatementTypes.UNWIND);
    }
  }

  /**
   * LIMIT statement.<br />
   * 
   * @author arrebola
   *
   */
  class Limit extends Statement<Integer> {
    Limit() {
      super(StatementTypes.LIMIT);
    }
  }

  /**
   * TIMEOUT statement.<br />
   * 
   * @author arrebola
   *
   */
  class Timeout extends Statement<Integer> {
    Timeout() {
      super(StatementTypes.TIMEOUT);
    }
  }

  private Select select;
  private From from;
  private Where where;
  private Let let;
  private GroupBy groupBy;
  private OrderBy orderBy;
  private Unwind unwind;
  private Limit limit;
  private Timeout timeout;

  /**
   * The OrientDB query builder.<br />
   * 
   * @author arrebola
   *
   */
  public static class OrientDbQueryBuilder {

    /**
     * The WHERE statement builder.<br />
     * Please note that all the addition methods ({@link #add(Clause)}, {@link #and(Clause)},
     * {@link #nand(Clause)}, {@link #or(Clause)}, {@link #nor(Clause)}) behave exactly the same.
     * Logical operators are ignored if the WHERE statement is empty (that is, if it has no
     * clauses).
     * 
     * @author arrebola
     *
     */
    public static class WhereBuilder {

      private Where where;

      /**
       * Constructor.<br />
       */
      WhereBuilder() {
        super();
        this.where = new Where();
      }

      /**
       * Adds a generic clause.<br />
       * 
       * @param clause
       *          the {@link Clause} to be added
       * @param operator
       *          the {@link OrientDbQueryBuilder.WhereBuilder}
       * @return the {@link Where.LogicalOperators} logical operator
       */
      private WhereBuilder add(Clause clause, Where.LogicalOperators operator) {
        this.where.add(clause, operator);
        return this;
      }

      /**
       * Adds a generic clause.<br />
       * Please note that any existing clause will be discarded.
       * 
       * @param clause
       *          the {@link Clause} to be added
       * 
       * @return the {@link OrientDbQueryBuilder.WhereBuilder}
       */
      public WhereBuilder add(Clause clause) {
        this.where.add(clause);
        return this;
      }

      /**
       * Adds a clause using the AND logical operator.<br />
       * 
       * @param item
       *          the {@link Clause} to be added
       * 
       * @return the {@link OrientDbQueryBuilder.WhereBuilder}
       */
      public WhereBuilder and(Clause item) {
        return add(item, Where.LogicalOperators.AND);
      }

      /**
       * Adds a clause using the NOT AND logical operator.<br />
       * 
       * @param item
       *          the {@link Clause} to be added
       * 
       * @return the {@link OrientDbQueryBuilder.WhereBuilder}
       */
      public WhereBuilder nand(Clause item) {
        return add(item, Where.LogicalOperators.NAND);
      }

      /**
       * Adds a clause using the OR logical operator.<br />
       * 
       * @param item
       *          the {@link Clause} to be added
       * 
       * @return the {@link OrientDbQueryBuilder.WhereBuilder}
       */
      public WhereBuilder or(Clause item) {
        return add(item, Where.LogicalOperators.OR);
      }

      /**
       * Adds a clause using the NOT OR logical operator.<br />
       * 
       * @param item
       *          the {@link Clause} to be added
       * 
       * @return the {@link OrientDbQueryBuilder.WhereBuilder}
       */
      public WhereBuilder nor(Clause item) {
        return add(item, Where.LogicalOperators.NOR);
      }

      /**
       * Builds a WHERE statement.<br />
       * 
       * @return the {@link Where} statement
       */
      Where build() {
        return this.where;
      }
    }

    private OrientDbQueryBuilder.WhereBuilder whereBuilder;
    private OrientDbQuery query;

    /**
     * Constructor.<br />
     */
    public OrientDbQueryBuilder() {
      super();
      this.whereBuilder = new WhereBuilder();
      this.query = new OrientDbQuery();
    }

    /**
     * Adds a SELECT projection.<br />
     * 
     * @param name
     *          the {@link String} that represents the projection name
     * 
     * @return this {@link OrientDbQueryBuilder}
     */
    public OrientDbQueryBuilder select(String name) {
      this.query.select.add(new Projection(name));
      return this;
    }

    /**
     * Adds a SELECT projection.<br />
     * 
     * @param name
     *          the {@link String} that represents the projection name
     * @param alias
     *          the {@link String} that represents the projection alias
     * 
     * @return this {@link OrientDbQueryBuilder}
     */
    public OrientDbQueryBuilder select(String name, String alias) {
      this.query.select.add(new Projection(name, alias));
      return this;
    }

    /**
     * Adds a FROM statement.<br />
     * Please note that any existing clause will be discarded.
     * 
     * @param name
     *          the {@link String} that represents the node class
     * 
     * @return this {@link OrientDbQueryBuilder}
     */
    public OrientDbQueryBuilder from(String name) {
      this.query.from.items.clear();
      this.query.from.add(name);
      return this;
    }

    /**
     * Adds a definition using the LET statement.<br />
     * 
     * @param name
     *          the {@link String} that represents the definition name
     * @param value
     *          the {@link String} that represents the definition value
     * 
     * @return this {@link OrientDbQueryBuilder}
     */
    public OrientDbQueryBuilder let(String name, String value) {
      this.query.let.add(new Definition(name, value));
      return this;
    }

    /**
     * Gets the WHERE statement builder.<br />
     * 
     * @return this {@link OrientDbQueryBuilder.WhereBuilder}
     */
    public OrientDbQueryBuilder.WhereBuilder where() {
      return this.whereBuilder;
    }

    /**
     * Adds a GROUP BY clause.<br />
     * 
     * @param property
     *          the {@link String} that represents the property
     * 
     * @return this {@link OrientDbQueryBuilder}
     */
    public OrientDbQueryBuilder groupBy(String property) {
      this.query.groupBy.add(property);
      return this;
    }

    /**
     * Adds an ORDER BY clause.<br />
     * 
     * @param property
     *          the {@link String} that represents the ordering
     * 
     * @return this {@link OrientDbQueryBuilder}
     */
    public OrientDbQueryBuilder orderBy(String property) {
      this.query.orderBy.add(property);
      return this;
    }

    /**
     * Adds an UNWIND clause.<br />
     * 
     * @param name
     *          the {@link String} that represents the name
     * 
     * @return this {@link OrientDbQueryBuilder}
     */
    public OrientDbQueryBuilder unwind(String name) {
      this.query.unwind.add(name);
      return this;
    }

    /**
     * Sets the query limits.<br />
     * 
     * @param limit
     *          the {@link String} that represents the limit
     * 
     * @return this {@link OrientDbQueryBuilder}
     */
    public OrientDbQueryBuilder limit(Integer limit) {
      this.query.limit.add(limit);
      return this;
    }

    /**
     * Sets the query timeout limit.<br />
     * 
     * @param timeout
     *          the {@link String} that represents the timeout
     * 
     * @return this {@link OrientDbQueryBuilder}
     */
    public OrientDbQueryBuilder timeout(Integer timeout) {
      this.query.timeout.add(timeout);
      return this;
    }

    /**
     * Builds the query.<br />
     * 
     * @return this {@link OrientDbQuery} that represents the query
     */
    public OrientDbQuery build() {
      this.query.where = this.whereBuilder.build();
      if (this.query.timeout.isEmpty()) {
        this.query.timeout.add(Constants.DEFAULT_QUERY_TIMEOUT_IN_MS);
      }
      return this.query;
    }
  }

  /**
   * Private constructor.<br />
   * Please use the {@link OrientDbQueryBuilder}.
   */
  private OrientDbQuery() {
    super();
    this.select = new Select();
    this.from = new From();
    this.let = new Let();
    this.groupBy = new GroupBy();
    this.orderBy = new OrderBy();
    this.unwind = new Unwind();
    this.limit = new Limit();
    this.timeout = new Timeout();
  }

  @Override
  public String toString() {

    StringBuilder builder = new StringBuilder();

    builder.append(this.select);
    builder.append(this.from);

    if (this.let.isNotEmpty()) {
      builder.append(this.let);
    }

    if (this.where.isNotEmpty()) {
      builder.append(this.where);
    }

    if (this.groupBy.isNotEmpty()) {
      builder.append(this.groupBy);
    }

    if (this.orderBy.isNotEmpty()) {
      builder.append(this.orderBy);
    }

    if (this.unwind.isNotEmpty()) {
      builder.append(this.unwind);
    }

    if (this.limit.isNotEmpty()) {
      builder.append(this.limit);
    }

    if (this.timeout.isNotEmpty()) {
      builder.append(this.timeout);
    }

    return builder.toString();
  }

}