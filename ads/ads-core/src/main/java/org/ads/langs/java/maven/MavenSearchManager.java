package org.ads.langs.java.maven;

import org.ads.Constants;
import org.ads.langs.java.maven.ex.MavenException;
import org.ads.utils.CustomFileUtils;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;
import org.apache.commons.io.FileUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.lucene.search.BooleanClause;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Query;
import org.apache.maven.index.AbstractSearchRequest;
import org.apache.maven.index.ArtifactInfo;
import org.apache.maven.index.ArtifactInfoFilter;
import org.apache.maven.index.ArtifactInfoGroup;
import org.apache.maven.index.FlatSearchRequest;
import org.apache.maven.index.FlatSearchResponse;
import org.apache.maven.index.GroupedSearchRequest;
import org.apache.maven.index.GroupedSearchResponse;
import org.apache.maven.index.Grouping;
import org.apache.maven.index.Indexer;
import org.apache.maven.index.IteratorSearchRequest;
import org.apache.maven.index.IteratorSearchResponse;
import org.apache.maven.index.context.IndexCreator;
import org.apache.maven.index.context.IndexingContext;
import org.apache.maven.index.updater.IndexUpdateRequest;
import org.apache.maven.index.updater.IndexUpdater;
import org.apache.maven.index.updater.ResourceFetcher;
import org.apache.maven.index.updater.WagonHelper;
import org.apache.maven.wagon.Wagon;
import org.apache.maven.wagon.events.TransferEvent;
import org.apache.maven.wagon.events.TransferListener;
import org.apache.maven.wagon.observers.AbstractTransferListener;
import org.apache.maven.wagon.resource.Resource;
import org.codehaus.plexus.ContainerConfiguration;
import org.codehaus.plexus.DefaultContainerConfiguration;
import org.codehaus.plexus.DefaultPlexusContainer;
import org.codehaus.plexus.PlexusConstants;
import org.codehaus.plexus.PlexusContainer;

import java.io.IOException;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.function.Consumer;

/**
 * The Maven repository search manager.<br />
 * It creates, updates, searches and deletes the Lucene indexes that a Maven repository supports.
 * <br />
 * There are two type of searches that can be performed using this indexer. A <quote>flat
 * search</quote> returns a set of artifacts to the caller so it is not appropriate for high volume
 * data sets; for scenarios like that the <quote>iterator search</quote> is more appropriate.<br />
 * <b>Note</b>: to provide these kind of functionalities, this class uses not only the Maven indexer
 * API itself, but also the CodeHaus' Plexus container and the Wagon transport abstraction.
 * 
 * @author arrebola
 *
 */
@edu.umd.cs.findbugs.annotations.SuppressWarnings(
    value = { 
        "NP_NULL_PARAM_DEREF_NONVIRTUAL",
        "NP_PARAMETER_MUST_BE_NONNULL_BUT_MARKED_AS_NULLABLE" }, 
    justification = "Null checks are done via CustomObjectUtils")
public class MavenSearchManager {

  private ContainerConfiguration containerConfiguration;
  private PlexusContainer plexusContainer;
  private Indexer indexer;
  private IndexUpdater indexUpdater;
  private Wagon wagon;
  private IndexingContext indexingContext;

  private static final String HTTP = "http";

  private static final String CONTEXT_ID = "context";
  private static final String REPOSITORY_ID = "central";

  private static MavenSearchManager instance;

  private static final Logger LOGGER = LogManager.getLogger(MavenSearchManager.class);

  /**
   * Private constructor.<br />
   */
  private MavenSearchManager() {
    super();
  }

  /**
   * Gets an instance of this class.<br />
   * 
   * @param update
   *          <code>true</code> if the indexes should be updated, otherwise <code>false</code>
   * 
   * @return instance of {@link MavenSearchManager}
   */
  private static MavenSearchManager getInstance(boolean update) throws MavenException {
    synchronized (MavenSearchManager.class) {
      if (instance == null) {
        instance = new MavenSearchManager();
        instance.initialize();
        if (update) {
          instance.update();
        }
      }
    }
    return instance;
  }

  /**
   * Gets an instance of this class.<br />
   * 
   * @return instance of {@link MavenSearchManager}
   */
  public static MavenSearchManager getInstance() throws MavenException {
    return getInstance(false);
  }

  /**
   * Gets an instance of this class, considering that all indexes should be up to date.<br />
   * 
   * @return instance of {@link MavenSearchManager}
   */
  public static MavenSearchManager getUpToDateInstance() throws MavenException {
    return getInstance(true);
  }

  /**
   * Gets the {@link LuceneQueryBuilder}.<br />
   * 
   * @return the {@link LuceneQueryBuilder}
   */
  public LuceneQueryBuilder getQueryBuilder() {
    return new LuceneQueryBuilder(this.indexer);
  }

  /**
   * Initializes the Plexus container and looks up for the Maven indexers and the HTTP Wagon
   * transport mechanism. <br />
   * 
   * @throws MavenException
   *           in case the initialization fails
   */
  private void initialize() throws MavenException {

    Path basePath = CustomFileUtils.getWorkspacePath();

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Initializing MVN indexer for repo {} at local path {}...",
          Constants.DEFAULT_MAVEN_REPOSITORY_URL, basePath);
    }

    this.containerConfiguration = new DefaultContainerConfiguration();
    this.containerConfiguration.setClassPathScanning(PlexusConstants.SCANNING_INDEX);

    try {

      this.plexusContainer = new DefaultPlexusContainer(this.containerConfiguration);
      this.indexer = this.plexusContainer.lookup(Indexer.class);
      this.indexUpdater = this.plexusContainer.lookup(IndexUpdater.class);
      this.wagon = this.plexusContainer.lookup(Wagon.class, HTTP);

      open();

    } catch (Exception exception) {
      LOGGER.fatal("Failed to initialize Maven repository indexer.", exception);
      throw new MavenException(exception);
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Maven repository indexer successfully initialized.");
    }

  }

  /**
   * Creates Lucene indexes for the given Maven remote repository.<br />
   * 
   * @throws MavenException
   *           in case indexes creation fails
   */
  private void open() throws MavenException {

    try {

      CustomFileUtils.createIfNotPresent(CustomFileUtils.getWorkspacePath());

      Path repositoryPath = CustomFileUtils.getLocalRepositoryPath();
      CustomFileUtils.createIfNotPresent(repositoryPath);

      Path indexesPath = CustomFileUtils.getIndexPath();
      CustomFileUtils.createIfNotPresent(indexesPath);
      CustomFileUtils.createIfNotPresent(CustomFileUtils.getLocalRepositoryPath());
      CustomFileUtils.createIfNotPresent(CustomFileUtils.getLogPath());

      List<IndexCreator> indexCreators = new ArrayList<IndexCreator>();
      indexCreators.add(this.plexusContainer.lookup(IndexCreator.class, "min"));
      indexCreators.add(this.plexusContainer.lookup(IndexCreator.class, "jarContent"));
      indexCreators.add(this.plexusContainer.lookup(IndexCreator.class, "maven-plugin"));

      this.indexingContext = this.indexer.createIndexingContext(CONTEXT_ID, REPOSITORY_ID,
          repositoryPath.toFile(), indexesPath.toFile(), Constants.DEFAULT_MAVEN_REPOSITORY_URL,
          null, true, false, indexCreators);

    } catch (Exception exception) {
      LOGGER.fatal("Failed to create Maven repository indexing context.", exception);
      throw new MavenException(exception);
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Lucene indexes successfully created.");
    }

  }

  /**
   * Closes the Maven repository indexing context.<br />
   * 
   * @param deleteFiles
   *          <code>true</code> if all indexer related files (including Lucene index!) needs to be
   *          deleted, <code>false</code> otherwise.
   */
  private void close(boolean deleteFiles) {
    try {
      this.indexer.closeIndexingContext(this.indexingContext, deleteFiles);
    } catch (IOException exception) {
      LOGGER.error("Failed to close indexing context", exception);
    }
  }

  /**
   * Closes the Maven repository indexing context.<br />
   * 
   * @throws IOException
   *           in case closing fails
   */
  public void close() {
    close(false);
  }

  /**
   * Deletes Lucene indexes.<br />
   * 
   * @throws IOException
   *           in case the deletion fails
   */
  public void delete() throws IOException {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Deleting Maven repository indexer...");
    }

    close(true);

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Maven repository indexer successfully deleted");
    }
  }

  /**
   * Updates Lucene indexes for the given Maven remote repository.<br />
   * 
   * @param listener
   *          the {@link TransferListener} to notify during resources download
   * @throws MavenException
   *           in case the update fails
   */
  public void update(TransferListener listener) throws MavenException {

    Parameters.requireNonNull(listener);

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Updating lucene indexes (this may take a moment or two)...");
    }

    ResourceFetcher resourceFetcher = new WagonHelper.WagonFetcher(this.wagon, listener, null,
        null);

    IndexUpdateRequest updateRequest = new IndexUpdateRequest(this.indexingContext,
        resourceFetcher);
    updateRequest.setLocalIndexCacheDir(CustomFileUtils.getIndexCachePath().toFile());

    try {
      this.indexUpdater.fetchAndUpdateIndex(updateRequest);
    } catch (IOException exception) {
      LOGGER.fatal("Failed to update lucene indexes.", exception);
      throw new MavenException(exception);
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Lucene indexes successfully updated.");
    }

  }

  /**
   * Updates Lucene indexes for the given Maven remote repository.<br />
   * 
   * @throws MavenException
   *           in case the update fails
   */
  public void update() throws MavenException {

    TransferListener listener = new AbstractTransferListener() {

      private final String transferEventResourceToString(TransferEvent transferEvent) {

        Resource resource = transferEvent.getResource();
        if (CustomObjectUtils.isNull(resource)) {
          return CustomStringUtils.EMPTY;
        }

        return String.format("%s (%s)", resource.getName(),
            FileUtils.byteCountToDisplaySize(resource.getContentLength()));

      }

      @Override
      public void transferStarted(TransferEvent transferEvent) {
        if (LOGGER.isInfoEnabled()) {
          LOGGER.info("Downloading {}.", transferEventResourceToString(transferEvent));
        }
      }

      @Override
      public void transferProgress(TransferEvent transferEvent, byte[] buffer, int length) {
      }

      @Override
      public void transferCompleted(TransferEvent transferEvent) {
        if (LOGGER.isInfoEnabled()) {
          LOGGER.info("Downloaded {}.", transferEventResourceToString(transferEvent));
        }
      }
    };

    update(listener);

  }

  /**
   * Dumps a query using this class logger.<br />
   * 
   * @param query
   *          the {@link Query} to be dumped
   */
  private static void dumpQuery(Query query) {

    if (!LOGGER.isDebugEnabled()) {
      LOGGER.warn("Query clauses will not be dumped since DEBUG logger level is disabled.");
      return;
    }

    LOGGER.debug("Query is an instance of {}.", query.getClass());
    if (query instanceof BooleanQuery) {
      int idx = 0;
      BooleanClause[] clauses = ((BooleanQuery) query).getClauses();
      for (BooleanClause clause : clauses) {
        LOGGER.debug("[{}] {}, occur = {}, isProhibited = {}, isRequired = {}.", ++idx,
            clause.getQuery().toString(), clause.getOccur(), clause.isProhibited(),
            clause.isRequired());
      }
    } else {
      LOGGER.debug("{}.", query.toString());
    }

  }

  /**
   * Runs a flat search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * @param filter
   *          the {@link ArtifactInfoFilter} used to filter out artifacts
   * @param count
   *          the count of wanted results
   * 
   * @return the {@link Set} of {@link ArtifactInfo} that represents the search results
   */
  private Set<ArtifactInfo> runFlatSearch(Query query, ArtifactInfoFilter filter, int count)
      throws MavenException {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Searching lucene indexes using flat search type...");
    }

    dumpQuery(query);

    Set<ArtifactInfo> results = Collections.emptySet();

    FlatSearchRequest request = new FlatSearchRequest(query, this.indexingContext);
    if (count > 0) {
      request.setCount(count);
    }

    if (CustomObjectUtils.isNotNull(filter)) {
      request.setArtifactInfoFilter(filter);
    }

    try {

      FlatSearchResponse response = null;
      synchronized (MavenSearchManager.class) {
        response = this.indexer.searchFlat(request);
      }

      if (CustomObjectUtils.isNull(response)) {
        throw new IOException("Empty response");
      }

      if (LOGGER.isInfoEnabled()) {
        LOGGER.info("Found {} entries.", response.getTotalHitsCount());
      }
      results = response.getResults();

    } catch (IOException exception) {
      LOGGER.error("Search failed.", exception);
      throw new MavenException(exception);
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Lucene indexes flat search successfully completed");
    }

    return results;
  }

  /**
   * Runs a flat search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * @param filter
   *          the {@link ArtifactInfoFilter} used to filter out artifacts
   * @param count
   *          the count of wanted results
   * 
   * @return the {@link Set} of {@link ArtifactInfo} that represents the search results
   */

  public Set<ArtifactInfo> searchFlat(Query query, ArtifactInfoFilter filter, int count)
      throws MavenException {

    Parameters.requireNonNull(query, filter);

    return runFlatSearch(query, filter, count);

  }

  /**
   * Runs a flat search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * @param filter
   *          the {@link ArtifactInfoFilter} used to filter out artifacts
   * 
   * @return the {@link Set} of {@link ArtifactInfo} that represents the search results
   */

  public Set<ArtifactInfo> searchFlat(Query query, ArtifactInfoFilter filter)
      throws MavenException {

    Parameters.requireNonNull(query, filter);

    return runFlatSearch(query, filter, AbstractSearchRequest.UNDEFINED);
  }

  /**
   * Runs a flat search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * @param count
   *          the count of wanted results
   * 
   * @return the {@link Set} of {@link ArtifactInfo} that represents the search results
   */

  public Set<ArtifactInfo> searchFlat(Query query, int count) throws MavenException {

    Parameters.requireNonNull(query);

    return runFlatSearch(query, null, count);
  }

  /**
   * Runs a flat search in the Lucene indexes of a Maven repository using the query given as input
   * parameter.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * 
   * @return the {@link Set} of {@link ArtifactInfo} that represents the search results
   */

  public Set<ArtifactInfo> searchFlat(Query query) throws MavenException {

    Parameters.requireNonNull(query);

    return runFlatSearch(query, null, AbstractSearchRequest.UNDEFINED);
  }

  /**
   * Runs an iterator search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * @param filter
   *          the {@link ArtifactInfoFilter} used to filter out artifacts
   * @param limit
   *          the count of wanted results
   * @param page
   *          the desired page
   * @param pageSize
   *          the page size
   * 
   * @return the {@link Iterator} of {@link ArtifactInfo} that represents a iterator search response
   * 
   * @throws MavenException
   *           in case the search fails
   */
  private Iterator<ArtifactInfo> runIteratorSearch(Query query, ArtifactInfoFilter filter,
      int limit, int page, int pageSize) throws MavenException {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Searching Lucene indexes using iterator search type...");
    }

    dumpQuery(query);

    Iterator<ArtifactInfo> iterator = Collections.emptyIterator();
    try {

      IteratorSearchRequest request = new IteratorSearchRequest(query, this.indexingContext);

      if (CustomObjectUtils.isNotNull(filter)) {
        request.setArtifactInfoFilter(filter);
      }

      request.setLuceneExplain(true);

      if (limit > 0) {
        request.setCount(limit);
      } else if (pageSize > 0) {
        request.setCount(pageSize);
        if (page > 1) {
          request.setStart((page - 1) * pageSize);
        }
      }

      IteratorSearchResponse response = null;
      synchronized (MavenSearchManager.class) {
        response = this.indexer.searchIterator(request);
      }

      if (CustomObjectUtils.isNull(response)) {
        throw new IOException("Empty response");
      }

      if (LOGGER.isInfoEnabled()) {
        LOGGER.info("Found {} entries.", response.getTotalHitsCount());
      }

      iterator = response.iterator();

    } catch (IOException exception) {
      LOGGER.error("Search failed.", exception);
      throw new MavenException(exception);
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Lucene indexes iterator search successfully completed.");
    }

    return iterator;
  }

  /**
   * Runs an iterator search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * @param consumer
   *          the {@link Consumer} for the search results
   * 
   * @throws MavenException
   *           in case the search fails
   */
  public void searchIterator(Query query, ArtifactInfoFilter filter,
      Consumer<? super ArtifactInfo> consumer) throws MavenException {

    Parameters.requireNonNull(query, filter, consumer);

    runIteratorSearch(query, filter, Constants.UNDEFINED_AS_INT, Constants.UNDEFINED_AS_INT,
        Constants.UNDEFINED_AS_INT).forEachRemaining(consumer);

  }

  /**
   * Runs an iterator search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * @param consumer
   *          the {@link Consumer} for the search results
   * @param limit
   *          the count of wanted results
   * @param page
   *          the desired page
   * @param pageSize
   *          the page size
   * 
   * @throws MavenException
   *           in case the search fails
   */
  public void searchIterator(Query query, Consumer<? super ArtifactInfo> consumer, int limit,
      int page, int pageSize) throws MavenException {

    Parameters.requireNonNull(query, consumer);

    runIteratorSearch(query, null, limit, page, pageSize).forEachRemaining(consumer);

  }

  /**
   * Runs an iterator search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * @param filter
   *          the {@link ArtifactInfoFilter} to filter out artifacts
   * @param consumer
   *          the {@link Consumer} for the search results
   * @param limit
   *          the count of wanted results
   * @param page
   *          the desired page
   * @param pageSize
   *          the page size
   * 
   * @throws MavenException
   *           in case the search fails
   */
  public void searchIterator(Query query, ArtifactInfoFilter filter,
      Consumer<? super ArtifactInfo> consumer, int limit, int page, int pageSize)
      throws MavenException {

    Parameters.requireNonNull(query, filter, consumer);

    runIteratorSearch(query, filter, limit, page, pageSize).forEachRemaining(consumer);

  }

  /**
   * Runs an iterator search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * @param consumer
   *          the {@link Consumer} for the search results
   * 
   * @throws MavenException
   *           in case the search fails
   */
  public void searchIterator(Query query, Consumer<? super ArtifactInfo> consumer)
      throws MavenException {

    Parameters.requireNonNull(query, consumer);

    runIteratorSearch(query, null, Constants.UNDEFINED_AS_INT, Constants.UNDEFINED_AS_INT,
        Constants.UNDEFINED_AS_INT).forEachRemaining(consumer);

  }

  /**
   * Runs an iterator search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * 
   * @throws MavenException
   *           in case the search fails
   */

  public Iterator<ArtifactInfo> searchIterator(Query query) throws MavenException {

    Parameters.requireNonNull(query);

    return runIteratorSearch(query, null, Constants.UNDEFINED_AS_INT, Constants.UNDEFINED_AS_INT,
        Constants.UNDEFINED_AS_INT);

  }

  /**
   * Runs an iterator search.<br />
   * 
   * @param query
   *          the {@link Query} to be used by this search
   * 
   * @throws MavenException
   *           in case the search fails
   */

  public Iterator<ArtifactInfo> searchIterator(Query query, ArtifactInfoFilter filter)
      throws MavenException {

    Parameters.requireNonNull(query, filter);

    return runIteratorSearch(query, filter, Constants.UNDEFINED_AS_INT, Constants.UNDEFINED_AS_INT,
        Constants.UNDEFINED_AS_INT);

  }

  private Map<String, ArtifactInfoGroup> runGroupedSearch(Query query, Grouping grouping, int limit)
      throws MavenException {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Searching Lucene indexes using grouped search type.");
    }

    dumpQuery(query);

    Map<String, ArtifactInfoGroup> map = Collections.emptyMap();

    try {

      GroupedSearchRequest request = new GroupedSearchRequest(query, grouping,
          this.indexingContext);

      if (limit > 0) {
        request.setCount(limit);
      }

      GroupedSearchResponse response = this.indexer.searchGrouped(request);

      if (LOGGER.isInfoEnabled()) {
        LOGGER.info("Found {} entries.", response.getTotalHitsCount());
      }

      map = response.getResults();

    } catch (IOException exception) {
      LOGGER.error("Search failed.", exception);
      throw new MavenException(exception);
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Lucene indexes grouped search successfully completed.");
    }

    return map;

  }

  public Map<String, ArtifactInfoGroup> searchGrouped(Query query, Grouping grouping)
      throws MavenException {

    Parameters.requireNonNull(query, grouping);

    return runGroupedSearch(query, grouping, Constants.UNDEFINED_AS_INT);

  }

}
