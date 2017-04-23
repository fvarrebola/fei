package org.ads.orientdb.ex;

/**
 * Custom exception to handle OrientDB exceptions.<br />
 * 
 * @author arrebola
 *
 */
public class OrientException extends Exception {

  private static final long serialVersionUID = 7051064381157048160L;

  /**
   * Constructor.<br />
   */
  public OrientException() {
    super();
  }

  /**
   * Constructor.<br />
   * 
   * @param message
   *          the {@link String} that represents the detail message
   */
  public OrientException(String message) {
    super(message);
  }

  /**
   * Constructor.<br />
   * 
   * @param cause
   *          the {@link Throwable} that represents the cause
   */
  public OrientException(Throwable cause) {
    super(cause);
  }

}
