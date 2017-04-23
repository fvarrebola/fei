package org.ads.utils;

import org.apache.commons.io.FilenameUtils;

import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

/**
 * Utility class for handling file names.<br />
 * 
 * @author arrebola
 *
 */
public class CustomFilenameUtils extends FilenameUtils {

  /**
   * Gets a ZIP entry distinguished name, that is, a combination between the ZIP file name and the
   * entry's name.<br />
   * 
   * @param file
   *          the {@link ZipFile} that represents the file
   * @param entry
   *          the {@link ZipEntry} that represents the entry
   * @return the {@link String} that represents the ZIP entry distinguished name
   */
  public static String getZipEntryDn(ZipFile file, ZipEntry entry) {

    Parameters.requireNonNull(file, entry);

    return getName(file.getName()) + "!" + entry.getName();

  }
}
