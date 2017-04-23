package org.ads.console.commands.impl;

import org.ads.Constants;
import org.ads.langs.java.dao.impl.JavaLibraryDao;
import org.ads.langs.java.maven.MavenArtifactResolver;
import org.ads.langs.java.maven.MvnClassifiers;
import org.ads.langs.java.maven.ex.MavenException;
import org.ads.langs.java.model.JavaLibrary;
import org.ads.utils.ConverterUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.maven.index.ArtifactInfo;

import java.util.Collection;
import java.util.function.Consumer;

/**
 * Command to resolve the most popular artifacts found in our popularity graph.<br />
 * 
 * @author arrebola
 *
 */
public class ResolveArtifactCommandImpl extends AbstractCommand {

  private static final Logger LOGGER = LogManager.getLogger(ResolveArtifactCommandImpl.class);

  /**
   * Constructor.<br />
   */
  public ResolveArtifactCommandImpl() {
    super();
  }

  @Override
  protected void doExecute() throws Exception {

    MavenArtifactResolver resolver = MavenArtifactResolver.getInstance();
    JavaLibraryDao libraryMgr = new JavaLibraryDao();

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Searching popular libraries...");
    }

    Collection<JavaLibrary> collection = libraryMgr.getPopularLibraries(true,
        Constants.MAX_LIMIT_AS_INT);
    final int size = collection.size();

    if (size == 0) {
      LOGGER.warn("No libraries found.");
      return;
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Resolving {} artifacts...", size);
    }

    collection.forEach(new Consumer<JavaLibrary>() {
      @Override
      public void accept(JavaLibrary javaLibrary) {
        try {

          ArtifactInfo artifactInfo = ConverterUtils
              .toMaven(libraryMgr.getMostPopularVersion(javaLibrary));

          artifactInfo.setClassifier(MvnClassifiers.JAVADOC.classifier());
          resolver.resolveArtifact(artifactInfo);

          artifactInfo.setClassifier(MvnClassifiers.SOURCES.classifier());
          resolver.resolveArtifact(artifactInfo);

        } catch (MavenException mavenException) {
          LOGGER.error("Failed to resolve artifact.", mavenException);
        }
      }
    });

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("All libraries successfully resolved.");
    }

  }

}
