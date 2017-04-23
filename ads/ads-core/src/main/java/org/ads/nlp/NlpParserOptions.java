package org.ads.nlp;

/**
 * This class concentrates all NLP techniques that can be applied to the end user input.<br />
 * So far, there's support to POS tagging through OpenNLP library.<br />
 * There's also support to lemmatization and synonym search through JWNL WordNet library.<br />
 * 
 * @author arrebola
 *
 */
public class NlpParserOptions {

  private boolean removeUnsafeChars;

  private boolean lemma;
  private boolean join;
  private boolean use1stVbNn;
  private boolean useSyns;
  private boolean useVbSynsOnly;

  /**
   * Constructor.<br />
   */
  public NlpParserOptions() {
    super();
  }

  public boolean isRemoveUnsafeChars() {
    return removeUnsafeChars;
  }

  public void setRemoveUnsafeChars(boolean removeUnsafeChars) {
    this.removeUnsafeChars = removeUnsafeChars;
  }

  public boolean isLemma() {
    return lemma;
  }

  public void setLemma(boolean lemma) {
    this.lemma = lemma;
  }

  public boolean isJoin() {
    return join;
  }

  public void setJoin(boolean join) {
    this.join = join;
  }

  public boolean isUse1stVbNn() {
    return use1stVbNn;
  }

  public void setUse1stVbNn(boolean use1stVbNn) {
    this.use1stVbNn = use1stVbNn;
  }

  public boolean isUseSynsets() {
    return useSyns;
  }

  public void setUseSyns(boolean useSynsets) {
    this.useSyns = useSynsets;
  }

  public boolean isUseVbSynsOnly() {
    return useVbSynsOnly;
  }

  public void setUseVbSynsOnly(boolean useVbSynsOnly) {
    this.useVbSynsOnly = useVbSynsOnly;
  }

  @Override
  public String toString() {

    StringBuilder builder = new StringBuilder();
    builder.append("[safe: ").append(this.removeUnsafeChars);
    builder.append(", lemma: ").append(this.lemma);
    builder.append(", join: ").append(this.join);
    builder.append(", use1stVerbAndNoun: ").append(this.use1stVbNn);
    builder.append(", useSynsets: ").append(this.useSyns);
    builder.append(", useVBSynsetsOnly: ").append(this.useVbSynsOnly).append("]");

    return builder.toString();
  }

  public static class NlpParserOptionsBuilder {

    private NlpParserOptions options;

    /**
     * Constructor.<br />
     */
    public NlpParserOptionsBuilder() {
      super();
      this.options = new NlpParserOptions();
    }

    public NlpParserOptionsBuilder safe() {
      this.options.setRemoveUnsafeChars(true);
      return this;
    }

    public NlpParserOptionsBuilder lemma() {
      this.options.setLemma(true);
      return this;
    }

    public NlpParserOptionsBuilder join() {
      this.options.setJoin(true);
      return this;
    }

    public NlpParserOptionsBuilder use1stVbAndNn() {
      this.options.setUse1stVbNn(true);
      return this;
    }

    public NlpParserOptionsBuilder useSynsets() {
      this.options.setUseSyns(true);
      return this;
    }

    /**
     * Only use synonyms for verbs.<br />
     * A call to this method implies in calling {@link #useSynsets()}.<br />
     * 
     * @return {@link NlpParserOptionsBuilder} that represents this builder
     */
    public NlpParserOptionsBuilder useVbSynsOnly() {

      if (!this.options.isUseSynsets()) {
        this.options.setUseSyns(true);
      }

      this.options.setUseVbSynsOnly(true);

      return this;

    }

    public NlpParserOptions build() {
      return this.options;
    }

  }

}
