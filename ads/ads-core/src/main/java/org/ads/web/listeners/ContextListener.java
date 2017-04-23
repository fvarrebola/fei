package org.ads.web.listeners;

import org.ads.langs.java.maven.MavenArtifactResolver;
import org.ads.langs.java.maven.MavenSearchManager;
import org.ads.langs.java.maven.ex.MavenException;
import org.ads.nlp.NlpParser;
import org.ads.nlp.ex.NlpException;
import org.ads.orientdb.ex.OrientException;
import org.ads.orientdb.utils.OrientDbGraphFactory;
import org.ads.quartz.UpdateJavaDocsGraphJob;
import org.ads.quartz.UpdateMavenIndexesJob;
import org.ads.quartz.UpdatePopularityGraphJob;
import org.ads.utils.CustomStringUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.quartz.DailyTimeIntervalScheduleBuilder;
import org.quartz.Job;
import org.quartz.JobBuilder;
import org.quartz.JobDetail;
import org.quartz.Scheduler;
import org.quartz.SchedulerException;
import org.quartz.SchedulerFactory;
import org.quartz.TimeOfDay;
import org.quartz.Trigger;
import org.quartz.TriggerBuilder;
import org.quartz.impl.StdSchedulerFactory;
import org.quartz.listeners.JobChainingJobListener;

import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

/**
 * A context listener that should be used to initialize the application resources.<br />
 * This will prevent delays during web application requests.<br />
 * So far, the following resources are initialized:
 * <ol>
 * <li>The Maven search manager as defined in {@link MavenSearchManager}.</li>
 * <li>The Maven artifact resolver as defined {@link MavenArtifactResolver}.</li>
 * <li>The user input parser as defined in {@link NlpParser}.</li>
 * </ol>
 * 
 * @author arrebola
 *
 */
@WebListener
public final class ContextListener implements ServletContextListener {

  private static final String NAME = "API Documentation Search Prototype";
  private static final String VERSION = "1.0";

  private static final TimeOfDay MIDNIGHT = TimeOfDay.hourAndMinuteOfDay(0, 0);

  private static final Logger LOGGER = LogManager.getLogger(ContextListener.class);

  /**
   * Creates a Quartz job.<br />
   * 
   * @param clazz
   *          the {@link Class} that implements the Quartz job
   * 
   * @return the {@link JobDetail} that represents the Quartz job
   * 
   * @throws SchedulerException
   *           in case job creation fails
   */
  private static JobDetail newJob(Class<? extends Job> clazz, boolean isDurable)
      throws SchedulerException {
    return JobBuilder.newJob(clazz)
        .withIdentity(CustomStringUtils.lowerCase(clazz.getCanonicalName())).storeDurably(isDurable)
        .build();
  }

  /**
   * Initializes the Quartz jobs.<br />
   * 
   * @throws SchedulerException
   *           in case initialization fails
   */
  private static void initializeQuartzJobs() throws SchedulerException {

    SchedulerFactory schedulerFactory = new StdSchedulerFactory();

    Scheduler scheduler = schedulerFactory.getScheduler();
    scheduler.start();

    final JobDetail jMavenJob = newJob(UpdateMavenIndexesJob.class, false);
    final JobDetail jPopularityJob = newJob(UpdatePopularityGraphJob.class, true);
    final JobDetail jJavaDocsJob = newJob(UpdateJavaDocsGraphJob.class, true);

    JobChainingJobListener jobListener = new JobChainingJobListener("jobListener");
    jobListener.addJobChainLink(jMavenJob.getKey(), jPopularityJob.getKey());
    jobListener.addJobChainLink(jPopularityJob.getKey(), jJavaDocsJob.getKey());

    final DailyTimeIntervalScheduleBuilder scheduleBuilder = DailyTimeIntervalScheduleBuilder
        .dailyTimeIntervalSchedule().onMondayThroughFriday().startingDailyAt(MIDNIGHT);
    final Trigger trigger = TriggerBuilder.newTrigger().startNow().withSchedule(scheduleBuilder)
        .build();

    scheduler.scheduleJob(jMavenJob, trigger);
    scheduler.addJob(jPopularityJob, true);
    scheduler.addJob(jJavaDocsJob, true);

    scheduler.getListenerManager().addJobListener(jobListener);

  }

  @Override
  public void contextInitialized(ServletContextEvent sce) {

    final long startTime = System.currentTimeMillis();

    LOGGER.info(CustomStringUtils.EMPTY);
    LOGGER.info(CustomStringUtils.LOTS_OF_STARS);
    LOGGER.info(CustomStringUtils.STAR);
    LOGGER.info(CustomStringUtils.STAR);
    LOGGER.info(String.format("* %s %s ", NAME, VERSION));
    LOGGER.info(CustomStringUtils.STAR);
    LOGGER.info(CustomStringUtils.STAR);
    LOGGER.info(CustomStringUtils.LOTS_OF_STARS);
    LOGGER.info(CustomStringUtils.EMPTY);

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Initializing web application context...");
    }

    try {
      OrientDbGraphFactory.getInstance();
    } catch (OrientException exception) {
      throw new RuntimeException("Failed to initialized OrientDB graph factory.", exception);
    }

    try {
      initializeQuartzJobs();
    } catch (SchedulerException exception) {
      throw new RuntimeException("Failed to initialized Quartz jobs.", exception);
    }

    try {
      MavenSearchManager.getInstance();
    } catch (MavenException exception) {
      throw new RuntimeException("Failed to initialized Maven repository search manager.",
          exception);
    }

    try {
      MavenArtifactResolver.getInstance();
    } catch (MavenException exception) {
      throw new RuntimeException("Failed to initialized Maven artifact resolver.", exception);
    }

    try {
      NlpParser.getInstance();
    } catch (NlpException exception) {
      throw new RuntimeException("Failed to initialized the user input parser.", exception);
    }

    if (LOGGER.isInfoEnabled()) {
      final long elapsed = System.currentTimeMillis() - startTime;
      LOGGER.info("Web application context successfully initialized in {} ms.", elapsed);
    }
  }

  @Override
  public void contextDestroyed(ServletContextEvent sce) {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Destroying context.");
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Context successfully destroyed.");
    }

  }

}
