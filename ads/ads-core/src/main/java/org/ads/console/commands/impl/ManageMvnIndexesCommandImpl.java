package org.ads.console.commands.impl;

import org.ads.console.utils.ConsoleUtils;
import org.ads.langs.java.maven.MavenSearchManager;
import org.ads.messages.ShellMessageConstants;

/**
 * Command to manage Maven indexes.<br />
 * 
 * @author arrebola
 *
 */
public final class ManageMvnIndexesCommandImpl extends AbstractCommand {

  private static final String NEW = "new";
  private static final String UPDATE = "update";
  private static final String DELETE = "delete";

  private static final String[] OPTIONS = new String[] { UPDATE, NEW, DELETE };

  /**
   * Constructor.<br />
   */
  public ManageMvnIndexesCommandImpl() {
    super();
  }

  @Override
  protected void doExecute() throws Exception {

    MavenSearchManager indexer = MavenSearchManager.getInstance();

    String option = ConsoleUtils.getString(ShellMessageConstants.PLEASE_SELECT_AN_OPTION, OPTIONS);
    if (NEW.equals(option)) {
      indexer.delete();
      indexer.update();
    } else if (UPDATE.equals(option)) {
      indexer.update();
    } else if (DELETE.equals(option)) {
      indexer.delete();
    }

  }
}
