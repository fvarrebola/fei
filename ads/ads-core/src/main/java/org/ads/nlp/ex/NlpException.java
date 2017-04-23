package org.ads.nlp.ex;

/**
 * Custom exception that wraps OpenNLP exceptions.<br />
 * 
 * @author arrebola
 *
 */
public class NlpException extends Exception {

  private static final long serialVersionUID = 6028393185183940175L;

  /**
   * Constructor.<br />
   */
  public NlpException() {
    super();
  }

  /**
   * Constructor.<br />
   * 
   * @param msg
   *          the {@link String} that represents the detail message
   */
  public NlpException(String msg) {
    super(msg);
  }

  /**
   * Constructor.<br />
   * 
   * @param cause
   *          the {@link Throwable} that represents this exception cause
   */
  public NlpException(Throwable cause) {
    super(cause);
  }

}