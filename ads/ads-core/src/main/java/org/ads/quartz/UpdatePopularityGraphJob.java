package org.ads.quartz;

import org.ads.console.commands.impl.BuildPopularityGraphCommandImpl;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.quartz.DisallowConcurrentExecution;
import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * Quartz job implementation that updates the popularity graph.<br />
 * 
 * @author arrebola
 *
 */
@DisallowConcurrentExecution
public class UpdatePopularityGraphJob implements Job {

  private static final Logger LOGGER = LogManager.getLogger(UpdatePopularityGraphJob.class);

  /**
   * Constructor.<br />
   */
  public UpdatePopularityGraphJob() {
    super();
  }

  @Override
  public void execute(JobExecutionContext jobExecutionContext) throws JobExecutionException {

    final long startTime = System.currentTimeMillis();
    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Popularity graph update Quartz job has started.");
    }

    new BuildPopularityGraphCommandImpl().execute();

    if (LOGGER.isInfoEnabled()) {
      final long elapsed = System.currentTimeMillis() - startTime;
      LOGGER.info("Popularity graph update Quartz job ended in {} ms.", elapsed);
    }
  }
}
