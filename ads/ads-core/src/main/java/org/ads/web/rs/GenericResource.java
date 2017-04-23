package org.ads.web.rs;

import org.ads.utils.Parameters;

import java.util.ArrayList;
import java.util.List;

/**
 * Generic JAW-RS resource.<br />
 * This resource wraps data items and its properties and all the eventual error information.<br />
 * 
 * @author arrebola
 *
 */
public class GenericResource<T> {

  private Integer error;
  private String message;

  private Integer count;
  private List<T> items;

  private Integer limit;
  private Integer page;
  private Integer pageSize;

  private Object extendedInfo;

  public GenericResource() {
    super();
    this.items = new ArrayList<T>();
  }

  public Integer getErrorCode() {
    return error;
  }

  public void setErrorCode(Integer error) {
    this.error = error;
  }

  public String getErrorMessage() {
    return message;
  }

  public void setErrorMessage(String message) {
    this.message = message;
  }

  public Integer getCount() {
    return count;
  }

  public void setCount(Integer count) {
    this.count = count;
  }

  public Integer getLimit() {
    return limit;
  }

  public void setLimit(Integer limit) {
    this.limit = limit;
  }

  public Integer getPage() {
    return page;
  }

  public void setPage(Integer page) {
    this.page = page;
  }

  public Integer getPageSize() {
    return pageSize;
  }

  public void setPageSize(Integer pageSize) {
    this.pageSize = pageSize;
  }

  public Object getExtendedInfo() {
    return extendedInfo;
  }

  public void setExtendedInfo(Object extendedInfo) {
    this.extendedInfo = extendedInfo;
  }

  public List<T> getItems() {
    return items;
  }

  /**
   * Sets the items to be wrapped by this resource.<br />
   * 
   * @param items
   *          the {@link List} of items
   */
  public void setItems(List<T> items) {

    Parameters.requireNonNull(items);

    this.items = items;
    this.count = this.items.size();

  }

  /**
   * Sets the failure information to be wrapped by this resource.<br />
   * 
   * @param error
   *          the {@link Errors} that represents the JAX-RS error
   * @param extendedInfo
   *          the {@link Object} that represents some extended information
   */
  public void fail(Errors error, Object extendedInfo) {

    Parameters.requireNonNull(error);

    this.error = error.ordinal();
    this.message = "TODO";

    this.extendedInfo = extendedInfo;

  }

}
