package org.ads.langs.java.dao.impl;

import com.orientechnologies.orient.core.record.impl.ODocument;
import com.orientechnologies.orient.core.sql.query.OSQLSynchQuery;

import org.ads.Constants;
import org.ads.langs.java.model.JavaMethod;
import org.ads.nlp.UserInput;
import org.ads.orientdb.dao.AbstractDao;
import org.ads.orientdb.utils.OrientDbQuery;
import org.ads.orientdb.utils.OrientDbQuery.OrientDbQueryBuilder;
import org.ads.utils.ConverterUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.function.Consumer;

public class JavaMethodDao extends AbstractDao {

  private static final String[] KNOWN_APACHE_LIBS = new String[] { "org.apache", "apache",
      "commons-io" };
  private static final String[] KNOWN_JDK_LIBS = new String[] { "oracle-jdk-1.8.0_72" };
  private static final String[] KNOWN_TEST_LIBS = new String[] { "junit", "log4j", "org.testng",
      "org.slf4j", "org.mockito" };

  private static final Logger LOGGER = LogManager.getLogger(JavaMethodDao.class);

  /**
   * Constructor.<br />
   */
  public JavaMethodDao() {
    super();
  }

  /**
   * Builds the search string.<br />
   * 
   * @param input
   *          the search {@link String}
   * @param options
   *          the {@link JavaMethodSearchOptions} that represents the search options
   * 
   * @return the search query {@link OrientDbQuery}
   */
  private static OrientDbQuery build(String input, JavaMethodSearchOptions options) {

    OrientDbQueryBuilder builder = new OrientDbQueryBuilder();

    builder.select("$L.fqn", "library_name");

    if (options.isUsePopularityIndex()) {
      builder.select("$L.in(\'depends\').size()", "dependencies").orderBy("dependencies desc");
    }

    builder.select("$O.name", "object_name").select("name", "method_name")
        .select("signature", "method_signature").select("description", "method_description");

    builder.from("javamethod");

    builder.let("L", "in(\'is-part-of\').in()").let("O", "in(\'is-part-of\')");

    OrientDbQueryBuilder.WhereBuilder whereBuilder = builder.where();
    if (CustomStringUtils.isNotEmpty(input)) {
      List<String> luceneFields = new ArrayList<String>();
      if (!options.isIgnoreMethodNames()) {
        luceneFields.add("name");
      }
      if (!options.isIgnoreMethodDescriptions()) {
        luceneFields.add("description");
      }
      whereBuilder
          .and(new OrientDbQuery.LuceneClause(luceneFields.toArray(new String[] {}), input));
    }
    if (options.isUseApacheApis()) {
      whereBuilder.and(new OrientDbQuery.InClause("$L.groupId", KNOWN_APACHE_LIBS));
    }
    if (options.isUseJdkApi()) {
      whereBuilder.and(new OrientDbQuery.InClause("$L.fqn", KNOWN_JDK_LIBS));
    }
    if (options.isExcludeKnownTestApis()) {
      whereBuilder.and(new OrientDbQuery.NotInClause("$L.groupId", KNOWN_TEST_LIBS));
    }

    builder.unwind("library_name").unwind("object_name");

    final int limit = options.getLimit();
    builder.limit((limit > 0) ? limit : Constants.DEFAULT_LIMIT);

    return builder.build();

  }

  /**
   * Gets a list of all the Java methods (of type {@link JavaMethod}) found in a Orient Graph DB.
   * <br />
   * 
   * @return the {@link List} of {@link JavaMethod} found
   */
  public List<JavaMethod> getJavaMethods() {
    return getJavaMethods(null, new JavaMethodSearchOptions());
  }

  /**
   * Gets a list of all the Java methods (of type {@link JavaMethod}) found in a Orient Graph DB.
   * <br />
   * 
   * @param input
   *          the search {@link String}
   * 
   * @return the {@link List} of {@link JavaMethod} found
   */
  public List<JavaMethod> getJavaMethods(String input) {
    return getJavaMethods(input, new JavaMethodSearchOptions());
  }

  /**
   * Gets a list of all the Java methods (of type {@link JavaMethod}) found in a Orient Graph DB.
   * <br />
   * 
   * @param input
   *          the search {@link String}
   * @param options
   *          the {@link JavaMethodSearchOptions} that represents the search options
   * 
   * @return the {@link List} of {@link JavaMethod} found
   */
  public List<JavaMethod> getJavaMethods(String input, JavaMethodSearchOptions options) {

    List<JavaMethod> methods = new ArrayList<JavaMethod>();

    final OrientDbQuery query = build(input, options);
    final OSQLSynchQuery<ODocument> osqlSynchQuery = new OSQLSynchQuery<ODocument>(
        query.toString());
    final int limit = options.getLimit();
    if (limit > 0) {
      osqlSynchQuery.setLimit(limit);
    }

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Searching java methods using query \"{}\"...", query);
    }

    final List<ODocument> results = getTx().getRawGraph().query(osqlSynchQuery);
    results.forEach(new Consumer<ODocument>() {
      @Override
      public void accept(ODocument document) {
        methods.add(ConverterUtils.toJavaMethod(document));
      }
    });

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Search found {} java methods.", methods.size());
    }

    return methods;

  }

  /**
   * Gets a list of all the Java methods (of type {@link JavaMethod}) found in a Orient Graph DB.
   * <br />
   * 
   * @param userInput
   *          the search {@link UserInput}
   * @param options
   *          the {@link JavaMethodSearchOptions} that represents the search options
   * 
   * @return the {@link List} of {@link JavaMethod} found
   */
  public List<JavaMethod> getJavaMethodsUsingThreads(UserInput userInput,
      JavaMethodSearchOptions options) {

    Parameters.requireNonNull(userInput, options);

    List<JavaMethod> methods = new ArrayList<JavaMethod>();

    final Set<String> inputs = userInput.getFinalInputs();

    final int length = inputs.size();
    if (length == 1) {
      return getJavaMethods(inputs.iterator().next(), options);
    }

    ExecutorService executor = Executors.newFixedThreadPool(length);
    inputs.forEach(new Consumer<String>() {
      @Override
      public void accept(String input) {
        executor.execute(new Runnable() {
          @Override
          public void run() {
            methods.addAll(getJavaMethods(input, options));
          }
        });
      }
    });

    executor.shutdown();

    try {
      executor.awaitTermination(Constants.DEFAULT_AWAIT_TIMEOUT_IN_SECONDS, TimeUnit.SECONDS);
    } catch (InterruptedException exception) {
      LOGGER.warn("Failed to await executor termination.", exception);
    }

    return methods;

  }

}
