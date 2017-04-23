package org.ads.web.rs;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import com.orientechnologies.common.concur.OTimeoutException;

import org.ads.Constants;
import org.ads.messages.MessageBundleUtils;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.Parameters;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.ws.rs.ClientErrorException;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.Response.Status;

/**
 * An abstract RESTful resource.<br />
 * 
 * @author arrebola
 *
 */
public class AbstractResource {

  protected Gson defaultGson;
  protected Gson prettyGson;

  protected static MessageBundleUtils bundleUtils = MessageBundleUtils.getInstance();

  private static final Logger LOGGER = LogManager.getLogger(AbstractResource.class);

  /**
   * Constructor.<br />
   */
  public AbstractResource() {
    super();
    this.defaultGson = new Gson();
    this.prettyGson = new GsonBuilder().setPrettyPrinting().create();
  }

  /**
   * Serializes an {@link Object} using {@link Gson}.<br />
   * 
   * @param src
   *          the {@link Object} to serialize
   * @param prettyPrint
   *          indicates whether to use pretty print
   * 
   * @return the {@link String} that represents the JSON serialized object
   */
  protected final String toJson(Object src, boolean prettyPrint) {
    return (prettyPrint ? this.prettyGson.toJson(src) : this.defaultGson.toJson(src));
  }

  /**
   * Serializes an {@link Object} using {@link Gson}.<br />
   * 
   * @param src
   *          the {@link Object} to serialize
   * 
   * @return the {@link String} that represents the JSON serialized object
   */
  protected final String toJson(Object src) {
    return toJson(src, true);
  }

  /**
   * Returns a HTTP failure JAX-RS response.<br />
   * 
   * @param status
   *          the {@link Status} that represents a HTTP status code
   * @param resource
   *          the {@link GenericResource} entity to be serialized
   * @param error
   *          the {@link Errors} that represents custom errors
   * @param extendedInfo
   *          the {@link Object} that represents the extended error information
   * 
   * @return the JAX-RS {@link Response}
   */
  protected Response fail(Status status, GenericResource<?> resource, Errors error,
      Object extendedInfo) {

    Parameters.requireNonNull(status, resource, error);

    resource.fail(error, extendedInfo);

    LOGGER.fatal("Request failed with status {} and error {}.", status, error);
    if (CustomObjectUtils.isNotNull(extendedInfo) && extendedInfo instanceof Throwable) {
      Throwable throwable = (Throwable) extendedInfo;
      if (throwable instanceof OTimeoutException) {
        LOGGER.fatal("Query timeout {}.", throwable.getMessage());
      } else {
        LOGGER.fatal("System failure.", throwable);
      }
    }

    return Response.status(status).entity(toJson(resource)).build();

  }

  /**
   * Returns a HTTP failure JAX-RS response.<br />
   * 
   * @param status
   *          the {@link Status} that represents a HTTP status code
   * @param resource
   *          the {@link GenericResource} entity to be serialized
   * @param error
   *          the {@link Errors} that represents custom errors
   * 
   * @return the JAX-RS {@link Response}
   */
  protected Response fail(Status status, GenericResource<?> resource, Errors error) {
    return fail(status, resource, error, null);
  }

  /**
   * Returns a HTTP failure JAX-RS response.<br />
   * 
   * @param status
   *          the {@link Status} that represents a HTTP status code
   * @param error
   *          the {@link Errors} that represents custom errors
   * @param extendedInfo
   *          the {@link Object} that represents the extended error information
   * 
   * @return the JAX-RS {@link Response}
   */
  protected Response fail(Status status, Errors error, Object extendedInfo) {
    return fail(status, null, error, null);
  }

  /**
   * Returns a HTTP failure JAX-RS response.<br />
   * 
   * @param status
   *          the {@link Status} that represents a HTTP status code
   * @param error
   *          the {@link Errors} that represents custom errors
   * 
   * @return the JAX-RS {@link Response}
   */
  protected Response fail(Status status, Errors error) {

    Parameters.requireNonNull(status);

    return fail(status, null, error, null);
  }

  /**
   * Returns a HTTP failure JAX-RS response.<br />
   * 
   * @param status
   *          the {@link Status} that represents a HTTP status code
   * 
   * @return the JAX-RS {@link Response}
   */
  protected Response fail(Status status) {

    Parameters.requireNonNull(status);

    return fail(status, null, null, null);
  }

  /**
   * Returns a HTTP 200 OK JAX-RS response.<br />
   * 
   * @param entity
   *          the {@link GenericResource} entity to be serialized
   * 
   * @return the JAX-RS {@link Response}
   */
  protected Response ok(GenericResource<?> entity) {

    Parameters.requireNonNull(entity);

    return ok(entity, true);
  }

  /**
   * Returns a HTTP 200 OK JAX-RS response.<br />
   * 
   * @param entity
   *          the {@link GenericResource} entity to be serialized
   * @param prettyPrint
   *          indicates whether to use pretty print
   * 
   * @return the JAX-RS {@link Response}
   */
  protected Response ok(GenericResource<?> entity, boolean prettyPrint) {

    Parameters.requireNonNull(entity);

    return Response.ok().entity(toJson(entity, prettyPrint)).build();
  }

  /**
   * Checks search parameters.<br />
   * So far, the rules are:
   * <ol>
   * <li>If {@code limit} is set then {@code page} and {@code pageSize} must not be present.</li>
   * <li>{@code limit} must not be grater than {@link Constants#MAX_LIMIT_AS_INT}.</li>
   * <li>If {@code pageSize} is set then {@code page} must be set.</li>
   * </ol>
   * Failing to cope with these rules result will result in HTTP {@link Status#BAD_REQUEST} error.
   * <br />
   * 
   * @param limit
   *          the count of wanted results
   * @param page
   *          the desired page
   * @param pageSize
   *          the page size
   */
  protected static void checkSearchParameters(int limit, int page, int pageSize) {

    if (limit > 0 && (page > 0 || pageSize > 0)) {
      throw new ClientErrorException(Status.BAD_REQUEST);
    }

    if (limit > Constants.MAX_LIMIT_AS_INT) {
      throw new ClientErrorException(Status.BAD_REQUEST);
    }

    if (pageSize > 0 && page < 0) {
      throw new ClientErrorException(Status.BAD_REQUEST);
    }

  }

  protected static void log(Throwable throwable) {

    Parameters.requireNonNull(throwable);

  }

}
