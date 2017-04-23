package org.ads.orientdb.utils;

import com.orientechnologies.orient.core.record.impl.ODocument;
import com.tinkerpop.blueprints.Edge;
import com.tinkerpop.blueprints.Vertex;
import com.tinkerpop.blueprints.impls.orient.OrientEdge;
import com.tinkerpop.blueprints.impls.orient.OrientGraph;
import com.tinkerpop.blueprints.impls.orient.OrientGraphNoTx;
import com.tinkerpop.blueprints.impls.orient.OrientVertex;

import org.ads.orientdb.EdgeClass;
import org.ads.orientdb.VertexClass;
import org.ads.orientdb.annotations.MyVertex;
import org.ads.orientdb.annotations.MyVertexIndex;
import org.ads.orientdb.annotations.MyVertexProperty;
import org.ads.orientdb.annotations.MyVertexUid;
import org.ads.orientdb.ex.OrientException;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;
import org.ads.utils.ReflectionUtils;

import java.lang.reflect.Field;
import java.util.Collections;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.function.Consumer;

import javax.validation.constraints.NotNull;

/**
 * OrientDB utility class.<br />
 * 
 * @author arrebola
 *
 */
public class OrientUtils {

  /**
   * Checks if a class has valid {@link MyVertex}, {@link MyVertexProperty} and {@link MyVertexId}
   * annotations.<br />
   * 
   * @param clazz
   *          the {@link Class} to check
   */
  public static void checkClassAnnotations(Class<?> clazz) {

    int propertiesCount = 0;
    int vertexIdCount = 0;

    if (clazz.isAnnotationPresent(MyVertex.class)) {
      for (Field field : clazz.getDeclaredFields()) {
        if (field.isAnnotationPresent(MyVertexProperty.class)) {
          propertiesCount++;
        }
        if (field.isAnnotationPresent(MyVertexIndex.class)) {
          vertexIdCount++;
        }
      }
    }

    if (propertiesCount == 0 && vertexIdCount != 1) {
      throw new IllegalArgumentException();
    }
  }

  /**
   * Gets a {@link Map} of the object fields annotated with the {@link MyVertexProperty} annotation.
   * <br />
   * The keys of the map are set to the {@link MyVertexProperty#name()} property of the annotation.
   * If it is empty, then the field name is used.<br />
   * 
   * @param object
   *          the {@link Object} to
   * @return a {@link Map} of keys
   */
  public static Map<String, Object> getObjectFieldsAsMap(Object object) {

    Parameters.requireNonNull(object);

    Map<String, Object> map = new HashMap<String, Object>();

    Class<?> clazz = object.getClass();
    Field[] fields = clazz.getDeclaredFields();
    for (Field field : fields) {

      MyVertexProperty annotation = field.getAnnotation(MyVertexProperty.class);
      if (CustomObjectUtils.isNull(annotation)) {
        continue;
      }

      String key = annotation.value();
      if (CustomStringUtils.isEmpty(key)) {
        key = field.getName();
      }

      Object value = ReflectionUtils.getFieldValue(object, field);
      if (CustomObjectUtils.isNull(value)) {
        value = ReflectionUtils.invokeGetter(object, field);
      }

      if (CustomObjectUtils.isNull(value)) {
        continue;
      }

      // adds List-like fields
      if (annotation.isLinkedList()) {
        final String iClass = annotation.linkedClass().getSimpleName();
        Map<String, ODocument> linkedListMap = new HashMap<String, ODocument>();
        ((List<?>) value).forEach(new Consumer<Object>() {
          int counter = 0;

          @Override
          public void accept(Object object) {
            ODocument document = new ODocument(iClass);
            document.fromMap(getObjectFieldsAsMap(object));
            linkedListMap.put(String.valueOf(counter++), document);
          }
        });
        map.put(key, linkedListMap);
      } else {
        map.put(key, value);
      }

    }

    return map;

  }

  /**
   * Searches vertices using the fields of the object class that are annotated with
   * {@link MyVertexId}.<br />
   * 
   * @param graphNoTx
   *          the {@link OrientGraphNoTx} no-transaction graph
   * @param object
   *          the {@link Object} to search
   * 
   * @return the {@link Iterable} of {@link Vertex} that represents the objects
   * 
   * @throws OrientException
   *           in case the search fails
   */
  @NotNull
  public static Iterable<Vertex> searchVerticesUsingId(OrientGraphNoTx graphNoTx, Object object)
      throws OrientException {

    Parameters.requireNonNull(graphNoTx, object);

    String uniqueKey = null;
    Object uniqueValue = null;

    Class<?> clazz = object.getClass();
    checkClassAnnotations(clazz);

    Iterable<Vertex> iterable = new Iterable<Vertex>() {
      @Override
      public Iterator<Vertex> iterator() {
        return Collections.emptyIterator();
      }
    };

    boolean found = false;
    for (Field field : clazz.getDeclaredFields()) {
      if (field.isAnnotationPresent(MyVertexUid.class)) {
        uniqueKey = clazz.getSimpleName() + "." + field.getName();
        uniqueValue = ReflectionUtils.getFieldValue(object, field);
        if (CustomObjectUtils.isNull(uniqueValue)) {
          uniqueValue = ReflectionUtils.invokeGetter(object, field);
        }
        found = true;
        break;
      }
    }

    if (found) {
      iterable = graphNoTx.getVertices(uniqueKey, uniqueValue);
    }

    return iterable;

  }

  /**
   * Searches vertices using the fields of the object class that are annotated with
   * {@link MyVertexId}.<br />
   * 
   * @param graphNoTx
   *          the {@link OrientGraphNoTx} no-transaction graph
   * @param object
   *          the {@link Object} to search
   * 
   * @return the {@link Iterable} of {@link Vertex} that represents the objects
   * 
   * @throws OrientException
   *           in case the search fails
   */
  public static Vertex searchVertexUsingId(OrientGraphNoTx graphNoTx, Object object)
      throws OrientException {

    Vertex vertex = null;

    Iterable<Vertex> iterable = searchVerticesUsingId(graphNoTx, object);
    Iterator<Vertex> iterator = iterable.iterator();
    if (iterator.hasNext()) {
      vertex = iterator.next();
    }

    return vertex;

  }

  /**
   * Adds a vertex to the database.<br />
   * Note that the vertex class is determined by the class of the given object.<br />
   * 
   * @param graph
   *          the {@link OrientGraph} graph
   * @param object
   *          the {@link Object} that represents the vertex
   * 
   * @return {@link OrientVertex} that represents the newly created vertex
   * 
   * @throws OrientException
   *           in case addition fails
   */
  public static OrientVertex addVertex(OrientGraph graph, Object object) throws OrientException {

    Parameters.requireNonNull(graph, object);

    final Class<?> clazz = object.getClass();

    VertexClass vertexClass = null;
    for (VertexClass value : VertexClass.values()) {
      if (value.getModelClass().equals(clazz)) {
        vertexClass = value;
        break;
      }
    }

    if (CustomObjectUtils.isNull(vertexClass)) {
      throw new IllegalArgumentException("Invalid vertex class '" + clazz + "'.");
    }

    return graph.addVertex(vertexClass.getVertexClassName(),
        OrientUtils.getObjectFieldsAsMap(object));

  }

  /**
   * Adds a vertex to the database if it cannot be found.<br />
   * Note that the vertex class is determined by the class of the given object.<br />
   *
   * @param graphNoTx
   *          the {@link OrientGraphNoTx} graph
   * @param graph
   *          the {@link OrientGraph} graph
   * @param object
   *          the {@link Object} that represents the vertex
   * 
   * @return {@link OrientVertex} that represents the newly created vertex
   * 
   * @throws OrientException
   *           in case search or addition fails
   */
  public static OrientVertex addVertexIfNotFound(OrientGraphNoTx graphNoTx, OrientGraph graph,
      Object object) throws OrientException {

    Parameters.requireNonNull(graphNoTx, graph, object);

    OrientVertex vertex = (OrientVertex) searchVertexUsingId(graphNoTx, object);
    if (CustomObjectUtils.isNull(vertex)) {
      vertex = addVertex(graph, object);
    }

    if (CustomObjectUtils.isNull(vertex)) {
      throw new IllegalArgumentException("Could not find nor add a vertex for the given object.");
    }

    return vertex;

  }

  /**
   * Searches vertices using the fields of the object class that are annotated with
   * {@link MyVertexId}.<br />
   * 
   * @param graphNoTx
   *          the {@link OrientGraphNoTx} graph
   * @param vertexA
   *          the {@link Vertex} that represents the vertex A
   * @param vertexB
   *          the {@link Vertex} that represents the vertex B
   * @param edgeClass
   *          the {@link EdgeClass} that represents the edge
   * 
   * @throws OrientException
   *           in case the search fails
   */
  public static Edge searchEdge(OrientGraphNoTx graphNoTx, Vertex vertexA, Vertex vertexB,
      EdgeClass edgeClass) throws OrientException {

    Edge edge = null;

    return edge;

  }

  /**
   * Adds an edge to the database.<br />
   * Note that the edge class is determined by the label given.<br />
   * 
   * @param graph
   *          the {@link OrientGraph} graph
   * @param vertexA
   *          the {@link Vertex} that represents the vertex A
   * @param vertexB
   *          the {@link Vertex} that represents the vertex B
   * @param edgeClass
   *          the {@link EdgeClass} that represents the edge
   * 
   * @return {@link OrientEdge} that represents the newly created edge
   */
  public static OrientEdge addEdge(OrientGraph graph, Vertex vertexA, Vertex vertexB,
      EdgeClass edgeClass) {

    Parameters.requireNonNull(graph, vertexA, vertexB, edgeClass);

    return graph.addEdge(edgeClass.getEdgeClassName(), vertexA, vertexB, edgeClass.getEdgeLabel());

  }

  /**
   * Adds an edge to the database if it cannot be found.<br />
   * Note that the edge class is determined by the label given.<br />
   *
   * @param graphNoTx
   *          the {@link OrientGraphNoTx} graph
   * @param graph
   *          the {@link OrientGraph} graph
   * @param vertexA
   *          the {@link Vertex} that represents the vertex A
   * @param vertexB
   *          the {@link Vertex} that represents the vertex B
   * @param edgeClass
   *          the {@link EdgeClass} that represents the edge
   * 
   * @return {@link OrientVertex} that represents the newly created vertex
   * 
   * @throws OrientException
   *           in case search or addition fails
   */
  public static OrientEdge addEdgeIfNotFound(OrientGraphNoTx graphNoTx, OrientGraph graph,
      Vertex vertexA, Vertex vertexB, EdgeClass edgeClass) throws OrientException {

    Parameters.requireNonNull(graphNoTx, graph, vertexA, vertexB, edgeClass);

    OrientEdge edge = (OrientEdge) searchEdge(graphNoTx, vertexA, vertexB, edgeClass);
    if (CustomObjectUtils.isNull(edge)) {
      edge = addEdge(graph, vertexA, vertexB, edgeClass);
    }

    if (CustomObjectUtils.isNull(edge)) {
      throw new IllegalArgumentException(
          "Could not find nor add an edge linking the given vertexes.");
    }

    return edge;

  }

  

}