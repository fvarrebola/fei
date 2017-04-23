package org.ads;

public class DataSet {

  public static class Data {

    private String id;
    private String input;
    private String output;

    public Data() {
      super();
    }

    public String getId() {
      return id;
    }

    public void setId(String id) {
      this.id = id;
    }

    public String getInput() {
      return input;
    }

    public void setInput(String input) {
      this.input = input;
    }

    public String getOutput() {
      return output;
    }

    public void setOutput(String output) {
      this.output = output;
    }

  }

  private String id;
  private String description;
  private Data[] data;

  public DataSet() {
    super();
  }

  public String getId() {
    return id;
  }

  public void setId(String id) {
    this.id = id;
  }

  public String getDescription() {
    return description;
  }

  public void setDescription(String description) {
    this.description = description;
  }

  public Data[] getData() {
    return data;
  }

  public void setData(Data[] data) {
    this.data = data;
  }

}
