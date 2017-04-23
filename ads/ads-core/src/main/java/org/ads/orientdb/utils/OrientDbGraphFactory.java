package org.ads.orientdb.utils;

import com.orientechnologies.orient.core.index.OIndex;
import com.orientechnologies.orient.core.index.OIndexDefinition;
import com.orientechnologies.orient.core.index.OIndexDefinitionFactory;
import com.orientechnologies.orient.core.index.OIndexManager;
import com.orientechnologies.orient.core.index.OIndexManagerProxy;
import com.orientechnologies.orient.core.metadata.OMetadata;
import com.orientechnologies.orient.core.metadata.OMetadataDefault;
import com.orientechnologies.orient.core.metadata.schema.OClass;
import com.orientechnologies.orient.core.metadata.schema.OProperty;
import com.orientechnologies.orient.core.metadata.schema.OSchema;
import com.orientechnologies.orient.core.metadata.schema.OType;
import com.tinkerpop.blueprints.impls.orient.OrientEdgeType;
import com.tinkerpop.blueprints.impls.orient.OrientGraph;
import com.tinkerpop.blueprints.impls.orient.OrientGraphFactory;
import com.tinkerpop.blueprints.impls.orient.OrientGraphNoTx;
import com.tinkerpop.blueprints.impls.orient.OrientVertexType;
import com.tinkerpop.blueprints.impls.orient.OrientVertexType.OrientVertexProperty;

import org.ads.Constants;
import org.ads.langs.java.model.JavaField;
import org.ads.langs.java.model.JavaLibrary;
import org.ads.langs.java.model.JavaMethod;
import org.ads.langs.java.model.JavaObject;
import org.ads.langs.java.model.JavaPackage;
import org.ads.langs.java.model.JavaParameter;
import org.ads.orientdb.annotations.MyEdge;
import org.ads.orientdb.annotations.MyVertex;
import org.ads.orientdb.annotations.MyVertexIndex;
import org.ads.orientdb.annotations.MyVertexProperty;
import org.ads.orientdb.ex.OrientException;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;
import org.ads.utils.ReflectionUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.lang.reflect.Field;
import java.util.Arrays;
import java.util.Collection;
import java.util.Map;
import java.util.TreeMap;
import java.util.function.BiConsumer;
import java.util.function.Consumer;

public class OrientDbGraphFactory {

  private static final int MIN_POOL_SIZE = 50;
  private static final int MAX_POOL_SIZE = 100;

  private static OrientGraphFactory factory;

  private static final Logger LOGGER = LogManager.getLogger(OrientDbGraphFactory.class);

  private static OrientDbGraphFactory instance;

  /**
   * Constructor.<br />
   */
  private OrientDbGraphFactory() {
    super();
  }

  /**
   * Gets an instance of this class.<br />
   * 
   * @return an instance of {@link OrientDbGraphFactory}
   * 
   * @throws OrientException
   *           in case initialization fails
   */
  public static OrientDbGraphFactory getInstance() throws OrientException {
    return getInstance(Constants.ORIENTDB_DEFAULT_URL, Constants.ORIENTDB_DEFAULT_USERNAME,
        Constants.ORIENTDB_DEFAULT_PASSWORD);
  }

  /**
   * Gets an instance of this class.<br />
   * 
   * @param url
   *          the {@link String} that represents the database base path
   * @param username
   *          the {@link String} that represents the database user name
   * @param password
   *          the {@link String} that represents the database user password
   * 
   * @return an instance of {@link OrientDbGraphFactory}
   * 
   * @throws OrientException
   *           in case initialization fails
   */
  public static OrientDbGraphFactory getInstance(String url, String username, String password)
      throws OrientException {

    Parameters.requireNonNull(url, username, password);

    if (CustomObjectUtils.isNull(instance)) {
      synchronized (OrientDbGraphFactory.class) {
        if (CustomObjectUtils.isNull(instance)) {
          instance = new OrientDbGraphFactory();
          instance.initialize(url, username, password);
        }
      }
    }

    return instance;

  }

  /**
   * Initializes the database connection.<br />
   * 
   * @param url
   *          the {@link String} that represents the database base path
   * @param username
   *          the {@link String} that represents the database user name
   * @param password
   *          the {@link String} that represents the database user password
   * 
   * @throws OrientException
   *           in case initialization fails
   */
  private void initialize(String url, String username, String password) throws OrientException {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Initializing OrientDB using url {}, username ******** and password ********.",
          url);
    }

    factory = new OrientGraphFactory(url, username, password).setupPool(MIN_POOL_SIZE,
        MAX_POOL_SIZE);

    ensureMetadata(getTx());
    dumpMetadata(getTx());

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("OrientDB successfully initialized.");
    }

  }

  /**
   * Gets transactional graph with the database.<br />
   * 
   * @return the {@link OrientGraph} transactional graph
   */
  public OrientGraph getTx() {
    return factory.getTx();
  }

  /**
   * Gets non transactional graph with the database.<br />
   * 
   * @return the {@link OrientGraph} non transactional graph
   */
  public OrientGraphNoTx getNoTx() {
    return factory.getNoTx();
  }

  /**
   * Dumps all classes in a database metadata.<br />
   * 
   * @param metadata
   *          the {@link OMetadata} that represents the database metadata
   */
  private static void dumpClasses(OMetadata metadata) {

    OSchema schemaProxy = metadata.getSchema();
    if (CustomObjectUtils.isNull(schemaProxy)) {
      LOGGER.warn("Could not dump classes.");
      return;
    }

    LOGGER.debug("Dumping {} classes...", schemaProxy.countClasses());

    schemaProxy.getClasses().forEach(new Consumer<OClass>() {
      @Override
      public void accept(OClass clazz) {
        LOGGER.debug("Class: {}.", clazz.getName());
      }

    });

    LOGGER.debug("All classes were successfully dumped.");

  }

  /**
   * Dumps all indexes in a database metadata.<br />
   * 
   * @param metadata
   *          the {@link OMetadata} that represents the database metadata
   */
  private static void dumpIndexes(OMetadata metadata) {

    OIndexManagerProxy indexManagerProxy = metadata.getIndexManager();
    if (CustomObjectUtils.isNull(indexManagerProxy)) {
      LOGGER.warn("Could not dump indexes - failed to get the index manager.");
      return;
    }

    Collection<? extends OIndex<?>> indexes = indexManagerProxy.getIndexes();
    if (CustomObjectUtils.isNull(indexManagerProxy)) {
      LOGGER.warn("Could not dump indexes.");
      return;
    }

    LOGGER.debug("Dumping {} indexes...", indexes.size());

    indexes.forEach(new Consumer<OIndex<?>>() {
      @Override
      public void accept(OIndex<?> index) {
        LOGGER.debug("Index: {}, type: {}, engine: {}.", index.getName(), index.getType(),
            index.getAlgorithm());
      }

    });

    LOGGER.debug("All indexes were successfully dumped.");

  }

  /**
   * Dumps database metadata.<br />
   * 
   * @param graph
   *          the {@link OrientGraph} that represents the graph database
   */
  public static void dumpMetadata(OrientGraph graph) {

    Parameters.requireNonNull(graph);

    if (!LOGGER.isDebugEnabled()) {
      LOGGER.warn("Database metadata will not be dumped since DEBUG logger level is disabled.");
      return;
    }

    OMetadata metadata = graph.getRawGraph().getMetadata();

    dumpClasses(metadata);
    dumpIndexes(metadata);

  }

  /**
   * Gets an {@link OClass} given the class name as {@link String}.<br />
   * 
   * @param graph
   *          the {@link OrientGraph} graph
   * @param className
   *          the {@link String} that represents the class name
   * 
   * @return the {@link OClass}
   */
  private static OClass getClass(OrientGraph graph, String className) {

    Parameters.requireNonNull(graph, className);

    return graph.getRawGraph().getMetadata().getImmutableSchemaSnapshot().getClass(className);

  }

  /**
   * Ensures that a vertex type for the given class is available.<br />
   * 
   * @param graph
   *          the {@link OrientGraph} graph
   * @param clazz
   *          the {@link Class} that represents the class
   * 
   * @throws OrientException
   *           in case the vertex type cannot be found
   */
  private static void ensureVertexType(OrientGraph graph, Class<?> clazz) throws OrientException {

    MyVertex myVertex = ReflectionUtils.getClassAnnotation(clazz, MyVertex.class);

    Parameters.requireNonNull(myVertex);

    String clazzName = myVertex.value();
    if (CustomStringUtils.isEmpty(clazzName)) {
      clazzName = clazz.getName();
    }

    OrientVertexType vertexType = graph.getVertexType(clazzName);
    if (CustomObjectUtils.isNull(vertexType)) {
      vertexType = graph.createVertexType(clazzName);
    }

    if (CustomObjectUtils.isNull(vertexType)) {
      throw new OrientException("Vertex type '" + clazzName + "' not found");
    }

    for (Field field : clazz.getDeclaredFields()) {

      final MyVertexProperty myProperty = field.getAnnotation(MyVertexProperty.class);
      if (CustomObjectUtils.isNull(myProperty)) {
        continue;
      }

      OType type = OType.getTypeByClass(field.getType());
      if (CustomObjectUtils.isNull(type)) {
        continue;
      }

      if (myProperty.isLinkedList()) {
        type = OType.LINKLIST;
      }

      String name = myProperty.value();
      if (CustomStringUtils.isEmpty(name)) {
        name = field.getName();
      }

      OProperty property = vertexType.getProperty(name);
      if (CustomObjectUtils.isNull(property)) {
        OrientVertexProperty vertexProperty = vertexType.createProperty(name, type);
        vertexProperty.setMandatory(myProperty.mandatory());
        vertexProperty.setReadonly(myProperty.readOnly());
        vertexProperty.setNotNull(!myProperty.allowNull());
        if (OType.LINKLIST.equals(type)) {
          vertexProperty.setLinkedClass(getClass(graph, myProperty.linkedClass().getSimpleName()));
        }
      }

    }

  }

  /**
   * Ensures that the given edge type is available.<br />
   * 
   * @param graph
   *          the {@link OrientGraphNoTx} no-transaction graph
   * @param typeName
   *          the {@link String} that represents the edge type
   * 
   * @return the {@link OrientVertexType} that represents the edge type
   * 
   * @throws OrientException
   *           in case the edge type cannot be found
   */
  private static void ensureEdgeType(OrientGraph graph, Class<?> clazz) throws OrientException {

    MyEdge edge = ReflectionUtils.getClassAnnotation(clazz, MyEdge.class);
    Parameters.requireNonNull(edge);

    final String edgeName = edge.value();
    if (CustomStringUtils.isEmpty(edgeName)) {
      throw new OrientException("Edge name is empty");
    }

    OrientEdgeType type = graph.getEdgeType(edgeName);
    if (CustomObjectUtils.isNull(type)) {
      type = graph.createEdgeType(edgeName);
    }

    if (CustomObjectUtils.isNull(type)) {
      throw new OrientException("Failed to ensure edge type '" + edgeName + "'");
    }

  }

  /**
   * Ensures that all the indexes of a given class are present.<br />
   * 
   * @param graph
   *          the {@link OrientGraph} graph
   * @param clazz
   *          the {@link Class} that represents the class
   * 
   * @return the {@link Map} of indexes with keys as {@link String} and values as {@link OIndex}
   * 
   * @throws OrientException
   *           in case the index cannot be ensured
   */
  private static Map<String, OIndex<?>> ensureIndexes(OrientGraph graph, Class<?> clazz)
      throws OrientException {

    Map<String, OIndex<?>> indexMap = new TreeMap<String, OIndex<?>>();

    MyVertex vertexAnnotation = clazz.getAnnotation(MyVertex.class);
    if (CustomObjectUtils.isNull(vertexAnnotation)) {
      return indexMap;
    }

    String clazzName = vertexAnnotation.value();
    if (CustomStringUtils.isEmpty(clazzName)) {
      clazzName = clazz.getName();
    }

    final MyVertexIndex[] annotations = clazz.getAnnotationsByType(MyVertexIndex.class);
    if (CustomObjectUtils.isNull(annotations)) {
      return indexMap;
    }

    final OMetadataDefault metadata = graph.getRawGraph().getMetadata();

    final OIndexManager indexManager = metadata.getIndexManager();
    final OClass oClass = metadata.getImmutableSchemaSnapshot().getClass(clazzName);

    for (MyVertexIndex annotation : annotations) {

      final String[] fields = annotation.fields();
      if (CustomObjectUtils.isNull(fields)) {
        continue;
      }

      final String indexName = clazzName + "."
          + CustomStringUtils.join(fields, CustomStringUtils.UNDERLINE);

      final String indexType = annotation.type().name();
      final String indexAlgorithm = annotation.algorithm().name();

      OIndex<?> index = indexManager.getIndex(indexName);
      if (CustomObjectUtils.isNotNull(index)) {
        indexMap.put(indexName, index);
        continue;
      }

      final OType[] types = new OType[fields.length];
      Arrays.fill(types, OType.STRING);

      // creates the index definition
      OIndexDefinition indexDef = OIndexDefinitionFactory.createIndexDefinition(oClass,
          Arrays.asList(fields), Arrays.asList(types), null, indexType, indexAlgorithm);
      if (CustomObjectUtils.isNull(indexDef)) {
        throw new OrientException(
            "Failed to create index definition for index '" + indexName + ".");
      }

      // creates the index
      index = indexManager.createIndex(indexName, indexType, indexDef, null, null, null,
          indexAlgorithm);
      if (CustomObjectUtils.isNull(index)) {
        throw new OrientException("Failed to create index '" + indexName + ".");
      }

      indexMap.put(indexName, index);

    }

    return indexMap;

  }

  /**
   * Ensures that all required database meta data is present for the given class.<br />
   * 
   * @param graph
   *          the {@link OrientGraph} that represents the graph database
   * @param clazz
   *          the {@link Class}
   */
  private static void ensureMetadataForClass(OrientGraph graph, Class<?> clazz)
      throws OrientException {

    OrientUtils.checkClassAnnotations(clazz);

    ensureVertexType(graph, clazz);
    ensureEdgeType(graph, clazz);

    Map<String, OIndex<?>> indexMap = ensureIndexes(graph, clazz);
    indexMap.forEach(new BiConsumer<String, OIndex<?>>() {
      @Override
      public void accept(String indexName, OIndex<?> index) {

        if (index.getSize() > 0) {
          return;
        }

        if (index.isRebuiding()) {
          LOGGER.warn("Index {} is being rebuild.", indexName);
          return;
        }

        try {

          if (LOGGER.isInfoEnabled()) {
            LOGGER.info("Rebuilding index {}... (this may take a moment or two)", indexName);
          }

          index.rebuild();

          if (LOGGER.isInfoEnabled()) {
            LOGGER.info("Index {} successfully rebuilt.", indexName);
          }

        } catch (Exception exception) {
          LOGGER.warn("Failed to rebuild index {} ({}).", indexName, exception.getMessage());
        }

      }
    });

  }

  /**
   * Ensures that all required database metadata is present.<br />
   * 
   * @param graph
   *          the {@link OrientGraph} graph
   */
  private static void ensureMetadata(OrientGraph graph) throws OrientException {

    Parameters.requireNonNull(graph);

    ensureMetadataForClass(graph, JavaParameter.class);
    ensureMetadataForClass(graph, JavaMethod.class);
    ensureMetadataForClass(graph, JavaField.class);
    ensureMetadataForClass(graph, JavaObject.class);
    ensureMetadataForClass(graph, JavaPackage.class);
    ensureMetadataForClass(graph, JavaLibrary.class);

  }

}
