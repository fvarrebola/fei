package org.ads;

import org.apache.commons.lang3.RandomStringUtils;

public class TestUtils {

  private static int DEFAULT_RANDOM_STRING_LEN = 32;
  private static int MAX_RANDOM_STRING_LEN = 256;

  public static boolean isIllegalArgumentException(Exception exception) {
    return (exception instanceof IllegalArgumentException);
  }

  public static String randomString(int size) {
    return RandomStringUtils.randomAlphanumeric((size == 0 ? DEFAULT_RANDOM_STRING_LEN
        : (size > MAX_RANDOM_STRING_LEN ? MAX_RANDOM_STRING_LEN : size)));
  }

  public static String randomString() {
    return randomString(DEFAULT_RANDOM_STRING_LEN);
  }

}
