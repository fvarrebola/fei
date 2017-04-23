package org.ads.utils;

import org.apache.commons.lang3.ObjectUtils;

public class CustomObjectUtils extends ObjectUtils {

  public static boolean isNull(Object object) {
    return (object == null);
  }

  public static boolean isNotNull(Object object) {
    return (!isNull(object));
  }

  /**
   * Checks if at least one object is null.<br />
   * 
   * @param objects
   *          array of objects to check
   *          
   * @return <code>true</code> if at least one object is null, <code>false</code> otherwise
   */
  public static boolean atLeastOneNull(Object... objects) {

    if (isNull(objects)) {
      return true;
    }

    for (Object object : objects) {
      if (isNull(object)) {
        return true;
      }
    }

    return false;

  }

}
