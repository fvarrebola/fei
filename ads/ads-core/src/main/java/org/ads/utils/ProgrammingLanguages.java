package org.ads.utils;

import java.util.HashMap;
import java.util.Map;

public enum ProgrammingLanguages {

  ASM, CPLUSPLUS, CSHARP, JAVA, JAVASCRIPT, PHP, PYTHON, PERL, VB;

  private static Map<ProgrammingLanguages, String[]> aliases =
      new HashMap<ProgrammingLanguages, String[]>();

  static {
    aliases.put(ASM, new String[] { "asm", "assembly" });
    aliases.put(CPLUSPLUS, new String[] { "c++", "cplusplus" });
    aliases.put(CSHARP, new String[] { "c#", "csharp" });
    aliases.put(JAVA, new String[] { "java" });
    aliases.put(JAVASCRIPT, new String[] { "js", "javascript" });
    aliases.put(PHP, new String[] { "php" });
    aliases.put(PYTHON, new String[] { "python", "py" });
    aliases.put(PERL, new String[] { "perl" });
    aliases.put(VB, new String[] { "vb", "visual basic" });
  }

  /**
   * Gets the aliases for a given programming language.<br />
   * 
   * @param programmingLanguage
   *          the {@link ProgrammingLanguages} that represents the programming language
   * 
   * @return the array of {@link String} that represents the aliases
   */
  public static String[] aliases(ProgrammingLanguages programmingLanguage) {

    Parameters.requireNonNull(programmingLanguage);

    if (!aliases.containsKey(programmingLanguage)) {
      throw new IllegalArgumentException();
    }

    return aliases.get(programmingLanguage);

  }
}
