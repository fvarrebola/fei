package org.ads.utils;

import com.orientechnologies.orient.core.record.impl.ODocument;
import net.didion.jwnl.data.POS;
import org.ads.langs.java.model.JavaLibrary;
import org.ads.langs.java.model.JavaMethod;
import org.ads.langs.java.model.JavaObject;
import org.ads.nlp.PennTreebankPosTags;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.maven.index.ArtifactInfo;
import org.eclipse.aether.artifact.Artifact;
import org.eclipse.aether.artifact.DefaultArtifact;
import org.eclipse.aether.graph.Dependency;
import org.eclipse.aether.resolution.ArtifactDescriptorResult;

import java.util.List;
import java.util.function.Consumer;

/**
 * Converter utility class.<br />
 * 
 * @author arrebola
 *
 */
public final class ConverterUtils {

  private static final Logger LOGGER = LogManager.getLogger();

  /**
   * Converts an artifact information object {@link ArtifactInfo} of the Maven indexer API to a
   * artifact {@link Artifact} of the Aether resolver API.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * 
   * @return the {@link Artifact} that represents the Aether resolver API artifact information
   */
  public static Artifact mavenToAether(ArtifactInfo artifactInfo) {

    Parameters.requireNonNull(artifactInfo);

    return new DefaultArtifact(artifactInfo.getGroupId(), artifactInfo.getArtifactId(),
        artifactInfo.getClassifier(), artifactInfo.getFileExtension(), artifactInfo.getVersion());
  }

  /**
   * Converts an artifact information object {@link ArtifactInfo} of the Maven indexer API to a
   * artifact {@link JavaLibrary} of local API.<br />
   * 
   * @param artifactInfo
   *          the {@link ArtifactInfo} that represents the Maven indexer API artifact information
   * 
   * @return the {@link JavaLibrary} that represents the local API
   */
  public static JavaLibrary fromMaven(ArtifactInfo artifactInfo) {

    Parameters.requireNonNull(artifactInfo);

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Converting Maven Index API artifact {}.", artifactInfo);
    }

    JavaLibrary javaLibrary = new JavaLibrary();

    javaLibrary.setGroupId(artifactInfo.getGroupId());
    javaLibrary.setArtifactId(artifactInfo.getArtifactId());
    javaLibrary.setVersion(artifactInfo.getVersion());
    javaLibrary.setPackaging(artifactInfo.getPackaging());
    javaLibrary.setExtension(artifactInfo.getFileExtension());
    javaLibrary.setClassifier(artifactInfo.getClassifier());
    javaLibrary.buildName();

    return javaLibrary;

  }

  /**
   * Converts a local API artifact of type {@link JavaLibrary} to a Maven indexer API artifact of
   * type {@link ArtifactInfo}. <br />
   * 
   * @param javaLibrary
   *          the {@link JavaLibrary} that represents the local API artifact
   * 
   * @return the {@link ArtifactInfo} that represents the Maven indexer API artifact
   */
  public static ArtifactInfo toMaven(JavaLibrary javaLibrary) {

    Parameters.requireNonNull(javaLibrary);

    ArtifactInfo artifactInfo = new ArtifactInfo();

    artifactInfo.setGroupId(javaLibrary.getGroupId());
    artifactInfo.setArtifactId(javaLibrary.getArtifactId());
    artifactInfo.setVersion(javaLibrary.getVersion());
    artifactInfo.setFileExtension(javaLibrary.getExtension());
    artifactInfo.setPackaging(javaLibrary.getPackaging());
    artifactInfo.setClassifier(javaLibrary.getClassifier());

    return artifactInfo;

  }

  /**
   * Converts an artifact descriptor result {@link ArtifactDescriptorResult} object of the Aether
   * resolver API to a java library {@link JavaLibrary} of the internal API.<br />
   * 
   * @param artifactDescriptorResult
   *          the {@link ArtifactDescriptorResult} that represents the Aether descriptor result
   * 
   * @return the {@link JavaLibrary} that represents a java library
   */
  public static JavaLibrary fromAether(ArtifactDescriptorResult artifactDescriptorResult) {

    Parameters.requireNonNull(artifactDescriptorResult);

    Artifact aetherArtifact = artifactDescriptorResult.getArtifact();

    JavaLibrary javaLibrary = new JavaLibrary();
    javaLibrary.setGroupId(aetherArtifact.getGroupId());
    javaLibrary.setArtifactId(aetherArtifact.getArtifactId());
    javaLibrary.setVersion(aetherArtifact.getVersion());
    javaLibrary.setExtension(aetherArtifact.getExtension());
    javaLibrary.setClassifier(aetherArtifact.getClassifier());
    javaLibrary.setPackaging(aetherArtifact.getExtension());
    javaLibrary.buildName();

    List<Dependency> aetherDeps = artifactDescriptorResult.getDependencies();

    if (LOGGER.isDebugEnabled()) {
      LOGGER.debug("Artifact {} has {} dependency(ies).", aetherArtifact, aetherDeps.size());
    }

    aetherDeps.forEach(new Consumer<Dependency>() {

      int idx = 0;

      @Override
      public void accept(Dependency aetherDependency) {

        Artifact aetherDepArtifact = aetherDependency.getArtifact();

        if (LOGGER.isDebugEnabled()) {
          LOGGER.debug("[{}] Dependency {}.", ++idx, aetherDepArtifact);
        }

        JavaLibrary javaLibraryDependency = new JavaLibrary();
        javaLibraryDependency.setGroupId(aetherDepArtifact.getGroupId());
        javaLibraryDependency.setArtifactId(aetherDepArtifact.getArtifactId());
        javaLibraryDependency.setVersion(aetherDepArtifact.getVersion());
        javaLibraryDependency.setExtension(aetherDepArtifact.getExtension());
        javaLibraryDependency.setClassifier(aetherDepArtifact.getClassifier());
        javaLibraryDependency.setPackaging(aetherDepArtifact.getExtension());
        javaLibraryDependency.setScope(aetherDependency.getScope());
        javaLibraryDependency.buildName();

        javaLibrary.addDependency(javaLibraryDependency);

      }

    });

    return javaLibrary;
  }

  /**
   * Converts an artifact Orient DB {@link ODocument} object to a java library {@link JavaLibrary}
   * of the internal API.<br />
   * 
   * @param document
   *          the {@link ODocument} that represents the Orient DB object
   * 
   * @return the {@link JavaLibrary} that represents a java library
   */
  public static JavaLibrary toJavaLibrary(ODocument document, int librariesCount) {

    Parameters.requireNonNull(document);

    JavaLibrary javaLibrary = new JavaLibrary();

    javaLibrary.setGroupId(document.field("groupId"));
    javaLibrary.setArtifactId(document.field("artifactId"));
    javaLibrary.setVersion(document.field("version"));
    javaLibrary.setExtension(document.field("extension"));
    javaLibrary.setPackaging(document.field("packging"));
    javaLibrary.setClassifier(document.field("classifier"));

    if (librariesCount > 0) {
      javaLibrary.setPopularityIndex(((int) document.field("idx_value") / (librariesCount * 1.0f)));
    }

    return javaLibrary;

  }

  /**
   * Converts an artifact Orient DB {@link ODocument} object to a java library {@link JavaLibrary}
   * of the internal API.<br />
   * 
   * @param document
   *          the {@link ODocument} that represents the Orient DB object
   * 
   * @return the {@link JavaLibrary} that represents a java library
   */
  public static JavaLibrary toJavaLibrary(ODocument document) {
    return toJavaLibrary(document, 0);
  }

  /**
   * Converts an artifact Orient DB {@link ODocument} object to a java object {@link JavaObject} of
   * the internal API. <br />
   * 
   * @param document
   *          the {@link ODocument} that represents the Orient DB object
   * 
   * @return the {@link JavaObject} that represents a java library
   */
  public static JavaObject toJavaObject(ODocument document) {

    Parameters.requireNonNull(document);

    JavaObject object = new JavaObject();

    object.setName(document.field("name"));
    object.setDescription(document.field("description"));

    return object;
  }

  /**
   * Converts an artifact Orient DB {@link ODocument} object to a java method {@link JavaMethod} of
   * the internal API. <br />
   * 
   * @param document
   *          the {@link ODocument} that represents the Orient DB object
   * 
   * @return the {@link JavaMethod} that represents a java library
   */
  public static JavaMethod toJavaMethod(ODocument document) {

    Parameters.requireNonNull(document);

    final String libraryName = document.field("library_name");
    JavaLibrary library = new JavaLibrary();
    library.setFqn(libraryName);

    final String objectName = document.field("object_name");
    JavaObject object = new JavaObject(library);
    object.setName(objectName);

    JavaMethod method = new JavaMethod(object);
    method.setLibrary(libraryName);
    method.setObject(objectName);
    method.setName(document.field("method_name"));
    method.setSignature(document.field("method_signature"));
    method.setDescription(document.field("method_description"));

    return method;

  }

  /**
   * Converts a {@link String} part-of-speech tag to a {@link POS} object of the JWNL API.<br />
   * 
   * @param tag
   *          {@link PennTreebankPosTags} part-of-speech tag
   * 
   * @return the {@link POS} object of the JWNL API
   */
  public static POS toJwnlPos(PennTreebankPosTags tag) {

    Parameters.requireNonNull(tag);

    POS jwnlPos = POS.NOUN;
    if (PennTreebankPosTags.isVerb(tag)) {
      jwnlPos = POS.VERB;
    }

    return jwnlPos;

  }

}
