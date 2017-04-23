package org.ads.orientdb;

import org.ads.Constants;

public enum EdgeClass {

  DEPENDS("depends"), IS_PART_OF("is-part-of");

  private String edgeLabel;

  EdgeClass(String edgeLabel) {
    this.edgeLabel = edgeLabel;
  }

  public String getEdgeLabel() {
    return this.edgeLabel;
  }

  public String getEdgeClassName() {
    return Constants.ORIENTDB_CLASS_PREFIX + this.edgeLabel;
  }

}
