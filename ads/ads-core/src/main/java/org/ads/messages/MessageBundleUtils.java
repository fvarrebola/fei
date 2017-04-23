package org.ads.messages;

import org.ads.Constants;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;

import java.text.MessageFormat;
import java.util.Collection;
import java.util.HashSet;
import java.util.ResourceBundle;

/**
 * Mesage bundle utility class.<br />
 * 
 * @author arrebola
 *
 */
public final class MessageBundleUtils {

  private static final String SHELL_BUNDLE_NAME = "config.messages.shell-messages";
  private static final String WEBAPP_BUNDLE_NAME = "config.messages.webapp-messages";

  private Collection<ResourceBundle> bundles;

  private static MessageBundleUtils instance;

  /**
   * Private constructor.<br />
   */
  private MessageBundleUtils() {
    super();
    this.bundles = new HashSet<ResourceBundle>();
    this.bundles.add(ResourceBundle.getBundle(SHELL_BUNDLE_NAME));
    this.bundles.add(ResourceBundle.getBundle(WEBAPP_BUNDLE_NAME));
  }

  /**
   * Gets this class instance.<br />
   * 
   * @return the {@link MessageBundleUtils} instance
   */
  public static MessageBundleUtils getInstance() {
    synchronized (MessageBundleUtils.class) {
      if (instance == null) {
        instance = new MessageBundleUtils();
      }
    }
    return instance;
  }

  /**
   * Gets the message for a given key.<br />
   * 
   * @param key
   *          the {@link String} that represents the key
   * 
   * @return the {@link String} that represents the message
   */
  public String getValue(String key) {

    if (CustomStringUtils.isEmpty(key)) {
      throw new IllegalArgumentException();
    }

    String value = null;

    if (CustomObjectUtils.isNull(this.bundles)) {
      throw new IllegalStateException("Resource bundle should be initialized first.");
    }

    boolean found = false;
    for (ResourceBundle bundle : bundles) {
      if (bundle.containsKey(key)) {
        value = bundle.getString(key);
        found = true;
        break;
      }
    }

    if (!found) {
      value = Constants.UNKNOWN_VALUE_PREFIX + key + Constants.UNKNOWN_VALUE_SUFFIX;
    }

    return value;

  }

  /**
   * Gets the message for a given key.<br />
   * 
   * @param key
   *          the {@link String} that represents the key
   * @param arguments
   *          the {@link Object} to format
   * 
   * @return the {@link String} that represents the message
   */
  public String getValue(String key, Object... arguments) {

    if (CustomStringUtils.isEmpty(key)) {
      throw new IllegalArgumentException();
    }

    return MessageFormat.format(getValue(key), arguments);
  }

}
