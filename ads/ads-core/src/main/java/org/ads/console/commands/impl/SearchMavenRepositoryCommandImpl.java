package org.ads.console.commands.impl;

import org.ads.console.utils.ConsoleUtils;
import org.apache.maven.index.ArtifactInfo;

import java.util.function.Consumer;

/**
 * Command to search the Maven repository.<br />
 * 
 * @author arrebola
 *
 */
public class SearchMavenRepositoryCommandImpl extends AbstractCommand {

  /**
   * Constructor.<br />
   */
  public SearchMavenRepositoryCommandImpl() {
    super();
  }

  static Consumer<ArtifactInfo> defaultConsumer = new Consumer<ArtifactInfo>() {
    @Override
    public void accept(ArtifactInfo artifactInfo) {
      ConsoleUtils.log(artifactInfo);
    }
  };

  @Override
  protected void doExecute() throws Exception {
    /*
     * MavenSearchManager searcher = MavenSearchManager.getInstance(); QueryBuilder helper =
     * searcher.getQueryBuilder();
     * 
     * Query query = null; final String groupId =
     * ConsoleUtils.getString(ShellMessageConstants.PLEASE_INFORM_GROUP_ID); final String artifactId
     * = ConsoleUtils.getString(ShellMessageConstants.PLEASE_INFORM_ARTIFACT_ID); String version =
     * null; if (ConsoleUtils.getBoolean(ShellMessageConstants.INFORM_ARTIFACT_VERSION)) { version =
     * ConsoleUtils.getString(ShellMessageConstants.PLEASE_INFORM_ARTIFACT_VERSION); } String
     * classifier = null; if
     * (ConsoleUtils.getBoolean(ShellMessageConstants.INFORM_ARTIFACT_CLASSIFIER)) { classifier =
     * ConsoleUtils.getString(ShellMessageConstants.PLEASE_INFORM_ARTIFACT_CLASSIFIER); }
     * 
     * searcher.searchIterator(query, defaultConsumer);
     */
  }
}
