package org.ads.orientdb;

import org.ads.Constants;
import org.ads.langs.java.model.JavaField;
import org.ads.langs.java.model.JavaLibrary;
import org.ads.langs.java.model.JavaMethod;
import org.ads.langs.java.model.JavaObject;

public enum VertexClass {

  JLIBRARY(JavaLibrary.class), JOBJECT(JavaObject.class), JMETHOD(JavaMethod.class), JFIELD(
      JavaField.class);

  private Class<?> modelClass;

  VertexClass(Class<?> modelClass) {
    this.modelClass = modelClass;
  }

  public Class<?> getModelClass() {
    return this.modelClass;
  }

  public String getVertexLabel() {
    return this.modelClass.getSimpleName().toLowerCase();
  }

  public String getVertexClassName() {
    return Constants.ORIENTDB_CLASS_PREFIX + getVertexLabel();
  }

}
