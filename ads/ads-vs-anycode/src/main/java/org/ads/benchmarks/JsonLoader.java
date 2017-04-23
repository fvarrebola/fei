package org.ads.benchmarks;

import java.io.FileReader;
import java.io.Reader;
import java.net.URL;

import org.ads.utils.CustomObjectUtils;
import org.ads.utils.Parameters;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import com.google.gson.Gson;

/**
 * Abstract JSON loader.<br />
 * 
 * @author arrebola
 *
 * @param <T>
 */
public class JsonLoader {

    private static final Logger LOGGER = LogManager.getLogger(JsonLoader.class);

    /**
     * Constructor.<br />
     */
    public JsonLoader() {
        super();
    }

    /**
     * Loads an array of elements <T> from the given resource.<br />
     * 
     * @param resource
     *            the {@link String} that represents the resource name
     * 
     * @return array of elements <T>
     */
    @SuppressWarnings("unchecked")
    public <T extends Benchmark> T[] loadFromResource(String resource, Class<? extends Benchmark[]> clazz) {

        Parameters.requireNonEmpty(resource);

        T[] benchmarks = null;

        final URL url = JsonLoader.class.getClassLoader().getResource("json/" + resource);
        if (CustomObjectUtils.isNull(url)) {
            LOGGER.error("Could not find resource '" + resource + "'.");
            return benchmarks;
        }

        try (Reader reader = new FileReader(url.getPath())) { 
            benchmarks = (T[]) new Gson().fromJson(reader, clazz);
        } catch (Exception exception) {
            LOGGER.fatal("Failed to parse resource.", exception);
        }

        return benchmarks;
    }

}
