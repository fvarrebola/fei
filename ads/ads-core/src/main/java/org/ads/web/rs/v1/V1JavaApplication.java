package org.ads.web.rs.v1;

import org.ads.web.rs.AbstractRestApplication;
import org.ads.web.rs.v1.resources.JavaLibrariesResource;
import org.ads.web.rs.v1.resources.JavaMethodsResource;
import org.ads.web.rs.v1.resources.JavaObjectsResource;

import javax.ws.rs.ApplicationPath;

/**
 * JAX-RS application served at URI /api/v1/java.<br />
 * 
 * @author arrebola
 * 
 * @see AbstractRestApplication
 *
 */
@ApplicationPath("/api/v1/java")
public class V1JavaApplication extends AbstractRestApplication {

  /**
   * Constructor.<br />
   */
  public V1JavaApplication() {
    super();
    this.classes.add(JavaLibrariesResource.class);
    this.classes.add(JavaObjectsResource.class);
    this.classes.add(JavaMethodsResource.class);
  }

}
