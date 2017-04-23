package org.ads.web.rs.v1.resources;

import org.ads.Constants;
import org.ads.langs.java.dao.DaoFactory;
import org.ads.langs.java.dao.impl.JavaObjectDao;
import org.ads.langs.java.docs.parsers.zip.impl.GenericZipFileParserImpl;
import org.ads.langs.java.model.JavaObject;
import org.ads.utils.CustomStringUtils;
import org.ads.web.rs.AbstractResource;
import org.ads.web.rs.GenericResource;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.ws.rs.DefaultValue;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.ServerErrorException;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response.Status;

@Path("/objects")
public class JavaObjectsResource extends AbstractResource {

  private static final Logger LOGGER = LogManager.getLogger(JavaObjectsResource.class);

  /**
   * Constructor.<br />
   */
  public JavaObjectsResource() {
    super();
  }

  @GET
  @Path("online")
  @Produces(MediaType.APPLICATION_JSON)
  public String searchObjects(
      @QueryParam("groupId") @DefaultValue(CustomStringUtils.EMPTY) String groupId,
      @QueryParam("artifactId") @DefaultValue(CustomStringUtils.EMPTY) String artifactId,
      @QueryParam("version") @DefaultValue(CustomStringUtils.EMPTY) String version,
      @QueryParam("exact") @DefaultValue(CustomStringUtils.TRUE) boolean exact,
      @QueryParam("limit") @DefaultValue(Constants.MAX_LIMIT_AS_STRING) int limit,
      @QueryParam("page") @DefaultValue(Constants.UNDEFINED_AS_STRING) int page,
      @QueryParam("pageSize") @DefaultValue(Constants.UNDEFINED_AS_STRING) int pageSize,
      @QueryParam("prettyPrint") @DefaultValue(CustomStringUtils.FALSE) boolean prettyPrint) {

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug(
          "Searching objects using groupId = {}, artifactId = {}, version = {}, "
              + "exact = {}, limit = {}, page = {}, pageSize = {}, prettyPrint = {}...",
          groupId, artifactId, version, exact, limit, page, pageSize, prettyPrint);
    }

    checkSearchParameters(limit, page, pageSize);

    GenericResource<JavaObject> resource = new GenericResource<JavaObject>();

    try {
      resource.setItems(new GenericZipFileParserImpl().search(groupId, artifactId, version, exact,
          limit, page, pageSize));
    } catch (Throwable throwable) {
      LOGGER.fatal("System failure.", throwable);
      throw new ServerErrorException(Status.INTERNAL_SERVER_ERROR);
    }

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Returning {} objects.", resource.getItems().size());
    }

    return toJson(resource, prettyPrint);

  }

  @GET
  @Path("offline")
  @Produces(MediaType.APPLICATION_JSON)
  public String searchObjects(
      @QueryParam("input") @DefaultValue(CustomStringUtils.EMPTY) String input,
      @QueryParam("limit") @DefaultValue(Constants.MAX_LIMIT_AS_STRING) int limit,
      @QueryParam("page") @DefaultValue(Constants.UNDEFINED_AS_STRING) int page,
      @QueryParam("pageSize") @DefaultValue(Constants.UNDEFINED_AS_STRING) int pageSize,
      @QueryParam("prettyPrint") @DefaultValue(CustomStringUtils.FALSE) boolean prettyPrint) {

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug(
          "Searching objects using "
              + "input = {}, limit = {}, page = {}, pageSize = {}, prettyPrint = {}...",
          input, limit, page, pageSize, prettyPrint);
    }

    checkSearchParameters(limit, page, pageSize);

    GenericResource<JavaObject> resource = new GenericResource<JavaObject>();

    try {

      JavaObjectDao javaObjectDao = DaoFactory.getJavaObjectDao();
      resource.setItems(javaObjectDao.getJavaObjects(input));

    } catch (Throwable throwable) {

      LOGGER.fatal("System failure.", throwable);
      throw new ServerErrorException(Status.INTERNAL_SERVER_ERROR);

    }

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Returning {} objects.", resource.getItems().size());
    }

    return toJson(resource, prettyPrint);

  }

}
