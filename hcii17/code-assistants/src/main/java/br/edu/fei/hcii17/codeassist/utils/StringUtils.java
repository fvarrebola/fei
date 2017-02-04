package br.edu.fei.hcii17.codeassist.utils;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

/**
 * String handling utility class.<br />
 * 
 */
public class StringUtils {

    /**
     * Checks if an input string starts with any of the provided prefixes.<br />
     * 
     * @param str
     *            the {@link String} representing the input string
     * @param prefixes
     *            the prefixes
     * 
     * @return <code>true</code> if the input string starts with any of the provided prefixes; <code>false</code>
     */
    public static boolean startsWithAny(String str, String... prefixes) {

        if (str == null || prefixes == null || (Array.getLength(prefixes) == 0)) {
            return false;
        }

        for (String prefix : prefixes) {
            if (str.startsWith(prefix)) {
                return true;
            }
        }

        return false;

    }

    /**
     * Splits an input string using the given delimiter.<br />
     * 
     * @param str
     *            the {@link String} representing the input string
     * @param delim
     *            the {@link String} representing the delimiter
     * 
     * @return the array of {@link String} representing the tokens
     */
    public static String[] tokenize(String str, String delim) {

        if (str == null) {
            return null;
        }

        StringTokenizer tokenizer = new StringTokenizer(str, delim);

        final int size = tokenizer.countTokens();
        List<String> tokens = new ArrayList<String>(size);
        while (tokenizer.hasMoreElements()) {
            final String token = tokenizer.nextToken();
            tokens.add(token.trim());
        }

        return tokens.toArray(new String[size]);

    }

    /**
     * Splits an input string using the comma delimiter.<br />
     * 
     * @param str
     *            the {@link String} representing the input string
     * 
     * @return the array of {@link String} representing the tokens
     */
    public static String[] tokenize(String str) {
        return tokenize(str, ",");
    }

}
