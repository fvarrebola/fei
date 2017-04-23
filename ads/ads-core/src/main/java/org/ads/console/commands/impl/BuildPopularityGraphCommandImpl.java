package org.ads.console.commands.impl;

import org.ads.langs.java.dao.impl.JavaLibraryDao;
import org.ads.langs.java.maven.MavenArtifactResolver;
import org.ads.langs.java.maven.MavenSearchManager;
import org.ads.langs.java.maven.ex.MavenException;
import org.ads.langs.java.maven.queries.AllArtifactsQuery;
import org.ads.langs.java.model.JavaLibrary;
import org.ads.orientdb.ex.OrientException;
import org.ads.utils.CustomObjectUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.lucene.search.Query;
import org.apache.maven.index.ArtifactAvailability;
import org.apache.maven.index.ArtifactInfo;
import org.apache.maven.index.ArtifactInfoGroup;
import org.apache.maven.index.search.grouping.GAGrouping;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.Map;
import java.util.Map.Entry;
import java.util.function.Consumer;

/**
 * Command to build a popularity graph of Java libraries using the MVN Lucene indexes.<br />
 * The graph is built after performing a grouped search using the {@link GAGrouping} implementation.
 * <br />
 * Then, for each group we determine the latest artifact available for which sources and javadoc do
 * exist.<br />
 * 
 * @author arrebola
 *
 */
public final class BuildPopularityGraphCommandImpl extends AbstractCommand {

  private static final Logger LOGGER = LogManager.getLogger(BuildPopularityGraphCommandImpl.class);

  /**
   * Constructor.<br />
   */
  public BuildPopularityGraphCommandImpl() {
    super();
  }

  @Override
  protected void doExecute() throws Exception {

    MavenSearchManager searchMgr = MavenSearchManager.getInstance();
    MavenArtifactResolver resolver = MavenArtifactResolver.getInstance();
    JavaLibraryDao popularityMgr = new JavaLibraryDao();

    Query query = searchMgr.getQueryBuilder().add(new AllArtifactsQuery()).getQuery();

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Searching artifacts with grouped searching...");
    }

    Collection<ArtifactInfo> collection = new ArrayList<ArtifactInfo>();
    Map<String, ArtifactInfoGroup> groupedSearchMap = searchMgr.searchGrouped(query,
        new GAGrouping());
    groupedSearchMap.entrySet().forEach(new Consumer<Map.Entry<String, ArtifactInfoGroup>>() {

      @Override
      public void accept(Entry<String, ArtifactInfoGroup> entry) {

        final String key = entry.getKey();
        ArtifactInfoGroup infoGroup = entry.getValue();

        if (LOGGER.isDebugEnabled()) {
          LOGGER.debug(
              "Searching group {} for the latest artifact (with sources and javadocs included)...",
              key);
        }

        ArtifactInfo latest = null;
        Iterator<ArtifactInfo> each = infoGroup.getArtifactInfos().iterator();
        while (each.hasNext() && CustomObjectUtils.isNull(latest)) {
          ArtifactInfo element = each.next();
          if (ArtifactAvailability.PRESENT.equals(element.getSourcesExists())
              && ArtifactAvailability.PRESENT.equals(element.getJavadocExists())) {
            latest = element;
          }
        }

        final boolean addToCollection = CustomObjectUtils.isNotNull(latest);
        if (addToCollection) {
          collection.add(latest);
        }

        if (LOGGER.isDebugEnabled()) {
          if (addToCollection) {
            LOGGER.debug("Found artifact {}.", latest);
          } else {
            LOGGER.debug("Could not find an adequate artifact in group {}.", key);
          }
        }

      }
    });

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("There are {} artifacts left to consider.", collection.size());
      LOGGER.info("Building the popularity graph...");
    }

    collection.forEach(new Consumer<ArtifactInfo>() {
      @Override
      public void accept(ArtifactInfo artifactInfo) {
        try {

          if (LOGGER.isDebugEnabled()) {
            LOGGER.debug("Building model for artifact {}.", artifactInfo);
          }

          final JavaLibrary model = resolver.buildArtifactModel(artifactInfo);
          if (LOGGER.isDebugEnabled()) {
            LOGGER.debug("Artifact model successfully built {}.", model);
            LOGGER.debug("Adding model to database.");
          }

          popularityMgr.addJavaLibrary(model);

          if (LOGGER.isTraceEnabled()) {
            LOGGER.trace("Artifact model successfully added to database.");
          }

        } catch (MavenException mavenException) {
          LOGGER.error("Failed to build model for artifact {}.", artifactInfo);
        } catch (OrientException orientException) {
          LOGGER.error("Failed to add artifact model to database.");
        }
      }
    });

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Popularity graph successfully built.");
    }

  }

}