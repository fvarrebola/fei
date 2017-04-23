package org.ads.langs.java.dao;

import org.ads.langs.java.dao.impl.JavaLibraryDao;
import org.ads.langs.java.dao.impl.JavaMethodDao;
import org.ads.langs.java.dao.impl.JavaObjectDao;

/**
 * A simple DAO factory.<br />
 * 
 * @author arrebola
 *
 */
public class DaoFactory {

  /**
   * Gets a new instance of the JavaLibraryDAO.<br />
   * 
   * @return the {@link JavaLibraryDao} instance
   */
  public static JavaLibraryDao getJavaLibraryDao() {
    return new JavaLibraryDao();
  }

  /**
   * Gets a new instance of the JavaObjectDAOImpl.<br />
   * 
   * @return the {@link JavaObjectDao} instance
   */
  public static JavaObjectDao getJavaObjectDao() {
    return new JavaObjectDao();
  }

  /**
   * Gets a new instance of the JavaMethodDAOImpl.<br />
   * 
   * @return the {@link JavaMethodDao} instance
   */
  public static JavaMethodDao getJavaMethodDao() {
    return new JavaMethodDao();
  }

}
