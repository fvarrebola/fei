package org.ads.benchmarks;

public class Benchmark {

    private String id;
    private String input;
    private String filtered;
    private String output;
    private String library;
    private String object;
    private String method;

    /**
     * Constructor.<br />
     */
    public Benchmark() {
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

    public String getFiltered() {
        return filtered;
    }

    public void setFiltered(String filtered) {
        this.filtered = filtered;
    }

    public String getOutput() {
        return output;
    }

    public void setOutput(String output) {
        this.output = output;
    }

    public String getLibrary() {
        return library;
    }

    public void setLibrary(String library) {
        this.library = library;
    }

    public String getObject() {
        return object;
    }

    public void setObject(String object) {
        this.object = object;
    }

    public String getMethod() {
        return method;
    }

    public void setMethod(String method) {
        this.method = method;
    }

    @Override
    public String toString() {

        StringBuilder builder = new StringBuilder();

        builder.append("[input = ").append(this.input);
        builder.append(", output = ").append(this.output);
        builder.append("]");

        return builder.toString();
    }

}
