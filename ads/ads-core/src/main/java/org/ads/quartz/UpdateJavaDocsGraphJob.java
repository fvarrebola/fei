package org.ads.quartz;

import org.ads.console.commands.impl.BuildJavaDocGraphCommandImpl;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.quartz.DisallowConcurrentExecution;
import org.quartz.Job;
import org.quartz.JobExecutionContext;
import org.quartz.JobExecutionException;

/**
 * Quartz job implementation that updates javadocs graph.<br />
 * 
 * @author arrebola
 *
 */
@DisallowConcurrentExecution
public class UpdateJavaDocsGraphJob implements Job {

  private static final Logger LOGGER = LogManager.getLogger(UpdateJavaDocsGraphJob.class);

  /**
   * Constructor.<br />
   */
  public UpdateJavaDocsGraphJob() {
    super();
  }

  @Override
  public void execute(JobExecutionContext arg0) throws JobExecutionException {

    final long startTime = System.currentTimeMillis();
    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("JavaDocs graph update Quartz job has started.");
    }

    new BuildJavaDocGraphCommandImpl().execute();

    if (LOGGER.isInfoEnabled()) {
      final long elapsed = System.currentTimeMillis() - startTime;
      LOGGER.info("JavaDocs graph update Quartz job ended in {} ms.", elapsed);
    }

  }

}
