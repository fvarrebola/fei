package org.ads.orientdb.dao;

import com.tinkerpop.blueprints.impls.orient.OrientGraph;
import com.tinkerpop.blueprints.impls.orient.OrientGraphNoTx;

import org.ads.orientdb.ex.OrientException;
import org.ads.orientdb.utils.OrientDbGraphFactory;

/**
 * Abstract DAO.<br />
 * 
 * @author arrebola
 *
 */
public abstract class AbstractDao {

  /**
   * Constructor.<br />
   */
  public AbstractDao() {
    super();
  }

  /**
   * Gets transactional graph with the database.<br />
   * 
   * @return the {@link OrientGraph} transactional graph
   * 
   */
  protected static OrientGraph getTx() {
    OrientGraph tx = null;
    try {
      tx = OrientDbGraphFactory.getInstance().getTx();
    } catch (OrientException exception) {
      throw new IllegalStateException(exception);
    }
    return tx;
  }

  /**
   * Gets non transactional graph with the database.<br />
   * 
   * @return the {@link OrientGraph} non transactional graph
   */
  protected static OrientGraphNoTx getNoTx() {
    OrientGraphNoTx noTx = null;
    try {
      noTx = OrientDbGraphFactory.getInstance().getNoTx();
    } catch (OrientException exception) {
      throw new IllegalStateException(exception);
    }
    return noTx;
  }

}
