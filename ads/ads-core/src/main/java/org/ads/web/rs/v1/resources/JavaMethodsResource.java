package org.ads.web.rs.v1.resources;

import org.ads.Constants;
import org.ads.langs.java.dao.DaoFactory;
import org.ads.langs.java.dao.impl.JavaMethodDao;
import org.ads.langs.java.dao.impl.JavaMethodSearchOptions;
import org.ads.langs.java.model.JavaMethod;
import org.ads.nlp.NlpParser;
import org.ads.nlp.NlpParserOptions;
import org.ads.nlp.UserInput;
import org.ads.nlp.ex.NlpException;
import org.ads.scenarios.Scenario;
import org.ads.scenarios.java.JavaMethodSearchScenario;
import org.ads.scenarios.java.JavaMethodSearchScenarioFactory;
import org.ads.scenarios.java.impl.DefaultSearchScenarioImpl;
import org.ads.scenarios.nlp.NlpScenario;
import org.ads.scenarios.nlp.NlpScenarioFactory;
import org.ads.scenarios.nlp.impl.DefaultNlpScenarioImpl;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.web.rs.AbstractResource;
import org.ads.web.rs.Errors;
import org.ads.web.rs.GenericResource;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.function.BiConsumer;

import javax.ws.rs.DefaultValue;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.Response.Status;

@Path("/methods")
public class JavaMethodsResource extends AbstractResource {

  /**
   * Constructor.<br />
   */
  public JavaMethodsResource() {
    super();
  }

  /**
   * Gets a list of all the Java methods.<br />
   * 
   * @param input
   *          the {@link String} that represents the search string
   * @param nlpOptions
   *          the {@link NlpParserOptions} that represents the NLP search options
   * @param searchOptions
   *          the {@link JavaMethodSearchOptions} that represents the search options
   * 
   * @return the {@link List} of {@link JavaMethod} found
   * 
   * @throws NlpException
   *           in case a NLP operation fails
   */
  private static List<JavaMethod> search(String input, NlpParserOptions nlpOptions,
      JavaMethodSearchOptions searchOptions) throws NlpException {

    List<JavaMethod> items = new ArrayList<JavaMethod>();

    JavaMethodDao javaMethodDao = DaoFactory.getJavaMethodDao();

    if (CustomStringUtils.isEmpty(input)) {
      items = javaMethodDao.getJavaMethods();
    } else {
      final UserInput userInput = NlpParser.getInstance().parse(input, nlpOptions);
      items = javaMethodDao.getJavaMethodsUsingThreads(userInput, searchOptions);
    }

    return items;
  }

  @GET
  @Produces(MediaType.APPLICATION_JSON)
  public Response listMethods(
      @QueryParam("input") @DefaultValue(CustomStringUtils.EMPTY) String input,
      @QueryParam("nlp_lemma") boolean lemma,
      @QueryParam("nlp_join") boolean join,
      @QueryParam("nlp_use1stVbNn") boolean use1stVbANn,
      @QueryParam("nlp_useSyns") boolean useSyns,
      @QueryParam("nlp_useVbSynsOnly") boolean useVbSynsOnly,
      @QueryParam("search_ignoreMethodNames") boolean ignoreMethodNames,
      @QueryParam("search_ignoreMethodDescriptions") boolean ignoreMethodDescriptions,
      @QueryParam("search_usePopularityIndex") boolean usePopularityIndex,
      @QueryParam("search_excludeTestApis") boolean excludeTestApis,
      @QueryParam("search_useJDKApi") boolean useJdkApi,
      @QueryParam("search_useApacheApi") boolean useApacheApis,
      @QueryParam("search_limit") @DefaultValue(Constants.MAX_LIMIT_AS_STRING) int limit,
      @QueryParam("search_page") @DefaultValue(Constants.UNDEFINED_AS_STRING) int page,
      @QueryParam("search_pageSize") @DefaultValue(Constants.UNDEFINED_AS_STRING) int pageSize,
      @QueryParam("prettyPrint") boolean prettyPrint) {

    checkSearchParameters(limit, page, pageSize);

    GenericResource<JavaMethod> resource = new GenericResource<JavaMethod>();

    try {

      NlpParserOptions nlpOptions = new NlpParserOptions();
      nlpOptions.setLemma(lemma);
      nlpOptions.setJoin(join);
      nlpOptions.setUse1stVbNn(use1stVbANn);
      nlpOptions.setUseSyns(useSyns);
      nlpOptions.setUseVbSynsOnly(useVbSynsOnly);

      JavaMethodSearchOptions searchOptions = new JavaMethodSearchOptions();
      searchOptions.setExcludeKnownTestApis(excludeTestApis);
      searchOptions.setUseApacheApis(useApacheApis);
      searchOptions.setUseJdkApi(useJdkApi);
      searchOptions.setIgnoreMethodDescriptions(ignoreMethodDescriptions);
      searchOptions.setIgnoreMethodNames(ignoreMethodNames);
      searchOptions.setUsePopularityIndex(usePopularityIndex);
      searchOptions.setLimit(limit);
      searchOptions.setPage(page);
      searchOptions.setPageSize(pageSize);

      resource.setItems(search(input, nlpOptions, searchOptions));

    } catch (Throwable throwable) {
      return fail(Status.INTERNAL_SERVER_ERROR, Errors.SYSTEM_FAILURE, throwable);
    }

    return ok(resource, prettyPrint);

  }

  static class RegisteredObject {

    String id;
    String name;
    String description;

    public RegisteredObject(String id, String name, String description) {
      super();
      this.id = id;
      this.name = name;
      this.description = description;
    }

  }

  private static <T> List<RegisteredObject> getScenarios(
      Map<String, Class<? extends T>> registeredObjects) {

    List<RegisteredObject> scenarios = new ArrayList<RegisteredObject>();

    registeredObjects.forEach(new BiConsumer<String, Class<?>>() {
      @Override
      public void accept(String key, Class<?> value) {
        final Scenario scenario = value.getAnnotation(Scenario.class);
        if (CustomObjectUtils.isNotNull(scenario)) {
          scenarios
              .add(new RegisteredObject(scenario.id(), scenario.name(), scenario.description()));
        }
      }
    });

    Collections.sort(scenarios, new Comparator<RegisteredObject>() {
      @Override
      public int compare(RegisteredObject o1, RegisteredObject o2) {
        return o1.id.compareTo(o2.id);
      }
    });

    return scenarios;

  }

  @GET
  @Path("scenarios/nlp")
  @Produces(MediaType.APPLICATION_JSON)
  public Response listNlpScenarios() {

    GenericResource<RegisteredObject> resource = new GenericResource<RegisteredObject>();
    try {
      resource.setItems(getScenarios(new NlpScenarioFactory().getRegisteredObjects()));
    } catch (Throwable throwable) {
      return fail(Status.BAD_REQUEST);
    }

    return ok(resource);

  }

  @GET
  @Path("scenarios/search")
  @Produces(MediaType.APPLICATION_JSON)
  public Response listSearchScenarios() {

    GenericResource<RegisteredObject> resource = new GenericResource<RegisteredObject>();
    try {
      resource.setItems(getScenarios(new JavaMethodSearchScenarioFactory().getRegisteredObjects()));
    } catch (Throwable throwable) {
      return fail(Status.BAD_REQUEST);
    }

    return ok(resource);

  }

  @GET
  @Path("scenarios")
  @Produces(MediaType.APPLICATION_JSON)
  public Response searchMethods(
      @QueryParam("input") @DefaultValue(CustomStringUtils.EMPTY) String input,
      @QueryParam("nlp") @DefaultValue(CustomStringUtils.EMPTY) String nlp,
      @QueryParam("options") @DefaultValue(CustomStringUtils.EMPTY) String options) {

    GenericResource<JavaMethod> resource = new GenericResource<JavaMethod>();

    NlpScenario scenario = null;
    try {
      scenario = new NlpScenarioFactory().getObject(nlp);
    } catch (Throwable throwable) {
      scenario = new DefaultNlpScenarioImpl();
    }

    JavaMethodSearchScenario searchScenario = null;
    try {
      searchScenario = new JavaMethodSearchScenarioFactory().getObject(options);
    } catch (Throwable throwable) {
      searchScenario = new DefaultSearchScenarioImpl();
    }

    try {
      resource.setItems(search(input, scenario.getOptions(), searchScenario.getOptions()));
    } catch (Throwable throwable) {
      return fail(Status.INTERNAL_SERVER_ERROR, resource, Errors.SYSTEM_FAILURE, throwable);
    }

    return ok(resource);

  }

}
