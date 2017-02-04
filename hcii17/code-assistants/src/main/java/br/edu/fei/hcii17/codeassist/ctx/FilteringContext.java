package br.edu.fei.hcii17.codeassist.ctx;

import java.lang.reflect.Array;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

/**
 * The simplest filtering context so far.<br />
 * It is defined by lists of preferred classes and packages.<br />
 * 
 */
public class FilteringContext {

    private List<String> preferredClasses = new LinkedList<String>();
    private List<String> preferredPackages = new LinkedList<String>();

    /**
     * Constructor.<br />
     */
    public FilteringContext() {
        super();
    }

    public String[] getPreferredClasses() {
        return this.preferredClasses.toArray(new String[] {});
    }

    public void addPreferredClasses(String[] classes) {
        if (Array.getLength(classes) == 0) {
            return;
        }
        this.preferredClasses.addAll(Arrays.asList(classes));
    }

    public String[] getPreferredPackages() {
        return this.preferredPackages.toArray(new String[] {});
    }

    public void addPreferredPackages(String[] pkgs) {
        if (Array.getLength(pkgs) == 0) {
            return;
        }
        this.preferredPackages.addAll(Arrays.asList(pkgs));
    }

    public boolean isEmpty() {
        return (this.preferredClasses.isEmpty() && this.preferredPackages.isEmpty());
    }
    
}
