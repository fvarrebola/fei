package org.ads.utils;

import com.google.gson.Gson;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.File;
import java.io.FileReader;
import java.io.Reader;
import java.net.URL;

/**
 * Abstract JSON loader.<br />
 * 
 * @author arrebola
 *
 */
public class JsonLoader {

  private static final Logger LOGGER = LogManager.getLogger(JsonLoader.class);

  /**
   * Constructor.<br />
   */
  private JsonLoader() {
    super();
  }

  /**
   * Loads an array of elements from the given resource.<br />
   * 
   * @param resource
   *          the {@link String} that represents the resource name
   * 
   * @return array of elements
   */
  @SuppressWarnings("unchecked")
  public static <T> T[] loadFromResource(String resource, Class<?> clazz) {

    Parameters.requireNonEmpty(resource);

    T[] array = null;

    final URL url = JsonLoader.class.getClassLoader().getResource("json/" + resource);
    if (CustomObjectUtils.isNull(url)) {
      LOGGER.error("Could not find resource '" + resource + "'.");
      return array;
    }

    try (Reader reader = new FileReader(url.getPath())) {
      array = (T[]) new Gson().fromJson(reader, clazz);
    } catch (Exception exception) {
      LOGGER.fatal("Failed to parse resource.", exception);
    }

    return array;
  }

  /**
   * Loads an array of elements from the given file.<br />
   * 
   * @param filePath
   *          the {@link String} that represents the file path
   * 
   * @return array of elements
   */
  @SuppressWarnings("unchecked")
  public static <T> T[] loadFromFile(String filePath, Class<?> clazz) {

    Parameters.requireNonEmpty(filePath);

    T[] array = null;

    final File file = new File(filePath);
    if (!file.exists()) {
      LOGGER.error("Could not find file '" + filePath + "'.");
      return array;
    }

    try (Reader reader = new FileReader(file)) {
      array = (T[]) new Gson().fromJson(reader, clazz);
    } catch (Exception exception) {
      LOGGER.fatal("Failed to parse file.", exception);
    }

    return array;

  }

}
