package org.ads.benchmarks;

import com.google.common.reflect.TypeToken;
import com.google.gson.Gson;

import org.ads.langs.java.model.JavaMethod;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;
import org.ads.scenarios.java.JavaMethodSearchScenarioFactory;
import org.ads.scenarios.nlp.NlpScenario;
import org.ads.scenarios.nlp.NlpScenarioFactory;
import org.ads.utils.CustomStringUtils;
import org.ads.web.rs.GenericResource;
import org.apache.commons.io.FileUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;

import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.Response.Status;

/**
 * 
 * @author arrebola
 *
 */
public class MainApp {

    private static final Logger LOGGER = LogManager.getLogger(MainApp.class);

    private static final Collection<Class<? extends NlpScenario>> nlpScenarios = new NlpScenarioFactory()
            .getRegisteredObjects().values();
    private static final Collection<Class<? extends JavaMethodSearchScenario>> optionsScenarios = new JavaMethodSearchScenarioFactory()
            .getRegisteredObjects().values();

    //private static final JavaMethodsResourceClient client = new JavaMethodsResourceClient();

    private static void write(File file, String str) {
        try {
            Files.write(Paths.get(file.getPath()), str.getBytes(), StandardOpenOption.APPEND);
        } catch (IOException exception) {
            LOGGER.error("Failed to write file.", exception);
        }
    }

    private static File getEmptyFile(String name) throws IOException {

        final String path = FileUtils.getTempDirectoryPath() + "ads" + File.separator + "logs";

        File file = new File(path + File.separator + name);
        if (file.exists()) {
            file.delete();
        }

        file.createNewFile();

        if (!file.exists()) {
            throw new IOException();
        }

        return file;

    }

    private static void sleep() {
        try {
            Thread.sleep(10000);
        } catch (InterruptedException e) {
        }
    }


    static TypeToken<GenericResource<JavaMethod>> typeToken = new TypeToken<GenericResource<JavaMethod>>() {
        private static final long serialVersionUID = -7712896744679522266L;
    };
    
    /**
     * 
     * @param args
     */
    public static void main(String[] args) {

        LOGGER.info(CustomStringUtils.EMPTY);
        LOGGER.info(CustomStringUtils.LOTS_OF_STARS);
        LOGGER.info(CustomStringUtils.STAR);
        LOGGER.info(CustomStringUtils.STAR);
        LOGGER.info(String.format("* %s %s ", "ADS vs AnyCode", "1.0"));
        LOGGER.info(CustomStringUtils.STAR);
        LOGGER.info(CustomStringUtils.STAR);
        LOGGER.info(CustomStringUtils.LOTS_OF_STARS);
        LOGGER.info(CustomStringUtils.EMPTY);

        boolean useIdFilter = false;
        String filter = null;
        if (args.length == 1) {
            useIdFilter = true;
            filter = args[0];
        }

        final Benchmark[] benchmarks = new JsonLoader().loadFromResource("anycode-benchmarks.json", Benchmark[].class);
        for (Benchmark benchmark : benchmarks) {

            final String id = benchmark.getId();
            if (useIdFilter && !CustomStringUtils.equals(filter, id)) {
                LOGGER.info("Skipping benchmark {}.", id);
                continue;
            }

            LOGGER.info(CustomStringUtils.LOTS_OF_STARS);
            LOGGER.info(benchmark);
            LOGGER.info(CustomStringUtils.LOTS_OF_STARS);

            File statsFile = null;
            File detailsFile = null;
            try {
                statsFile = getEmptyFile(String.format("%s-statistics.log", benchmark.getId()));
                detailsFile = getEmptyFile(String.format("%s-details.log", benchmark.getId()));
            } catch (IOException exception) {
                LOGGER.error("Failed to create log files.", exception);
                return;
            }

            Iterator<Class<? extends NlpScenario>> nlpIt = nlpScenarios.iterator();
            while (nlpIt.hasNext()) {

                final Class<? extends NlpScenario> clazz = nlpIt.next();
                final Scenario nlpA = clazz.getAnnotation(Scenario.class);

                Iterator<Class<? extends JavaMethodSearchScenario>> optIt = optionsScenarios.iterator();
                while (optIt.hasNext()) {

                    final Class<? extends JavaMethodSearchScenario> option = optIt.next();
                    final Scenario optA = option.getAnnotation(Scenario.class);

                    
                    List<JavaMethod> methods = new ArrayList<JavaMethod>();

                    Client client = ClientBuilder.newClient();

                    WebTarget target = client.target("http://localhost:8080/ads").path("api/java/methods/scenarios")
                            .queryParam("input", benchmark.getInput()).queryParam("nlp", nlpA.id()).queryParam("options", optA.id());

                    GenericResource<JavaMethod> resource = null;
                    final Response response = target.request(MediaType.APPLICATION_JSON_TYPE).get();
                    final int status = response.getStatus();
                    if (status == Status.OK.getStatusCode()) {
                        final String jsonString = response.readEntity(String.class);
                        resource = new Gson().fromJson(jsonString, typeToken.getType());
                        methods = resource.getItems();
                    }

                    response.close();
                    client.close();

                    
                    //final List<JavaMethod> methods = client.list(benchmark.getInput(), nlpA.id(), optA.id());
                    final String header = String.format("%s, %s, %s\r\n", nlpA.id(), optA.id(), methods.size());

                    write(statsFile, header);

                    write(detailsFile, header);
                    for (JavaMethod method : methods) {

                        if (method == null) {
                            System.out.println(String.format("WTF? %s %s %s", method, methods,
                                    (methods == null ? "-1" : methods.size())));
                            continue;
                        }

                        write(detailsFile, String.format("%s\r\n", method.toString()));
                    }

                }

            }

            LOGGER.info(CustomStringUtils.LOTS_OF_STARS);

            sleep();

        }

        LOGGER.info(CustomStringUtils.LOTS_OF_STARS);

    }

}
