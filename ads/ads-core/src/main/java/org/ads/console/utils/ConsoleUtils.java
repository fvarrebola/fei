package org.ads.console.utils;

import org.ads.messages.MessageBundleUtils;
import org.ads.messages.ShellMessageConstants;
import org.ads.utils.CustomStringUtils;
import org.ads.utils.Parameters;

import java.util.Scanner;

/**
 * Console utility class.<br />
 * 
 * @author arrebola
 * 
 */
public class ConsoleUtils {

  private static Scanner SCANNER = new Scanner(System.in);
  private static MessageBundleUtils BUNDLE = MessageBundleUtils.getInstance();

  public static void newLine() {
    System.out.println();
  }

  public static void log(Object obj) {
    System.out.println(obj);
  }

  public static void logWithoutCr(Object obj) {
    System.out.print(obj);
  }

  /**
   * Gets an end user option using the console.<br />
   * 
   * @param key
   *          the {@link String} that represents the message key
   * 
   * @return the {@link String} that represents the user option
   */
  public static String getString(String key) {

    String userOpt = null;

    logWithoutCr(BUNDLE.getValue(key) + ": ");

    boolean gotValidOption = false;

    do {

      if (SCANNER.hasNext()) {
        try {
          userOpt = SCANNER.next();
          gotValidOption = CustomStringUtils.isNotEmpty(userOpt);
        } catch (Exception exception) {
          break;
        }

        if (!gotValidOption) {
          log(BUNDLE.getValue(ShellMessageConstants.INVALID_INPUT));
        }
      }

    } while (!gotValidOption);

    return userOpt;
  }

  /**
   * Gets an end user option using the console.<br />
   * 
   * @param key
   *          the {@link String} that represents the message key
   * @param options
   *          the {@link String} vector that represents the available options
   * 
   * @return the {@link String} that represents the
   */
  public static String getString(String key, String[] options) {

    Parameters.requireNonNull(key);

    String userOpt = null;

    log(String.format("%s - %s", BUNDLE.getValue(key),
        BUNDLE.getValue(ShellMessageConstants.AVAILABLE_OPTIONS)));
    int idx = 0;
    for (String option : options) {
      log("\t[" + (++idx) + "] " + option);
    }

    boolean gotValidOption = false;

    do {

      int optIdx = 0;
      logWithoutCr(String.format("%s [1-%d]: ",
          BUNDLE.getValue(ShellMessageConstants.PLEASE_SELECT_AN_OPTION), idx));
      try {
        optIdx = SCANNER.nextInt();
        gotValidOption = (optIdx > 0 && optIdx <= idx);
      } catch (Exception ex) {
        break;
      }

      if (gotValidOption) {
        userOpt = options[optIdx - 1];
      }

    } while (!gotValidOption);

    return userOpt;

  }

  /**
   * Obtém a opção do usuário considerando os valores {@value #YES} e {@value #NO}.
   * 
   * @param msg
   *          o {@link String} que representa a mensagem exibida para o usuário
   * 
   * @return o {@link String} que representa a opção selecionada
   */
  public static String getUserInputAsYesOrNoString(String msg) {
    return getString(msg, new String[] { CustomStringUtils.YES, CustomStringUtils.NO });
  }

  /**
   * Obtém a opção do usuário considerando os valores {@value #YES} e {@value #NO}.
   * 
   * @param msg
   *          o {@link String} que representa a mensagem exibida para o usuário
   * 
   * @return <code>true</code> ou <code>false</code>
   */
  public static boolean getBoolean(String msg) {
    return CustomStringUtils.YES
        .equals(getString(msg, new String[] { CustomStringUtils.YES, CustomStringUtils.NO }));
  }

}
