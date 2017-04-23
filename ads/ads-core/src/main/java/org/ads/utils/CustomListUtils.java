package org.ads.utils;

import java.util.List;

import javax.validation.constraints.NotNull;
import javax.validation.constraints.Null;

/**
 * List handling utility class.<br />
 * 
 * @author arrebola
 *
 */
public class CustomListUtils {

  /**
   * Checks whether a given generic list is empty.<br />
   * 
   * @param list
   *          the {@link List} that represents the generic list
   * 
   * @return <code>true</code> if the list is empty, <code>false</code> otherwise
   */
  public static <T> boolean isEmpty(@NotNull List<T> list) {
    return (list == null || list.isEmpty());
  }

  /**
   * Checks whether a given generic list is not empty, that is, if the list has at least one
   * element.<br />
   * 
   * @param list
   *          the {@link List} that represents the generic list
   * 
   * @return <code>true</code> if the list is not empty, <code>false</code> otherwise
   */
  public static <T> boolean isNotEmpty(@NotNull List<T> list) {
    return (!isEmpty(list));
  }

  /**
   * Gets the nth element of a list.<br />
   * 
   * @param list
   *          the {@link List}
   * @param index
   *          the index
   * 
   * @return the nth element
   */
  @Null
  public static <T> T getNth(@NotNull List<T> list, int index) {

    Parameters.requireNonNull(list);

    if (index < 0 || index > list.size()) {
      throw new IllegalArgumentException();
    }

    T element = null;
    if (isNotEmpty(list)) {
      element = list.get(index);
    }

    return element;
  }

  /**
   * Gets the first element of a list.<br />
   * 
   * @param list
   *          the {@link List}
   * 
   * @return the first element
   */
  @Null
  public static <T> T getFirst(@NotNull List<T> list) {
    return getNth(list, 0);
  }

}
