package org.ads.orientdb.annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import javax.inject.Qualifier;

@Qualifier
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.TYPE)
public @interface MyVertexIndexes {

  /**
   * Gets the array of vertex indexes.<br />
   * 
   * @return array of vertex indexes
   */
  MyVertexIndex[] value();

}