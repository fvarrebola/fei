package org.ads.utils;

public final class Parameters {

  /**
   * Throws an {@link NullPointerException} if at least one of the given objects is null.<br/>
   * 
   * @param objects
   *          the objects
   * 
   * @throws NullPointerException
   *           if at least one of the given objects is null
   */
  public static void requireNonNull(Object... objects) {
    if (CustomObjectUtils.atLeastOneNull(objects)) {
      throw new IllegalArgumentException();
    }
  }

  /**
   * Throws an {@link NullPointerException} if at least one of the given strings is null.<br/>
   * 
   * @param strings
   *          the strings
   * 
   * @throws NullPointerException
   *           if at least one of the given objects is null
   */
  public static void requireNonEmpty(String... strings) {
    if (CustomStringUtils.isAnyEmpty(strings)) {
      throw new NullPointerException();
    }
  }

}
