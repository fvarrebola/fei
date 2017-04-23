package org.ads.orientdb.annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import javax.inject.Qualifier;

@Qualifier
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.FIELD)
public @interface MyVertexUid {

    /**
     * The name of the index.<br />
     * 
     * @return {@link String} that represents the name of the index
     */
    String value() default "";

}