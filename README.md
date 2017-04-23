# FEI
Here you will find FEI related source code, which now includes:

## Class assignments
Class assignments were mostly build using C/C++ so a VS compiler will probably do the job.

## API Documentation Search (ADS) prototype
The API Documentation Search prototype combines dependency information from Maven artifacts (the information you get from `pom.xml` files) to javadoc documentation artifacts to provide a NLP-based search tool.

All the main NLP features like tokeninzation and POS tagging are provided by the [OpenNLP](https://opennlp.apache.org/) library. Synonyms support is provided by the [JWNL](https://sourceforge.net/projects/jwordnet/) which is ultimately backed up by [WordNet](https://wordnet.princeton.edu) dictionary files. The dependency information data representation relies upon graph database features provided by [OrientDB](https://orientdb.com).

Complete instructions are to be provided in the future. For now, use and deploy the resulting .WAR to a [Tomcat](https://tomcat.apache.org/ )server.
```
mvn package
```

## HCII17
