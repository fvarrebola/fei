package org.ads.web.rs;

import org.ads.web.rs.v1.V1JavaApplication;

import javax.ws.rs.ApplicationPath;

/**
 * Default JAX-RS application served at URI /api/java.<br />
 * This class should extend the latest JAX-RS application available.<br />
 * 
 * @author arrebola
 * 
 */
@ApplicationPath("/api/java")
public final class DefaultJavaApplication extends V1JavaApplication {

  /**
   * Constructor.<br />
   */
  public DefaultJavaApplication() {
    super();
  }

}
