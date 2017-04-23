package org.ads.orientdb.annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import javax.inject.Qualifier;

@Qualifier
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.TYPE)
public @interface MyVertex {
    
    /**
     * The name of the vertex.<br />
     * 
     * @return {@link String} that represents the name of the vertex
     */
    String value();

}