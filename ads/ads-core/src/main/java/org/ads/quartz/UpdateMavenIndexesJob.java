package org.ads.quartz;

import org.ads.langs.java.maven.MavenSearchManager;
import org.ads.langs.java.maven.ex.MavenException;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.quartz.DisallowConcurrentExecution;
import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * Quartz job implementation that updates Maven indexes.<br />
 * 
 * @author arrebola
 *
 */
@DisallowConcurrentExecution
public class UpdateMavenIndexesJob implements Job {

  private static final Logger LOGGER = LogManager.getLogger(UpdateMavenIndexesJob.class);

  /**
   * Constructor.<br />
   */
  public UpdateMavenIndexesJob() {
    super();
  }

  @Override
  public void execute(JobExecutionContext jobExecutionContext) throws JobExecutionException {

    final long startTime = System.currentTimeMillis();
    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Maven indexes update Quartz job has started.");
    }

    try {
      MavenSearchManager.getInstance().update();
    } catch (MavenException exception) {
      LOGGER.error("Failed to update Maven indexes.", exception);
    }

    if (LOGGER.isInfoEnabled()) {
      final long elapsed = System.currentTimeMillis() - startTime;
      LOGGER.info("Maven indexes Quartz job ended in {} ms.", elapsed);
    }

  }

}
