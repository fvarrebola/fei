package org.ads.langs.java.dao.impl;

import com.orientechnologies.common.exception.OException;
import com.orientechnologies.orient.core.record.impl.ODocument;
import com.orientechnologies.orient.core.sql.query.OSQLSynchQuery;
import com.tinkerpop.blueprints.impls.orient.OrientVertex;

import org.ads.langs.java.model.JavaField;
import org.ads.langs.java.model.JavaLibrary;
import org.ads.langs.java.model.JavaMethod;
import org.ads.langs.java.model.JavaObject;
import org.ads.orientdb.EdgeClass;
import org.ads.orientdb.dao.AbstractDao;
import org.ads.orientdb.ex.OrientException;
import org.ads.orientdb.utils.OrientUtils;
import org.ads.utils.ConverterUtils;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class JavaObjectDao extends AbstractDao {

  private static final String QUERY = "SELECT name, description FROM javaobject";
  private static final String LUCENE_QUERY = 
      "SELECT name, description FROM javaobject WHERE [name, description] LUCENE \"{0}\"";

  private static final Logger LOGGER = LogManager.getLogger(JavaObjectDao.class);

  /**
   * Constructor.<br />
   */
  public JavaObjectDao() {
    super();
  }

  private void addJavaFields(JavaObject object, OrientVertex objectVertex) throws OrientException {

    final List<JavaField> fields = object.getFields();
    for (JavaField field : fields) {
      final OrientVertex vertex = OrientUtils.addVertexIfNotFound(getNoTx(), getTx(), field);
      OrientUtils.addEdgeIfNotFound(getNoTx(), getTx(), objectVertex, vertex, EdgeClass.IS_PART_OF);
    }

  }

  private void addJavaMethods(JavaObject object, OrientVertex objectVertex) throws OrientException {

    final List<JavaMethod> methods = object.getMethods();
    for (JavaMethod method : methods) {
      final OrientVertex vertex = OrientUtils.addVertexIfNotFound(getNoTx(), getTx(), method);
      OrientUtils.addEdgeIfNotFound(getNoTx(), getTx(), objectVertex, vertex, EdgeClass.IS_PART_OF);
    }

  }

  /**
   * Adds a Java object (of type {@link JavaObject}) to an Orient Graph DB.<br />
   * The model is stored as a vertex using the JavaObject class and the dependency links are stored
   * as edges using the is-part-of class.<br />
   * 
   * @param library
   *          the {@link JavaLibrary} to which the object is a part of
   * @param object
   *          the {@link JavaObject} to be added
   * 
   * @throws OrientException
   *           in case addition fails
   */
  public void addJavaObject(JavaLibrary library, JavaObject object) throws OrientException {

    Parameters.requireNonNull(library, object);

    OrientVertex libraryVertex = (OrientVertex) OrientUtils.searchVertexUsingId(getNoTx(), library);
    if (CustomObjectUtils.isNull(libraryVertex)) {
      return;
    }

    final OrientVertex jObjectVertex = OrientUtils.addVertexIfNotFound(getNoTx(), getTx(), object);
    OrientUtils.addEdgeIfNotFound(getNoTx(), getTx(), libraryVertex, jObjectVertex,
        EdgeClass.IS_PART_OF);

    addJavaFields(object, jObjectVertex);
    addJavaMethods(object, jObjectVertex);

    try {
      getTx().commit();
    } catch (OException exception) {
      LOGGER.error("Failed to commit java object to database.", exception);
      throw new OrientException(exception);
    }

  }

  /**
   * Adds a list of Java object (of type {@link JavaObject}) to an Orient Graph DB.<br />
   * The model is stored as a vertex using the JavaObject class and the dependency links are stored
   * as edges using the is-part-of class.<br />
   * 
   * @param library
   *          the {@link JavaLibrary} to which the object is a part of
   * @param objects
   *          the {@link List} of {@link JavaObject} to be added
   * 
   * @throws OrientException
   *           in case addition fails
   */
  public void addJavaObjects(JavaLibrary library, List<JavaObject> objects) throws OrientException {

    Parameters.requireNonNull(library, objects);

    for (JavaObject object : objects) {
      addJavaObject(library, object);
    }

  }

  /**
   * Gets a list of all the Java objects (of type {@link JavaObject}) found in a Orient Graph DB.
   * <br />
   * 
   * @return the {@link List} of {@link JavaObject} found
   */
  public List<JavaObject> getJavaObjects() {
    return getJavaObjects(null);
  }

  /**
   * Gets a list of all the Java objects (of type {@link JavaObject}) found in a Orient Graph DB.
   * <br />
   * 
   * @param input
   *          the search {@link String}
   * 
   * @return the {@link List} of {@link JavaObject} found
   */
  public List<JavaObject> getJavaObjects(String input) {
    return getJavaObjects(input, -1);
  }

  /**
   * Gets a list of all the Java objects (of type {@link JavaObject}) found in a Orient Graph DB.
   * <br />
   * 
   * @param input
   *          the search {@link String}
   * @param limit
   *          the search limit
   * 
   * @return the {@link List} of {@link JavaObject} found
   */
  public List<JavaObject> getJavaObjects(String input, int limit) {

    List<JavaObject> objects = new ArrayList<JavaObject>();

    String query = null;
    if (CustomStringUtils.isEmpty(input)) {
      query = QUERY;
    } else {
      query = MessageFormat.format(LUCENE_QUERY, input);
    }

    final OSQLSynchQuery<ODocument> osqlSynchQuery = new OSQLSynchQuery<ODocument>(query);
    if (limit > 0) {
      osqlSynchQuery.setLimit(limit);
    }

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Searching java objects using query {}...", query);
    }

    final List<ODocument> results = getTx().getRawGraph().query(osqlSynchQuery);
    results.forEach(new Consumer<ODocument>() {
      @Override
      public void accept(ODocument document) {
        objects.add(ConverterUtils.toJavaObject(document));
      }
    });

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Search found {} java methods.", objects.size());
    }

    return objects;

  }

}
