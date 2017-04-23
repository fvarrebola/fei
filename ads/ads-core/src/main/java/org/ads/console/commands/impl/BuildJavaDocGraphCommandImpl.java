package org.ads.console.commands.impl;

import org.ads.langs.java.dao.DaoFactory;
import org.ads.langs.java.dao.impl.JavaLibraryDao;
import org.ads.langs.java.dao.impl.JavaObjectDao;
import org.ads.langs.java.docs.parsers.zip.ZipFileParserFactory;
import org.ads.langs.java.docs.parsers.zip.impl.GenericZipFileParserImpl;
import org.ads.langs.java.model.JavaLibrary;
import org.ads.langs.java.model.JavaObject;
import org.ads.orientdb.ex.OrientException;
import org.ads.utils.CustomStringUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.File;
import java.net.URL;
import java.util.List;
import java.util.function.Consumer;

/**
 * Command to add a specific javadoc to the graph.<br />
 * 
 * @author arrebola
 *
 */
public final class BuildJavaDocGraphCommandImpl extends AbstractCommand {

  private static final Logger LOGGER = LogManager.getLogger(BuildJavaDocGraphCommandImpl.class);

  /**
   * Constructor.<br />
   */
  public BuildJavaDocGraphCommandImpl() {
    super();
  }

  @Override
  protected void doExecute() throws Exception {

    JavaLibrary jdk = new JavaLibrary();
    jdk.setGroupId("oracle");
    jdk.setArtifactId("jdk");
    jdk.setVersion("1.8.0_72");
    jdk.setExtension("jar");
    jdk.setPackaging("jar");
    jdk.buildName();

    JavaLibraryDao libraryDao = DaoFactory.getJavaLibraryDao();
    libraryDao.addJavaLibrary(jdk);

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Adding JDK info...");
    }

    final URL url = BuildJavaDocGraphCommandImpl.class.getClassLoader()
        .getResource("config/javadoc/jdk-8u72-docs-all.zip");

    JavaObjectDao objectDao = DaoFactory.getJavaObjectDao();
    objectDao.addJavaObjects(jdk, ZipFileParserFactory
        .getInstance(ZipFileParserFactory.ParserTypes.JDK).parseFile(new File(url.getPath())));

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("JDK info succssfully added.");
    }

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Searching the most popular artifacts so far...");
    }

    final List<JavaLibrary> libraries = libraryDao.getPopularLibraries(true, 1000);
    libraries.forEach(new Consumer<JavaLibrary>() {

      @Override
      public void accept(JavaLibrary library) {
        try {

          if (LOGGER.isInfoEnabled()) {
            LOGGER.info("Getting the most popular version for library {}...", library);
          }

          final JavaLibrary popularLib = libraryDao.getMostPopularVersion(library);
          if (CustomStringUtils.isAnyEmpty(popularLib.getGroupId(), popularLib.getArtifactId())) {
            LOGGER.warn("Could not find the most popular version of library {}.", library);
            return;
          }

          if (CustomStringUtils.isEmpty(popularLib.getFqn())) {
            popularLib.buildName();
          }

          final List<JavaObject> objects = new GenericZipFileParserImpl().search(popularLib);
          if (LOGGER.isInfoEnabled()) {
            LOGGER.info("Library {} parsing has found {} objects.", popularLib, objects.size());
          }

          objectDao.addJavaObjects(popularLib, objects);

        } catch (OrientException exception) {
          LOGGER.error("Failed to add Java library to database.", exception);
        }
      }
    });

  }

}