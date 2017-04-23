package org.ads.utils;

import org.ads.Constants;
import org.apache.commons.io.FileUtils;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

/**
 * Utility class for handling files.<br />
 * 
 * @author arrebola
 *
 */
public class CustomFileUtils {

  /**
   * Gets the path to the workspace directory.<br />
   * 
   * @return the {@link Path} to the workspace directory
   */
  public static Path getBasePath() {
    return Paths.get(FileUtils.getTempDirectoryPath(), Constants.BASE_DIRECTORY);
  }

  /**
   * Gets the path to the workspace directory.<br />
   * 
   * @return the {@link Path} to the workspace directory
   */
  public static Path getWorkspacePath() {
    return getBasePath().resolve(Constants.WORKSPACE_DIRECTORY);
  }

  /**
   * Gets the path to the local repository directory.<br />
   * 
   * @return the {@link Path} to the local repository directory
   */
  public static Path getLocalRepositoryPath() {
    return getWorkspacePath().resolve(Constants.REPOSITORY_DIRECTORY);
  }

  /**
   * Gets the path to the Lucene indexes directory.<br />
   * 
   * @return the {@link Path} to the Lucene indexes directory
   */
  public static Path getIndexPath() {
    return getWorkspacePath().resolve(Constants.INDEX_DIRECTORY);
  }

  /**
   * Gets the path to the Lucene index cache directory.<br />
   * 
   * @return the {@link Path} to the Lucene index cache directory
   */
  public static Path getIndexCachePath() {
    return getWorkspacePath().resolve(Constants.INDEX_CACHE_DIRECTORY);
  }

  /**
   * Gets the path to the log directory.<br />
   * 
   * @return the {@link Path} to the log directory
   */
  public static Path getLogPath() {
    return getBasePath().resolve(Constants.LOGS_DIRECTORY);
  }

  /**
   * Creates a path if it does not exist.<br />
   * 
   * @param path
   *          the {@link Path} to be created
   * 
   * @throws IOException
   *           if the creation fails
   */
  public static void createIfNotPresent(Path path) throws IOException {

    Parameters.requireNonNull(path);

    if (!Files.exists(path)) {
      Files.createDirectories(path);
    }

  }
}
