package org.ads.langs.java.maven.ex;

/**
 * Custom exception that wraps some of the Maven indexer API and Aether resolver API exceptions.
 * <br />
 * 
 * @author arrebola
 *
 */
public class MavenException extends Exception {

  private static final long serialVersionUID = -5861275853487885214L;

  /**
   * Constructor.<br />
   */
  public MavenException() {
    super();
  }

  /**
   * Constructor.<br />
   * 
   * @param msg
   *          the {@link String} that represents the detail message
   */
  public MavenException(String msg) {
    super(msg);
  }

  /**
   * Constructor.<br />
   * 
   * @param cause
   *          the {@link Throwable} that represents this exception cause
   */
  public MavenException(Throwable cause) {
    super(cause);
  }

}
