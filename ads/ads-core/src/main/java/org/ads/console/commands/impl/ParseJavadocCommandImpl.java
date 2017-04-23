package org.ads.console.commands.impl;

import org.ads.langs.java.docs.parsers.zip.impl.GenericZipFileParserImpl;
import org.ads.utils.CustomFileUtils;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;
import org.apache.commons.io.FilenameUtils;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.io.IOException;
import java.nio.file.FileVisitOption;
import java.nio.file.FileVisitResult;
import java.nio.file.FileVisitor;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.Collections;
import java.util.Set;
import java.util.zip.ZipFile;

/**
 * Command to parse javadocs from the local repository path defined by
 * {@link CustomFileUtils#getLocalRepositoryPath()}. <br />
 * 
 * @author arrebola
 *
 */
public final class ParseJavadocCommandImpl extends AbstractCommand {

  private static final Logger LOGGER = LogManager.getLogger(ParseJavadocCommandImpl.class);

  /**
   * Constructor.<br />
   */
  public ParseJavadocCommandImpl() {
    super();
  }

  @Override
  protected void doExecute() throws Exception {

    Path path = CustomFileUtils.getLocalRepositoryPath();

    Set<FileVisitOption> options = Collections.emptySet();
    final int maxDepth = Integer.MAX_VALUE;

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("Walking file tree starting at {} with max depth of {}.", path, maxDepth);
    }

    int counter = 0;
    Files.walkFileTree(path, options, maxDepth, new FileVisitor<Path>() {

      @Override
      public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs)
          throws IOException {
        return FileVisitResult.CONTINUE;
      }

      @Override
      public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {

        final Path fileNameAsPath = file.getFileName();
        if (CustomObjectUtils.isNull(fileNameAsPath)) {
          return FileVisitResult.CONTINUE;
        }

        final String fileName = fileNameAsPath.toString();

        if (attrs.isRegularFile() && FilenameUtils.isExtension(fileName, "jar")
            && CustomStringUtils.contains(fileName, "javadoc")) {
          try (ZipFile zipFile = new ZipFile(file.toFile())) {
            new GenericZipFileParserImpl().parseFile(zipFile);
          } catch (IOException exception) {
            LOGGER.error("Failed to parse file {}.", fileName);
          }
        }

        return FileVisitResult.CONTINUE;
      }

      @Override
      public FileVisitResult visitFileFailed(Path file, IOException exc) throws IOException {
        return FileVisitResult.CONTINUE;
      }

      @Override
      public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
        return FileVisitResult.CONTINUE;
      }

    });

    if (LOGGER.isInfoEnabled()) {
      LOGGER.info("{} javadoc artifacts were successfully parsed.", counter);
    }

  }

}