package br.edu.fei.hcii17.codeassist;

import java.io.FileInputStream;
import java.io.InputStream;
import java.util.Iterator;
import java.util.Locale;
import java.util.Map.Entry;
import java.util.Properties;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.LogManager;
import java.util.logging.Logger;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

/**
 * Activator implementation for this plug-in.<br/>
 * 
 * @see BundleActivator
 * 
 */
public class Activator implements BundleActivator {

    private static final String LOGGING_PROPERTIES = "logging.properties";

    private static BundleContext context;
    private static Logger logger;

    // forcing English as log levels language
    static {
        Locale.setDefault(Locale.ENGLISH);
    }

    static BundleContext getContext() {
        return context;
    }

    /**
     * Dumps system configuration information.<br />
     */
    private static void dumpSystemConfiguration() {

        if (!logger.isLoggable(Level.INFO)) {
            return;
        }

        logger.info(Messages.config_DumpingSystemProperties);

        Properties properties = System.getProperties();
        Set<Entry<Object, Object>> entrySet = properties.entrySet();
        Iterator<Entry<Object, Object>> iterator = entrySet.iterator();
        while (iterator.hasNext()) {
            final Entry<Object, Object> entry = iterator.next();
            logger.info(Messages.bind(Messages.config_SystemPropertyDetails, entry.getKey(), entry.getValue()));
        }

    }

    private static InputStream readPropertiesFromUserHome(String fileName) throws Exception {
        return new FileInputStream(System.getProperty("user.home") + "/" + fileName);
    }

    /**
     * Tries to Initialize the plug-in logger using the {@link StandardCompletionExtension#LOGGING_PROPERTIES} file
     * located in the user home directory. If it fails to do so it uses an embedded version.<br/>
     */
    private static void initializeLogger() {

        try (InputStream inputStream = readPropertiesFromUserHome(LOGGING_PROPERTIES)) {
            LogManager.getLogManager().readConfiguration(inputStream);
        } catch (Exception exReadingFileStream) {
            try (InputStream resourceStream = Activator.class.getClassLoader()
                    .getResourceAsStream(LOGGING_PROPERTIES)) {
                LogManager.getLogManager().readConfiguration(resourceStream);
            } catch (Exception exceptionReadingResourceStream) {
                throw new RuntimeException(Messages.logger_FailedToLoadDefaultConfig, exceptionReadingResourceStream);
            }
        }

        logger = Logger.getLogger(Activator.class.getSimpleName());
        
        if (logger.isLoggable(Level.INFO)) {
            logger.info(Messages.logger_InitializedSuccessfully);
        }

    }

    /**
     * Initializes this plug-in.<br/>
     */
    private static void initialize() {
        initializeLogger();
        logger.info(Messages.header);
        dumpSystemConfiguration();
    }

    @Override
    public void start(BundleContext bundleContext) throws Exception {
        Activator.context = bundleContext;
        initialize();
        if (logger.isLoggable(Level.FINE)) {
            logger.fine(Messages.bundle_HasStarted);
        }
    }

    @Override
    public void stop(BundleContext bundleContext) throws Exception {
        Activator.context = null;
        if (logger.isLoggable(Level.FINE)) {
            logger.fine(Messages.bundle_HasStopped);
        }
    }

}
