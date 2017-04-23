package org.ads;

/**
 * Project constants.<br />
 * 
 * @author arrebola
 *
 */
public class Constants {

  /**
   * The base directory.<br />
   */
  public static final String BASE_DIRECTORY = "ads";

  /**
   * The workspace base directory.<br />
   */
  public static final String WORKSPACE_DIRECTORY = "workspace";

  /**
   * The repository base directory.<br />
   */
  public static final String REPOSITORY_DIRECTORY = "repository";

  /**
   * The Lucene indexes base directory.<br />
   */
  public static final String INDEX_DIRECTORY = "index";

  /**
   * The Lucene indexes cache directory.<br />
   */
  public static final String INDEX_CACHE_DIRECTORY = "index-cache";

  /**
   * The default log directory.<br />
   */
  public static final String LOGS_DIRECTORY = "logs";

  /**
   * Default Maven repository URL.<br />
   */
  public static final String DEFAULT_MAVEN_REPOSITORY_URL = "http://repo1.maven.org/maven2";

  /**
   * The OrientDB database URL.<br />
   */
  public static final String ORIENTDB_DEFAULT_URL = "remote:localhost/javadocs";

  /**
   * The OrientDB database user name.<br />
   */
  public static final String ORIENTDB_DEFAULT_USERNAME = "admin";

  /**
   * The OrientDB database user password.<br />
   */
  public static final String ORIENTDB_DEFAULT_PASSWORD = "admin";

  /**
   * The OrientDB class prefix.<br />
   */
  public static final String ORIENTDB_CLASS_PREFIX = "class:";

  /**
   * Default query timeout in seconds.<br />
   */
  public static final int DEFAULT_QUERY_TIMEOUT_IN_MS = 5000;

  /**
   * Default search thread away timeout in seconds.<br />
   */
  public static final int DEFAULT_AWAIT_TIMEOUT_IN_SECONDS = 10;

  /**
   * Hour pattern.<br />
   */
  public static final String TIME_PATTERN = "HH:mm:ss";

  /**
   * Date time pattern.<br />
   */
  public static final String DATETIME_PATTERN = "yyyy-MM-dd " + TIME_PATTERN;

  /**
   * Unknown value prefix.<br />
   */
  public static final String UNKNOWN_VALUE_PREFIX = "???";

  /**
   * Unknown value suffix.<br />
   */
  public static final String UNKNOWN_VALUE_SUFFIX = "???";

  /**
   * Undefined value.<br />
   */
  public static final int UNDEFINED_AS_INT = -1;

  /**
   * Undefined value.<br />
   */
  public static final String UNDEFINED_AS_STRING = "-1";

  /**
   * Default limit for searches.<br />
   */
  public static final int DEFAULT_LIMIT = 5;

  /**
   * Maximum limit.<br />
   */
  public static final int MAX_LIMIT_AS_INT = 100;

  /**
   * Maximum limit.<br />
   */
  public static final String MAX_LIMIT_AS_STRING = "100";

}
