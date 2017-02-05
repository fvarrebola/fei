package br.edu.fei.hcii17.test.internal;

import java.io.FileInputStream;
import java.io.InputStream;
import java.util.Collections;
import java.util.List;
import java.util.Locale;
import java.util.logging.Level;
import java.util.logging.LogManager;
import java.util.logging.Logger;

import org.junit.internal.builders.AllDefaultPossibilitiesBuilder;
import org.junit.runner.Description;
import org.junit.runner.Result;
import org.junit.runner.Runner;
import org.junit.runner.notification.RunListener;
import org.junit.runner.notification.RunNotifier;
import org.junit.runners.ParentRunner;
import org.junit.runners.Suite.SuiteClasses;
import org.junit.runners.model.InitializationError;
import org.junit.runners.model.RunnerBuilder;

public class Suite extends ParentRunner<Runner> {

    private static Logger logger;

    static {

        Locale.setDefault(Locale.ENGLISH);

        final String PROPERTIES = "junit.logging.properties";
        try (InputStream is = new FileInputStream(System.getProperty("user.home") + "/" + PROPERTIES)) {
            LogManager.getLogManager().readConfiguration(is);
        } catch (Exception exReadingFileStream) {
            try (InputStream rs = Suite.class.getClassLoader().getResourceAsStream(PROPERTIES)) {
                LogManager.getLogManager().readConfiguration(rs);
            } catch (Exception exceptionReadingResourceStream) {
            }
        }
        logger = Logger.getLogger("JUnit");
        logger.info(Messages.junit_Header);
    }

    public static Runner emptySuite() {
        try {
            return new Suite((Class<?>) null, new Class<?>[0]);
        } catch (InitializationError e) {
            throw new RuntimeException("This shouldn't be possible");
        }
    }

    private static Class<?>[] getAnnotatedClasses(Class<?> klass) throws InitializationError {
        SuiteClasses annotation = klass.getAnnotation(SuiteClasses.class);
        if (annotation == null) {
            throw new InitializationError(
                    String.format("class '%s' must have a SuiteClasses annotation", klass.getName()));
        }
        return annotation.value();
    }

    private final List<Runner> runners;

    public Suite(Class<?> klass, RunnerBuilder builder) throws InitializationError {
        this(builder, klass, getAnnotatedClasses(klass));
    }

    public Suite(RunnerBuilder builder, Class<?>[] classes) throws InitializationError {
        this(null, builder.runners(null, classes));
    }

    protected Suite(Class<?> klass, Class<?>[] suiteClasses) throws InitializationError {
        this(new AllDefaultPossibilitiesBuilder(true), klass, suiteClasses);
    }

    protected Suite(RunnerBuilder builder, Class<?> klass, Class<?>[] suiteClasses) throws InitializationError {
        this(klass, builder.runners(klass, suiteClasses));
    }

    protected Suite(Class<?> klass, List<Runner> runners) throws InitializationError {
        super(klass);
        this.runners = Collections.unmodifiableList(runners);
    }

    @Override
    protected List<Runner> getChildren() {
        return runners;
    }

    @Override
    protected Description describeChild(Runner child) {
        return child.getDescription();
    }

    @Override
    protected void runChild(Runner runner, final RunNotifier notifier) {

        notifier.addListener(new RunListener() {
            @Override
            public void testStarted(Description description) throws Exception {
                super.testStarted(description);
                if (logger.isLoggable(Level.INFO)) {
                    logger.info(Messages.bind(Messages.junit_TestStarted, description.getClassName(),
                            description.getMethodName()));
                }
            }

            @Override
            public void testRunFinished(Result result) throws Exception {
                super.testRunFinished(result);
                if (logger.isLoggable(Level.INFO)) {
                    final int failures = result.getFailureCount();
                    logger.info(Messages.bind(Messages.junit_TestRunFinished, result.getRunCount(),
                            failures, result.getRunTime()));
                    if (failures == 0) {
                        logger.info(Messages.junit_TaskCompleted);
                    }
                }
            }

        });
        runner.run(notifier);
    }
}
