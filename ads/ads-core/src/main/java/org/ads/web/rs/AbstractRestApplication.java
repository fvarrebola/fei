package org.ads.web.rs;

import org.ads.utils.CustomObjectUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.HashSet;
import java.util.Set;

import javax.ws.rs.ApplicationPath;
import javax.ws.rs.core.Application;

/**
 * An abstract JAX-RS application.<br />
 * 
 * @author arrebola
 *
 */
public abstract class AbstractRestApplication extends Application {

  /**
   * {@link Set} of RESTful resources served by the application.<br />
   */
  protected Set<Class<?>> classes;

  private static final Logger LOGGER = LogManager.getLogger(AbstractRestApplication.class);

  /**
   * Constructor.<br />
   */
  public AbstractRestApplication() {
    super();

    if (LOGGER.isInfoEnabled()) {
      ApplicationPath path = this.getClass().getAnnotation(ApplicationPath.class);
      if (CustomObjectUtils.isNull(path)) {
        throw new InstantiationError("Could not find @ApplicationPath annotation.");
      }
      LOGGER.info("Registered JAX-RS application at path {}.", path.value());
    }

    this.classes = new HashSet<Class<?>>();
  }

  @Override
  public Set<Class<?>> getClasses() {
    return this.classes;
  }

}
