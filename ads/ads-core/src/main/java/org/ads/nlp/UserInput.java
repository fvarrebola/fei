package org.ads.nlp;

import org.ads.utils.Parameters;

import java.util.Arrays;
import java.util.Set;
import java.util.TreeSet;

/**
 * This class represents the user input.<br />
 * 
 * @author arrebola
 *
 */
public class UserInput {

  private String primaryInput;
  private String tokenized;
  private String lemmatized;
  private String stemmed;
  private String tags;

  private Set<String> syns;
  private Set<String> finalInputs;

  /**
   * Constructor.<br />
   */
  public UserInput() {
    super();
    this.syns = new TreeSet<String>();
    this.finalInputs = new TreeSet<String>();
  }

  /**
   * Gets the primary input.<br />
   * 
   * @return the primaryInput
   */
  public String getPrimaryInput() {
    return primaryInput;
  }

  /**
   * Sets the primary input.<br />
   * 
   * @param primaryInput
   *          the primaryInput to set
   */
  public void setPrimaryInput(String primaryInput) {
    this.primaryInput = primaryInput;
  }

  /**
   * Gets the tokenized primary input.<br />
   * 
   * @return the tokenized
   */
  public String getTokenized() {
    return tokenized;
  }

  /**
   * Sets the tokenized primary input.<br />
   * 
   * @param tokenized
   *          the tokenized to set
   */
  public void setTokenized(String tokenized) {
    this.tokenized = tokenized;
  }

  /**
   * Gets the lemmatized primary input.<br />
   * 
   * @return the lemmatized
   */
  public String getLemmatized() {
    return lemmatized;
  }

  /**
   * Sets the lemmatized primary input.<br />
   * 
   * @param lemmatized
   *          the lemmatized to set
   */
  public void setLemmatized(String lemmatized) {
    this.lemmatized = lemmatized;
  }

  /**
   * Gets the stemmed input.<br />
   * 
   * @return the stemmed
   */
  public String getStemmed() {
    return stemmed;
  }

  /**
   * Sets the stemmed input.<br />
   * 
   * @param stemmed
   *          the stemmed to set
   */
  public void setStemmed(String stemmed) {
    this.stemmed = stemmed;
  }

  /**
   * Gets the POS tags.<br />
   * 
   * @return the tags
   */
  public String getTags() {
    return tags;
  }

  /**
   * Sets the POS tags.<br />
   * 
   * @param tags
   *          the tags to set
   */
  public void setTags(String tags) {
    this.tags = tags;
  }

  /**
   * Gets the synsets.<br />
   * 
   * @return the syns
   */
  public Set<String> getSyns() {
    return syns;
  }

  /**
   * Sets the synsets.<br />
   * 
   * @param syns
   *          the syns to set
   */
  public void setSyns(Set<String> syns) {
    this.syns = syns;
  }

  /**
   * Gets the final inputs.<br />
   * 
   * @return the finalInputs
   */
  public Set<String> getFinalInputs() {
    return finalInputs;
  }

  /**
   * Sets the final inputs.<br />
   * 
   * @param finalInputs
   *          the finalInputs to set
   */
  public void setFinalInputs(Set<String> finalInputs) {
    this.finalInputs = finalInputs;
  }

  /**
   * Adds a primary input synset.<br />
   * 
   * @param input
   *          the {@link String} that represents the input
   */
  public void addSyn(String input) {

    Parameters.requireNonEmpty(input);

    this.syns.add(input);

  }

  /**
   * Adds a final input.<br />
   * 
   * @param input
   *          the {@link String} that represents the input
   */
  public void addFinalInput(String input) {

    Parameters.requireNonEmpty(input);

    this.finalInputs.add(input);

  }

  @Override
  public String toString() {

    StringBuilder builder = new StringBuilder();

    builder.append("[prim. input = ").append(this.primaryInput);
    builder.append(", lemma = ").append(this.primaryInput);
    builder.append(", stemd = ").append(this.stemmed);
    builder.append(", tags = ").append(this.tags);
    builder.append(", synsets = ").append(Arrays.toString(this.syns.toArray()));
    builder.append(", final input = ").append(Arrays.toString(this.finalInputs.toArray()));
    builder.append("]");

    return builder.toString();
  }

}