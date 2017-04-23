package org.ads.utils;

import java.util.Map;
import java.util.TreeMap;

import javax.validation.constraints.NotNull;

/**
 * Generic object factory implementation.<br />
 * 
 * @author arrebola
 *
 */
public abstract class ObjectFactory<T> {

  private Map<String, Class<? extends T>> classMap;

  /**
   * Constructor.<br />
   */
  public ObjectFactory() {
    super();
    this.classMap = new TreeMap<String, Class<? extends T>>();
    doInitialize();
  }

  /**
   * Gets the map of registered objects.<br />
   * 
   * @return the {@link Map} that represents the registered objects in this factory
   */
  public Map<String, Class<? extends T>> getRegisteredObjects() {
    return this.classMap;
  }

  /**
   * Initializes this factory.<br />
   */
  protected abstract void doInitialize();

  /**
   * Gets the class key.<br />
   * 
   * @param clazz
   *          the {@link Class} to be registered
   * 
   * @return the String that represents the clazz key
   */
  protected abstract String doGetClassKey(Class<? extends T> clazz);

  /**
   * Registers a class into this factory.<br />
   * 
   * @param clazz
   *          the {@link Class} to be registered
   */
  public void register(Class<? extends T> clazz) {
    Parameters.requireNonNull(clazz);
    this.classMap.put(doGetClassKey(clazz), clazz);
  }

  /**
   * Gets an object from this factory.<br />
   * 
   * @param key
   *          the {@link String} that represents the object's class key
   * 
   * @return an instance of T
   */
  @NotNull
  public T getObject(String key) {

    Parameters.requireNonEmpty(key);

    Class<? extends T> clazz = this.classMap.get(key);
    if (CustomObjectUtils.isNull(clazz)) {
      throw new IllegalArgumentException();
    }

    T object = null;
    try {
      object = clazz.newInstance();
    } catch (Exception exception) {
      throw new InstantiationError();
    }

    return object;

  }

}
