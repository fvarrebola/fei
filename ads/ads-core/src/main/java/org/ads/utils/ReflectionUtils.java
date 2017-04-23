package org.ads.utils;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

import javax.validation.constraints.NotNull;
import javax.validation.constraints.Null;

/**
 * Java reflection utility class.<br />
 * 
 * @author arrebola
 *
 */
public final class ReflectionUtils {

  private static final String GETTER_PREFIX = "get";

  private static final Logger LOGGER = LogManager.getLogger(ReflectionUtils.class);

  /**
   * Gets an annotation for the specified class.<br />
   * 
   * @param clazz
   *          the {@link Class} to search for the given annotation
   * @param annotationClass
   *          the {@link Class} that represents the annotation
   * 
   * @return the {@link Annotation} that represents the annotation if present, else
   *         <code>null</code>
   */
  @Null
  public static <A extends Annotation> A getClassAnnotation(@NotNull Class<?> clazz,
      @NotNull Class<A> annotationClass) {

    Parameters.requireNonNull(clazz, annotationClass);

    return clazz.getAnnotation(annotationClass);

  }

  /**
   * Gets the list of annotations for the specified class.<br />
   * 
   * @param clazz
   *          the {@link Class} to search for the given annotation
   * @param annotationClass
   *          the {@link Class} that represents the annotation
   * 
   * @return the {@link List} of {@link Annotation} that represents the list of annotations
   */
  @NotNull
  public static <A extends Annotation> List<A> getClassAnnotationsList(@NotNull Class<?> clazz,
      @NotNull Class<A> annotationClass) {

    Parameters.requireNonNull(clazz, annotationClass);

    List<A> annotationsList = new ArrayList<A>();

    A[] annotationsArray = clazz.getAnnotationsByType(annotationClass);
    if (CustomObjectUtils.isNull(annotationsArray)) {
      return annotationsList;
    }

    annotationsList.addAll(Arrays.asList(annotationsArray));

    return annotationsList;

  }

  /**
   * Gets the list of fields of a class the hold the given annotation.<br />
   * 
   * @param clazz
   *          the {@link Class} from which to get the fields from
   * @param annotationClazz
   *          the {@link Class} of the desired annotation
   * 
   * @return the {@link List} of {@link Field} the represents the list of fields
   */
  @NotNull
  public static List<Field> getFields(@NotNull Class<?> clazz,
      @NotNull Class<? extends Annotation> annotationClazz) {

    Parameters.requireNonNull(clazz, annotationClazz);

    List<Field> fields = new ArrayList<Field>();

    for (Field field : clazz.getDeclaredFields()) {
      if (field.isAnnotationPresent(annotationClazz)) {
        fields.add(field);
      }
    }

    return fields;

  }

  /**
   * Gets the value of the field.<br />
   * 
   * @param object
   *          the {@link Object} from which to get the field value
   * @param field
   *          the {@link Field} to read the value from
   * @return the {@link Object} the represents the field value
   */
  @Null
  public static Object getFieldValue(@NotNull Object object, @NotNull Field field) {

    Parameters.requireNonNull(object, field);

    Object value = null;
    try {
      if (!field.isAccessible()) {
        field.setAccessible(true);
      }
      value = field.get(object);
    } catch (Exception exception) {
      LOGGER.warn("Failed to invoke getter method for field '{}'", field);
    }

    return value;
  }

  /**
   * Builds a getter method name using the prefix {@link ReflectionUtils#GETTER_PREFIX}.<br />
   * 
   * @param field
   *          the {@link Field} to invoke the getter from
   * @return the {@link Object} the represents the field value
   */
  private static String buildGetterMethodName(Field field) {
    return GETTER_PREFIX + CustomStringUtils.capitalize(field.getName());
  }

  /**
   * Gets the value of the field invoking its getter method, if any.<br />
   * 
   * @param object
   *          the {@link Object} from which to get the field value
   * @param field
   *          the {@link Field} to read the value from
   * 
   * @return the {@link Object} the represents the field value
   */
  public static Object invokeGetter(Object object, Field field) {

    Parameters.requireNonNull(object, field);

    Object value = null;
    Class<?> clazz = object.getClass();
    try {
      Method method = clazz.getDeclaredMethod(buildGetterMethodName(field));
      if (CustomObjectUtils.isNotNull(method)) {
        value = method.invoke(object);
      }
    } catch (Exception exception) {
      LOGGER.warn("Failed to invoke getter method for field '{}'", field);
    }

    return value;

  }
}
