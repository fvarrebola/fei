package org.ads.console.commands.impl;

import org.ads.console.commands.Command;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

/**
 * Represents an abstract shell command.<br />
 * 
 * @author arrebola
 *
 */
abstract class AbstractCommand implements Command {

  private static final Logger LOGGER = LogManager.getLogger(AbstractCommand.class);

  /**
   * Private constructor.<br />
   */
  protected AbstractCommand() {
    super();
  }

  /**
   * Executes a command.<br />
   * This method must be implemented by concrete classes.<br />
   * 
   * @param parameters
   *          the {@link String} vector the represents the input parameters
   * 
   * @throws Exception
   *           in case the execution fails
   */
  protected abstract void doExecute() throws Exception;

  @Override
  public void execute() {

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("About to execute command...");
    }

    try {
      doExecute();
    } catch (Exception exception) {
      LOGGER.error("Command execution failed.", exception);
    }

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Command succesfully executed.");
    }

  }

}
