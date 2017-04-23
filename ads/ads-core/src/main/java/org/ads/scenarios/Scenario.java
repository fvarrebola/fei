package org.ads.scenarios;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

/**
 * Annotation that represents a scenario.<br />
 * 
 * @author arrebola
 *
 */
@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface Scenario {

  /**
   * Gets this scenario id.<br >
   * 
   * @return the {@link String} that represents this scenario id
   */
  String id();

  /**
   * Gets this scenario name.<br >
   * 
   * @return the {@link String} that represents this scenario name
   */
  String name();

  /**
   * Gets this scenario description.<br >
   * 
   * @return the {@link String} that represents this scenario name
   */
  String description() default "";

}
