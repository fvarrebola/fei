package org.ads.nlp;

public enum PennTreebankPosTags {

    CC("CC", "Coordinatingconjunction"),
    CD("CD", "Cardinalnumber"),
    DT("DT", "Determiner"),
    EX("EX", "Existentialthere"),
    FW("FW", "Foreignword"),
    IN("IN", "Prepositionorsubordinatingconjunction"),
    JJ("JJ", "Adjective"),
    JJR("JJR", "Adjective,comparative"),
    JJS("JJS", "Adjective,superlative"),
    LS("LS", "Listitemmarker"),
    MD("MD", "Modal"),
    NN("NN", "Noun,singularormass"),
    NNS("NNS", "Noun,plural"),
    NNP("NNP", "Propernoun,singular"),
    NNPS("NNPS", "Propernoun,plural"),
    PDT("PDT", "Predeterminer"),
    POS("POS", "Possessiveending"),
    PRP("PRP", "Personalpronoun"),
    PRP$("PRP$", "Possessivepronoun"),
    RB("RB", "Adverb"),
    RBR("RBR", "Adverb,comparative"),
    RBS("RBS", "Adverb,superlative"),
    RP("RP", "Particle"),
    SYM("SYM", "Symbol"),
    TO("TO", "to"),
    UH("UH", "Interjection"),
    VB("VB", "Verb,baseform"),
    VBD("VBD", "Verb,pasttense"),
    VBG("VBG", "Verb,gerundorpresentparticiple"),
    VBN("VBN", "Verb,pastparticiple"),
    VBP("VBP", "Verb,non-3rdpersonsingularpresent"),
    VBZ("VBZ", "Verb,3rdpersonsingularpresent"),
    WDT("WDT", "Wh-determiner"),
    WP("WP", "Wh-pronoun"),
    WP$("WP$", "Possessivewh-pronoun"),
    WRB("WRB", "Wh-adverb");

  private String tag;
  private String description;

  PennTreebankPosTags(String tag, String description) {
    this.tag = tag;
    this.description = description;
  }

  String tag() {
    return this.tag;
  }

  String description() {
    return this.description;
  }

  public static boolean isVerb(PennTreebankPosTags tag) {
    return (VB.equals(tag) || VBD.equals(tag) || VBG.equals(tag) || VBN.equals(tag)
        || VBP.equals(tag) || VBZ.equals(tag));
  }

  public static boolean isNoun(PennTreebankPosTags tag) {
    return (NN.equals(tag) || NNP.equals(tag) || NNPS.equals(tag) || NNS.equals(tag));
  }

}
