package org.ads.web.rs.v1.resources;

import org.ads.Constants;
import org.ads.langs.java.dao.DaoFactory;
import org.ads.langs.java.dao.impl.JavaLibraryDao;
import org.ads.langs.java.maven.LuceneQueryBuilder;
import org.ads.langs.java.maven.MavenSearchManager;
import org.ads.langs.java.maven.SearchClause;
import org.ads.langs.java.maven.queries.ApacheArtifactsQuery;
import org.ads.langs.java.model.JavaLibrary;
import org.ads.utils.ConverterUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.web.rs.AbstractResource;
import org.ads.web.rs.GenericResource;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.maven.index.ArtifactInfo;
import org.apache.maven.index.MAVEN;

import java.util.function.Consumer;

import javax.ws.rs.ClientErrorException;
import javax.ws.rs.DefaultValue;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.ServerErrorException;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response.Status;

/**
 * Libraries resource.<br />
 * 
 * @author arrebola
 *
 */
@Path("/libraries")
// TODO: write a Gson TypeAdapter for a Iterator<JavaLibrary>
public class JavaLibrariesResource extends AbstractResource {

  private static final Logger LOGGER = LogManager.getLogger(JavaLibrariesResource.class);

  /**
   * Constructor.<br />
   */
  public JavaLibrariesResource() {
    super();
  }

  @GET
  @Produces(MediaType.APPLICATION_JSON)
  public String getLibraries(
      @QueryParam("groupId") @DefaultValue(CustomStringUtils.EMPTY) String groupId,
      @QueryParam("artifactId") @DefaultValue(CustomStringUtils.EMPTY) String artifactId,
      @QueryParam("version") @DefaultValue(CustomStringUtils.EMPTY) String version,
      @QueryParam("classifier") @DefaultValue(CustomStringUtils.EMPTY) String classifier,
      @QueryParam("packaging") @DefaultValue(CustomStringUtils.EMPTY) String packaging,
      @QueryParam("exact") @DefaultValue(CustomStringUtils.TRUE) boolean exact,
      @QueryParam("limit") @DefaultValue(Constants.MAX_LIMIT_AS_STRING) int limit,
      @QueryParam("page") @DefaultValue(Constants.UNDEFINED_AS_STRING) int page,
      @QueryParam("pageSize") @DefaultValue(Constants.UNDEFINED_AS_STRING) int pageSize,
      @QueryParam("extendedInfo") @DefaultValue(CustomStringUtils.FALSE) boolean extendedInfo,
      @QueryParam("prettyPrint") @DefaultValue(CustomStringUtils.FALSE) boolean prettyPrint) {

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug(
          "Searching libraries using groupId = {}, artifactId = {}, version = {}, "
              + "classifier = {}, packaging = {}, exact = {}, limit = {}, page = {}, "
              + "pageSize = {}, extendedInfo = {}, prettyPrint = {}...",
          groupId, artifactId, version, classifier, packaging, exact, limit, page, pageSize,
          extendedInfo, prettyPrint);
    }

    checkSearchParameters(limit, page, pageSize);

    GenericResource<Object> resource = new GenericResource<Object>();

    try {

      MavenSearchManager search = MavenSearchManager.getInstance();

      LuceneQueryBuilder builder = search.getQueryBuilder();

      if (CustomStringUtils.isNotEmpty(groupId)) {
        builder.add(new SearchClause.MustOccur(MAVEN.GROUP_ID, groupId, exact));
      }
      if (CustomStringUtils.isNotEmpty(artifactId)) {
        builder.add(new SearchClause.MustOccur(MAVEN.ARTIFACT_ID, artifactId, exact));
      }
      if (CustomStringUtils.isNotEmpty(version)) {
        builder.add(new SearchClause.MustOccur(MAVEN.VERSION, version, exact));
      }
      if (CustomStringUtils.isNotEmpty(classifier)) {
        builder.add(new SearchClause.MustOccur(MAVEN.CLASSIFIER, classifier, exact));
      }
      if (CustomStringUtils.isNotEmpty(packaging)) {
        builder.add(new SearchClause.MustOccur(MAVEN.PACKAGING, packaging, exact));
      }

      Consumer<ArtifactInfo> simpleConsumer = new Consumer<ArtifactInfo>() {
        @Override
        public void accept(ArtifactInfo artifactInfo) {
          resource.getItems().add(ConverterUtils.fromMaven(artifactInfo));
        }
      };

      Consumer<ArtifactInfo> extendedConsumer = new Consumer<ArtifactInfo>() {
        @Override
        public void accept(ArtifactInfo artifactInfo) {
          resource.getItems().add(artifactInfo);
        }
      };

      search.searchIterator(builder.getQuery(), (extendedInfo ? extendedConsumer : simpleConsumer),
          limit, page, pageSize);

    } catch (Throwable throwable) {

      LOGGER.fatal("System failure.", throwable);
      throw new ServerErrorException(Status.INTERNAL_SERVER_ERROR);

    }

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Returning {} libraries.", resource.getItems().size());
    }

    return toJson(resource, prettyPrint);

  }

  @GET
  @Path("popular")
  @Produces(MediaType.APPLICATION_JSON)
  public String getPopularLibraries(
      @QueryParam("group") @DefaultValue(CustomStringUtils.FALSE) boolean group,
      @QueryParam("limit") @DefaultValue(Constants.MAX_LIMIT_AS_STRING) int limit,
      @QueryParam("prettyPrint") @DefaultValue(CustomStringUtils.FALSE) boolean prettyPrint) {

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Searching libraries using group = {}, limit = {}, prettyPrint = {}...", group,
          limit, prettyPrint);
    }

    if (limit > Constants.MAX_LIMIT_AS_INT) {
      throw new ClientErrorException(Status.BAD_REQUEST);
    }

    GenericResource<JavaLibrary> resource = new GenericResource<JavaLibrary>();
    resource.setLimit(limit);

    try {

      JavaLibraryDao javaLibraryDao = DaoFactory.getJavaLibraryDao();
      resource.setItems(javaLibraryDao.getPopularLibraries(group, limit));

    } catch (Throwable throwable) {
      LOGGER.fatal("System failure.", throwable);
      throw new ServerErrorException(Status.INTERNAL_SERVER_ERROR);
    }

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Returning {} libraries.", resource.getItems().size());
    }

    return toJson(resource, prettyPrint);

  }

  @GET
  @Path("apache")
  @Produces(MediaType.APPLICATION_JSON)
  public String getApacheLibraries(
      @QueryParam("limit") @DefaultValue(Constants.MAX_LIMIT_AS_STRING) int limit,
      @QueryParam("page") @DefaultValue(Constants.UNDEFINED_AS_STRING) int page,
      @QueryParam("pageSize") @DefaultValue(Constants.UNDEFINED_AS_STRING) int pageSize,
      @QueryParam("extendedInfo") @DefaultValue(CustomStringUtils.FALSE) boolean extendedInfo,
      @QueryParam("prettyPrint") @DefaultValue(CustomStringUtils.FALSE) boolean prettyPrint) {

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug(
          "Searching libraries using limit = {}, page = {}, "
              + "pageSize = {}, extendedInfo = {}, prettyPrint = {}...",
          limit, page, pageSize, extendedInfo, prettyPrint);
    }

    checkSearchParameters(limit, page, pageSize);

    GenericResource<Object> resource = new GenericResource<Object>();

    try {

      MavenSearchManager indexer = MavenSearchManager.getInstance();

      LuceneQueryBuilder builder = indexer.getQueryBuilder().add(new ApacheArtifactsQuery());

      Consumer<ArtifactInfo> simpleConsumer = new Consumer<ArtifactInfo>() {
        @Override
        public void accept(ArtifactInfo artifactInfo) {
          resource.getItems().add(ConverterUtils.fromMaven(artifactInfo));
        }
      };

      Consumer<ArtifactInfo> extendedConsumer = new Consumer<ArtifactInfo>() {
        @Override
        public void accept(ArtifactInfo artifactInfo) {
          resource.getItems().add(artifactInfo);
        }
      };

      indexer.searchIterator(builder.getQuery(), (extendedInfo ? extendedConsumer : simpleConsumer),
          limit, page, pageSize);

    } catch (Throwable throwable) {

      LOGGER.fatal("System failure.", throwable);
      throw new ServerErrorException(Status.INTERNAL_SERVER_ERROR);

    }

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Returning {} libraries.", resource.getItems().size());
    }

    return toJson(resource, prettyPrint);

  }

}
