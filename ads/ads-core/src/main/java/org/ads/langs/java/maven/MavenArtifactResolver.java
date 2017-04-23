package org.ads.langs.java.maven;

import org.ads.Constants;
import org.ads.langs.java.maven.ex.MavenException;
import org.ads.langs.java.model.JavaLibrary;
import org.ads.utils.ConverterUtils;
import org.ads.utils.CustomFileUtils;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.Parameters;
import org.apache.commons.io.FileUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.maven.index.ArtifactInfo;
import org.apache.maven.repository.internal.MavenRepositorySystemUtils;
import org.codehaus.plexus.ContainerConfiguration;
import org.codehaus.plexus.DefaultContainerConfiguration;
import org.codehaus.plexus.DefaultPlexusContainer;
import org.codehaus.plexus.PlexusConstants;
import org.eclipse.aether.DefaultRepositorySystemSession;
import org.eclipse.aether.RepositoryListener;
import org.eclipse.aether.RepositorySystem;
import org.eclipse.aether.artifact.Artifact;
import org.eclipse.aether.collection.CollectRequest;
import org.eclipse.aether.graph.DependencyFilter;
import org.eclipse.aether.repository.LocalRepository;
import org.eclipse.aether.repository.RemoteRepository;
import org.eclipse.aether.resolution.ArtifactDescriptorException;
import org.eclipse.aether.resolution.ArtifactDescriptorRequest;
import org.eclipse.aether.resolution.ArtifactRequest;
import org.eclipse.aether.resolution.ArtifactResolutionException;
import org.eclipse.aether.resolution.ArtifactResult;
import org.eclipse.aether.resolution.DependencyRequest;
import org.eclipse.aether.resolution.DependencyResolutionException;
import org.eclipse.aether.transfer.TransferListener;
import org.eclipse.aether.util.artifact.JavaScopes;
import org.eclipse.aether.util.filter.DependencyFilterUtils;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

/**
 * The Maven repository artifact resolver.<br />
 * It resolves artifacts and its dependencies, downloading them to the local cache. <br />
 * It also reads artifact descriptors, building a Java library model.<br />
 * <b>Note</b>: to provide these kind of functionalities, this class uses not only the Maven indexer
 * API itself, but also the Eclipse's Aether resolver.
 * 
 * @author arrebola
 *
 */
public class MavenArtifactResolver {

  private static final String REPOSITORY_ID = "central";
  private static final String REPOSITORY_TYPE_ID = "default";

  private RepositorySystem system;
  private DefaultRepositorySystemSession session;
  private TransferListener transferListener;
  private RepositoryListener repositoryListener;

  private static MavenArtifactResolver instance;

  private static final Logger LOGGER = LogManager.getLogger(MavenArtifactResolver.class);

  /**
   * Private constructor.<br />
   */
  private MavenArtifactResolver() {
    super();
  }

  /**
   * Private constructor.<br />
   * 
   * @param transferListener
   *          the {@link TransferListener} to be notified during artifact resolution
   * @param repositoryListener
   *          the {@link RepositoryListener} to be notified during artifact resolution
   * 
   */
  private MavenArtifactResolver(TransferListener transferListener,
      RepositoryListener repositoryListener) {
    this();
    this.transferListener = transferListener;
    this.repositoryListener = repositoryListener;
  }

  /**
   * Gets an instance of this class.<br />
   * 
   * @return instance of {@link MavenArtifactResolver}
   */
  public static MavenArtifactResolver getInstance() throws MavenException {
    synchronized (MavenSearchManager.class) {
      if (instance == null) {
        instance = new MavenArtifactResolver();
        instance.initialize();
      }
    }
    return instance;
  }

  /**
   * Gets an instance of this class.<br />
   * 
   * @param transfListener
   *          the {@link TransferListener} to be notified during artifact resolution
   * @param repoListener
   *          the {@link RepositoryListener} to be notified during artifact resolution
   * 
   * @return instance of {@link MavenArtifactResolver}
   */
  public static MavenArtifactResolver getInstance(TransferListener transfListener,
      RepositoryListener repoListener) throws MavenException {
    synchronized (MavenSearchManager.class) {
      if (instance == null) {
        instance = new MavenArtifactResolver(transfListener, repoListener);
        instance.initialize();
      }
    }
    return instance;
  }

  /**
   * Initializes the Plexus container and looks up for the Aether repository system. <br />
   * 
   * @throws MavenException
   *           in case initialization fails
   */
  private void initialize() throws MavenException {

    try {

      ContainerConfiguration config = new DefaultContainerConfiguration();
      config.setAutoWiring(true);
      config.setClassPathScanning(PlexusConstants.SCANNING_INDEX);

      this.system = new DefaultPlexusContainer(config).lookup(RepositorySystem.class);

      LocalRepository localRepository = new LocalRepository(
          CustomFileUtils.getLocalRepositoryPath().toFile());

      this.session = MavenRepositorySystemUtils.newSession();
      session.setLocalRepositoryManager(
          this.system.newLocalRepositoryManager(this.session, localRepository));

      if (CustomObjectUtils.isNotNull(this.transferListener)) {
        session.setTransferListener(this.transferListener);
      }

      if (CustomObjectUtils.isNotNull(this.repositoryListener)) {
        session.setRepositoryListener(this.repositoryListener);
      }

    } catch (Exception exception) {
      throw new IllegalStateException("Dependency injection failed.", exception);
    }

  }

  private List<RemoteRepository> defaultMavenRepositoryAsList() {

    List<RemoteRepository> remoteRepositoryList = new ArrayList<RemoteRepository>();

    RemoteRepository remoteRepository = new RemoteRepository.Builder(REPOSITORY_ID,
        REPOSITORY_TYPE_ID, Constants.DEFAULT_MAVEN_REPOSITORY_URL).build();
    remoteRepositoryList.add(remoteRepository);

    return remoteRepositoryList;

  }

  /**
   * Resolves an artifact downloading its dependencies.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * @param resolveDependencies
   *          <code>true</code> if artifact dependencies should be resolved
   * @param transferListener
   *          the {@link TransferListener} to be notified during artifact resolution;
   *          <code>false</code> otherwise
   * @param repositoryListener
   *          the {@link RepositoryListener} to be notified during artifact resolution
   * 
   * @return <code>true</code> if the artifact is resolved, <code>false</code> otherwise
   * 
   * @throws MavenException
   *           in case the artifact resolution fails
   */
  private boolean doResolveArtifact(ArtifactInfo artifactInfo, boolean resolveDependencies,
      TransferListener transferListener, RepositoryListener repositoryListener)
      throws MavenException {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Resolving artifact {}{}", artifactInfo,
          (resolveDependencies ? " and its dependencies." : "."));
    }

    Artifact artifact = ConverterUtils.mavenToAether(artifactInfo);

    // build the artifact request
    ArtifactRequest artifactRequest = new ArtifactRequest();
    artifactRequest.setArtifact(artifact);
    artifactRequest.setRepositories(defaultMavenRepositoryAsList());

    // build the dependency request
    DependencyFilter dependencyFilter = DependencyFilterUtils.classpathFilter(JavaScopes.COMPILE);
    CollectRequest collectRequest = new CollectRequest();
    collectRequest.setRoot(new org.eclipse.aether.graph.Dependency(artifact, JavaScopes.COMPILE));
    collectRequest.setRepositories(defaultMavenRepositoryAsList());
    DependencyRequest dependencyRequest = new DependencyRequest(collectRequest, dependencyFilter);

    boolean resolved = false;
    try {

      resolved = system.resolveArtifact(session, artifactRequest).isResolved();

      if (resolveDependencies) {
        for (ArtifactResult result : system.resolveDependencies(session, dependencyRequest)
            .getArtifactResults()) {
          resolved &= result.isResolved();
        }
      }

    } catch (ArtifactResolutionException exception) {

      LOGGER.error("Failed to resolve artifact.", exception);
      throw new MavenException(exception);

    } catch (DependencyResolutionException exception) {

      LOGGER.error("Failed to resolve artifact dependencies.", exception);
      throw new MavenException(exception);

    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Artifact {} {} {} resolved.", artifactInfo,
          (resolveDependencies ? "(and its dependencies)" : ""),
          (resolved ? "successfully" : "could not be"));
    }

    return resolved;

  }

  /**
   * Resolves an artifact.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * @param transferListener
   *          the {@link TransferListener} to be notified during artifact resolution
   * @param repositoryListener
   *          the {@link RepositoryListener} to be notified during artifact resolution
   * 
   * @return <code>true</code> if the artifact is resolved, <code>false</code> otherwise
   * 
   * @throws MavenException
   *           in case the artifact resolution fails
   */
  public boolean resolveArtifact(ArtifactInfo artifactInfo, TransferListener transferListener,
      RepositoryListener repositoryListener) throws MavenException {

    Parameters.requireNonNull(artifactInfo, transferListener, repositoryListener);

    return doResolveArtifact(artifactInfo, false, transferListener, repositoryListener);

  }

  /**
   * Resolves an artifact.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * 
   * @return <code>true</code> if the artifact is resolved, <code>false</code> otherwise
   * 
   * @throws MavenException
   *           in case the artifact resolution fails
   */
  public boolean resolveArtifact(ArtifactInfo artifactInfo) throws MavenException {

    Parameters.requireNonNull(artifactInfo);

    return doResolveArtifact(artifactInfo, false, null, null);

  }

  /**
   * Resolves an artifact downloading its dependencies.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * @param transferListener
   *          the {@link TransferListener} to be notified during artifact resolution
   * @param repositoryListener
   *          the {@link RepositoryListener} to be notified during artifact resolution
   * 
   * @return <code>true</code> if the artifact is resolved, <code>false</code> otherwise
   * 
   * @throws MavenException
   *           in case the artifact resolution fails
   */
  public boolean resolveArtifactIncludingDependencies(ArtifactInfo artifactInfo,
      TransferListener transferListener, RepositoryListener repositoryListener)
      throws MavenException {

    Parameters.requireNonNull(artifactInfo, transferListener, repositoryListener);

    return doResolveArtifact(artifactInfo, true, transferListener, repositoryListener);

  }

  /**
   * Resolves an artifact downloading its dependencies.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * 
   * @return <code>true</code> if the artifact is resolved, <code>false</code> otherwise
   * 
   * @throws MavenException
   *           in case the artifact resolution fails
   */
  public boolean resolveArtifactIncludingDependencies(ArtifactInfo artifactInfo)
      throws MavenException {

    Parameters.requireNonNull(artifactInfo);

    return doResolveArtifact(artifactInfo, true, null, null);

  }

  /**
   * Builds an artifact model for a given artifact.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * @param transferListener
   *          the {@link TransferListener} to be notified during artifact resolution
   * @param repositoryListener
   *          the {@link RepositoryListener} to be notified during artifact resolution
   * 
   * @return the {@link JavaLibrary} the represents a Java library
   * 
   * @throws MavenException
   *           in case model building fails
   */
  private JavaLibrary doBuildArtifactModel(ArtifactInfo artifactInfo,
      TransferListener transferListener, RepositoryListener repositoryListener)
      throws MavenException {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Building Maven Indexer API Model for artifact {}.", artifactInfo);
    }

    ArtifactDescriptorRequest request = new ArtifactDescriptorRequest();
    request.setArtifact(ConverterUtils.mavenToAether(artifactInfo));
    request.setRepositories(defaultMavenRepositoryAsList());

    JavaLibrary mavenModel = null;
    try {

      mavenModel = ConverterUtils.fromAether(system.readArtifactDescriptor(session, request));

      mavenModel.setSourceExists(artifactInfo.getSourcesExists().name());
      mavenModel.setJavadocExists(artifactInfo.getJavadocExists().name());
      mavenModel.setLastModified(artifactInfo.getLastModified());

    } catch (ArtifactDescriptorException exception) {
      LOGGER.error("Failed to build artifact model.", exception);
      throw new MavenException(exception);
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Maven Indexer API Model successfully built.");
    }

    return mavenModel;

  }

  /**
   * Builds an artifact model for a given artifact.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * @param transferListener
   *          the {@link TransferListener} to be notified during artifact resolution
   * @param repositoryListener
   *          the {@link RepositoryListener} to be notified during artifact resolution
   * 
   * @return the {@link JavaLibrary} the represents a Java library
   * 
   * @throws MavenException
   *           in case model building fails
   */
  public JavaLibrary buildArtifactModel(ArtifactInfo artifactInfo,
      TransferListener transferListener, RepositoryListener repositoryListener)
      throws MavenException {

    Parameters.requireNonNull(artifactInfo, transferListener, repositoryListener);

    return doBuildArtifactModel(artifactInfo, transferListener, repositoryListener);

  }

  /**
   * Builds an artifact model for a given artifact.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * 
   * @return the {@link JavaLibrary} the represents a Java library
   * 
   * @throws MavenException
   *           in case model building fails
   */
  public JavaLibrary buildArtifactModel(ArtifactInfo artifactInfo) throws MavenException {

    Parameters.requireNonNull(artifactInfo);

    return doBuildArtifactModel(artifactInfo, null, null);

  }

  private File doGetFile(ArtifactInfo artifactInfo) throws MavenException {

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Getting artifact {} file.", artifactInfo);
    }

    // build the artifact request
    ArtifactRequest artifactRequest = new ArtifactRequest();
    artifactRequest.setArtifact(ConverterUtils.mavenToAether(artifactInfo));
    artifactRequest.setRepositories(defaultMavenRepositoryAsList());

    File file = null;
    try {

      ArtifactResult artifactResult = system.resolveArtifact(session, artifactRequest);
      if (artifactResult.isResolved()) {
        file = artifactResult.getArtifact().getFile();
      }

    } catch (Exception exception) {

      LOGGER.info("Failed to get artifact file.", exception);
      throw new MavenException(exception);

    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Artifact file {}.",
          (file == null ? "not found"
              : "found at path " + file.getAbsolutePath() + " ("
                  + FileUtils.byteCountToDisplaySize(file.length()) + ")"));
    }

    return file;

  }

  /**
   * Get an artifact file.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * 
   * @return the {@link File} that represents the artifact file
   * 
   * @throws MavenException
   *           in case artifact resolution fails
   */ 
  public File getFile(ArtifactInfo artifactInfo) throws MavenException {

    Parameters.requireNonNull(artifactInfo);

    return doGetFile(artifactInfo);

  }

}
