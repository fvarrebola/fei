package org.ads.langs.java.docs.parsers.zip;

import org.ads.langs.java.docs.parsers.html.HtmlFileParser;
import org.ads.langs.java.model.JavaObject;

import java.io.File;
import java.util.List;
import java.util.zip.ZipFile;

/**
 * Interface for the <code>allclasses-frame.html</code> file parsers.<br />
 * 
 * @author arrebola
 *
 */
public interface ZipFileParser {

  /**
   * All classes file name.<br />
   */
  public static final String ALL_CLASSES_FRAME_FILE = "allclasses-frame.html";

  /**
   * Parses a {@link File} for a {@link List} of {@link JavaObject}.<br />
   * Note that this function assumes that the file is a {@link ZipFile} and that it contains a
   * {@link HtmlFileParser#ALL_CLASSES_FRAME_FILE} file is present.<br />
   * 
   * @param file
   *          the {@link File} to be parsed
   * 
   * @return the {@link List} of {@link JavaObject} found in the {@link File}F
   * 
   */
  public abstract List<JavaObject> parseFile(File file);

  /**
   * Parses a {@link ZipFile} for a {@link List} of {@link JavaObject}.<br />
   * Note that this function assumes that a {@link HtmlFileParser#ALL_CLASSES_FRAME_FILE} file is
   * present.<br />
   * 
   * @param zipFile
   *          the {@link ZipFile} to be parsed
   * 
   * @return the {@link List} of {@link JavaObject} found in the {@link ZipFile}
   * 
   */
  public abstract List<JavaObject> parseFile(ZipFile zipFile);

}
