package org.ads.langs.java.dao.impl;

import com.orientechnologies.common.exception.OException;
import com.orientechnologies.orient.core.metadata.schema.OType;
import com.orientechnologies.orient.core.record.impl.ODocument;
import com.orientechnologies.orient.core.sql.query.OSQLSynchQuery;
import com.tinkerpop.blueprints.impls.orient.OrientVertex;

import org.ads.langs.java.model.JavaLibrary;
import org.ads.orientdb.EdgeClass;
import org.ads.orientdb.dao.AbstractDao;
import org.ads.orientdb.ex.OrientException;
import org.ads.orientdb.utils.OrientUtils;
import org.ads.utils.ConverterUtils;
import org.ads.utils.CustomListUtils;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

import javax.validation.constraints.NotNull;

/**
 * The Java library OrientDB database manager.<br />
 * 
 * @author arrebola
 *
 */
public class JavaLibraryDao extends AbstractDao {

  private static final String COUNT_QUERY = "SELECT COUNT(*) AS count FROM javalibrary";
  private static final String POPULAR_QUERY = "SELECT groupId, artifactId, version, packaging, classifier, extension, inE(\"depends\").size() AS idx_value FROM javalibrary ORDER BY idx_value DESC";
  private static final String GROUPED_POPULAR_QUERY = "SELECT groupId, artifactId, SUM(inE(\"depends\").size()) AS idx_value FROM javalibrary GROUP BY groupId, artifactId ORDER BY idx_value DESC";
  private static final String MOST_POPULAR_QUERY = "SELECT groupId, artifactId, version, packaging, classifier, extension, inE(\"depends\").size() as idx_value FROM javalibrary WHERE groupId = \"{0}\" AND artifactId = \"{1}\" and packaging = \"jar\" and extension = \"jar\" ORDER BY idx_value DESC LIMIT 1";

  private static final Logger LOGGER = LogManager.getLogger(JavaLibraryDao.class);

  /**
   * Constructor.<br />
   */
  public JavaLibraryDao() {
    super();
  }

  /**
   * Adds an artifact model (of type {@link JavaLibrary}) to an Orient Graph DB.<br />
   * The model is stored as a vertex using {@link #JAVALIBRARY_VERTEX_TYPE_CLASS} class and the
   * dependency links are stored as edges using the {@link #DEPENDENCY_EDGE_TYPE_CLASS} class.<br />
   * 
   * @param library
   *          the {@link JavaLibrary} that represents an artifact
   * 
   * @throws OrientException
   *           in case addition fails
   */
  public void addJavaLibrary(JavaLibrary library) throws OrientException {

    Parameters.requireNonNull(library);

    final OrientVertex vertex = OrientUtils.addVertexIfNotFound(getNoTx(), getTx(), library);

    for (JavaLibrary dep : library.getDependencies()) {
      final OrientVertex depVertex = OrientUtils.addVertexIfNotFound(getNoTx(), getTx(), dep);
      OrientUtils.addEdgeIfNotFound(getNoTx(), getTx(), vertex, depVertex, EdgeClass.DEPENDS);
    }

    try {
      getTx().commit();
    } catch (OException exception) {
      LOGGER.error("Failed to commit java library.", exception);
      throw new OrientException(exception);
    }

  }

  /**
   * Gets the list of popular libraries.<br />
   * 
   * @param group
   *          <code>true</code> if the libraries should be grouped by groupdId and artifactId,
   *          <code>false</code> otherwise
   * @param limit
   *          the count of wanted results
   * 
   * @return the {@link List} of {@link JavaLibrary} that represents the list of popular libraries
   */
  @NotNull
  public List<JavaLibrary> getPopularLibraries(boolean group, int limit) {

    List<JavaLibrary> libraries = new ArrayList<JavaLibrary>();

    final List<ODocument> librariesCountResult = getTx().getRawGraph()
        .query(new OSQLSynchQuery<ODocument>(COUNT_QUERY));

    if (librariesCountResult.isEmpty()) {
      return libraries;
    }

    final ODocument first = CustomListUtils.getFirst(librariesCountResult);
    final OType fieldType = first.fieldType("count");
    final int librariesCount = fieldType.asInt(first.field("count"));

    final OSQLSynchQuery<ODocument> osqlSynchQuery = new OSQLSynchQuery<ODocument>(
        (group ? GROUPED_POPULAR_QUERY : POPULAR_QUERY));

    if (limit > 0) {
      osqlSynchQuery.setLimit(limit);
    }

    final List<ODocument> results = getTx().getRawGraph().query(osqlSynchQuery);
    results.forEach(new Consumer<ODocument>() {
      @Override
      public void accept(ODocument document) {
        libraries.add(ConverterUtils.toJavaLibrary(document, librariesCount));
      }
    });

    return libraries;

  }

  /**
   * Gets the most popular version of a given library (defined by groupId and artifactId fields).
   * <br />
   * 
   * @param library
   *          the {@link JavaLibrary} that represents the given library
   * 
   * @return the {@link JavaLibrary} that represents the most popular version of the given library
   */
  @NotNull
  public JavaLibrary getMostPopularVersion(JavaLibrary library) {

    Parameters.requireNonNull(library);

    final String groupId = library.getGroupId();
    final String artifactId = library.getArtifactId();

    if (CustomStringUtils.isAnyEmpty(groupId, artifactId)) {
      throw new IllegalArgumentException();
    }

    JavaLibrary mostPopularLibrary = new JavaLibrary();

    final OSQLSynchQuery<ODocument> osqlSynchQuery = new OSQLSynchQuery<ODocument>(
        MessageFormat.format(MOST_POPULAR_QUERY, groupId, artifactId));
    osqlSynchQuery.setLimit(1);

    final List<ODocument> mostPopularVersionResult = getTx().getRawGraph().query(osqlSynchQuery);
    if (CustomListUtils.isNotEmpty(mostPopularVersionResult)) {
      final ODocument first = CustomListUtils.getFirst(mostPopularVersionResult);
      if (CustomObjectUtils.isNotNull(first)) {
        mostPopularLibrary = ConverterUtils.toJavaLibrary(first);
      }
    }

    return mostPopularLibrary;

  }

}
