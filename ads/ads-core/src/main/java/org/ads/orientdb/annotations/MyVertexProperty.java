package org.ads.orientdb.annotations;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

import javax.inject.Qualifier;

@Qualifier
@Retention(RetentionPolicy.RUNTIME)
@Target(ElementType.FIELD)
public @interface MyVertexProperty {

    /**
     * The name of the property.<br />
     * 
     * @return {@link String} that represents the property name
     */
    String value() default "";

    /**
     * Indicates if a property is mandatory.<br />
     * 
     * @return <code>true</code> if the property is mandatory; <code>false</code> otherwise
     */
    boolean mandatory() default true;

    /**
     * Indicates if a property is read-only.<br />
     * 
     * @return <code>true</code> if the property is read-only; <code>false</code> otherwise
     */
    boolean readOnly() default false;

    /**
     * Indicates if a property allows null.<br />
     * 
     * @return <code>true</code> if the property is allows null; <code>false</code> otherwise
     */
    boolean allowNull() default true;

    /**
     * Indicates if a property is a linked list.<br />
     * 
     * @return <code>true</code> if the property is a linked list; <code>false</code> otherwise
     */
    boolean isLinkedList() default false;

    /**
     * Indicates if a property is an embedded list.<br />
     * 
     * @return <code>true</code> if the property is an embedded list; <code>false</code> otherwise
     */
    boolean isEmbeddedList() default false;

    /**
     * Indicates the linked class of this property.<br />
     * 
     * @return the {@link Class} that represents the linked class of this property
     */
    Class<?> linkedClass() default Object.class;

}