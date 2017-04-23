package org.ads.console;

import org.ads.console.commands.Command;
import org.ads.console.commands.impl.BuildPopularityGraphCommandImpl;
import org.ads.console.commands.impl.ManageMvnIndexesCommandImpl;
import org.ads.console.commands.impl.ParseJavadocCommandImpl;
import org.ads.console.commands.impl.ResolveArtifactCommandImpl;
import org.ads.console.commands.impl.SearchMavenRepositoryCommandImpl;
import org.ads.console.utils.ConsoleUtils;
import org.ads.messages.MessageBundleUtils;
import org.ads.messages.ShellMessageConstants;
import org.ads.utils.CustomObjectUtils;
import org.ads.utils.CustomStringUtils;

import java.util.HashMap;
import java.util.Map;

/**
 * Command shell utilities.<br />
 * 
 * @author arrebola
 *
 */
public class Main {

  private static final String NAME = "API Search Console";
  private static final String VERSION = "1.0";

  private static final String MANAGE_INDEXES_COMMAND = "Manage MVN Lucene indexes (!)";
  private static final String SEARCH_MVN_COMMAND = "Search MVN";
  private static final String RESOLVE_ARTIFACT_COMMAND = "Resolve MVN artifact";
  private static final String BUILD_POPULARITY_GRAPH_COMMAND = "Build popularity graph";
  private static final String PARSE_JAVADOC_COMMAND = "Parse Javadocs";
  private static final String EXIT = "Exit";

  private static final String[] KNOWN_COMMANDS_AS_STRING_ARRAY;
  private static final Map<String, Command> KNOWN_COMMANDS_MAP = new HashMap<String, Command>();

  static {
    KNOWN_COMMANDS_MAP.put(MANAGE_INDEXES_COMMAND, new ManageMvnIndexesCommandImpl());
    KNOWN_COMMANDS_MAP.put(SEARCH_MVN_COMMAND, new SearchMavenRepositoryCommandImpl());
    KNOWN_COMMANDS_MAP.put(RESOLVE_ARTIFACT_COMMAND, new ResolveArtifactCommandImpl());
    KNOWN_COMMANDS_MAP.put(BUILD_POPULARITY_GRAPH_COMMAND, new BuildPopularityGraphCommandImpl());
    KNOWN_COMMANDS_MAP.put(PARSE_JAVADOC_COMMAND, new ParseJavadocCommandImpl());
    KNOWN_COMMANDS_MAP.put(EXIT, null);
    KNOWN_COMMANDS_AS_STRING_ARRAY = KNOWN_COMMANDS_MAP.keySet()
        .toArray(new String[KNOWN_COMMANDS_MAP.size()]);
  }

  /**
   * Entry point.<br />
   * 
   * @param args
   *          the {@link String} vector that represents the input parameters
   */
  public static void main(String[] args) {

    ConsoleUtils.newLine();
    ConsoleUtils.log(CustomStringUtils.LOTS_OF_STARS);
    ConsoleUtils.log(String.format("*\n* %s %s\n*", NAME, VERSION));
    ConsoleUtils.log(CustomStringUtils.LOTS_OF_STARS);
    ConsoleUtils.newLine();

    MessageBundleUtils.getInstance();

    Command command = null;

    do {
      command = KNOWN_COMMANDS_MAP.get(ConsoleUtils
          .getString(ShellMessageConstants.CHOOSE_YOUR_COMMAND, KNOWN_COMMANDS_AS_STRING_ARRAY));
      if (CustomObjectUtils.isNotNull(command)) {
        command.execute();
        ConsoleUtils.newLine();
      }

    } while (CustomObjectUtils.isNotNull(command));

    ConsoleUtils.newLine();
    ConsoleUtils.log(CustomStringUtils.LOTS_OF_STARS);

  }

}
