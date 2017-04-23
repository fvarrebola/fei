package org.ads.orientdb.annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Repeatable;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import javax.inject.Qualifier;

@Qualifier
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.TYPE)
@Repeatable(MyVertexIndexes.class)
public @interface MyVertexIndex {

  /**
   * These are the index types.<br />
   */
  enum Type {
    UNIQUE, FULLTEXT
  }

  /**
   * These are the index algorithms.<br />
   */
  enum Algorithm {
    SBTREE, LUCENE
  }

  /**
   * The list of fields to be used by the index.<br />
   * 
   * @return {@link String} that represents the list of fields
   */
  String[] fields();

  /**
   * The type of the index.<br />
   * 
   * @return {@link Type} that represents the type of the index
   */
  Type type() default Type.FULLTEXT;

  /**
   * The algorithm of the index.<br />
   * 
   * @return {@link Algorithm} that represents the algorithm of the index
   */
  Algorithm algorithm() default Algorithm.LUCENE;

}