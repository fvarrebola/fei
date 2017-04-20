# HCII17

Here you will find all Java projects and instructions to conduct the experiment reported on 
_On Source Code Completion Assistants and the Need of a Context-Aware Approach_.

## Experiment overview
The experiment aims to collect and interpret usage information regarding two code assistants that differ in the approaches used to filter and sort the list of possible completions. The first assistant is the longtime default option that ships with the [Eclipse IDE](https://eclipse.org). It filters completions according to the restrictions of code structure and method and variable visibility and scope. It also sorts completions alphabetically and eventually according to the expected return type of an expression. The second assistant is the popular [Code Recommenders](https://eclipse.org/recommenders) that adds sorting features that rely upon predefined statistical usage models.

## Programming tasks
A number of programming tasks were designed to observe how professional software developers use code code assistants. All tasks can be found in project `programming-tasks` and they all considered the _fill-in-the-blanks_ approach seen below, in which software developers should replace invalid or incomplete statements according to a set of given instructions.
```java
public static String encode(byte[] input) {

    if (input == null || Array.getLength(input) == 0) {
        throw new IllegalArgumentException();
    }
    
    // ********************************************************************************
    // *
    // * Find a method to get a Base64 encoder
    // *
    // ********************************************************************************
    //
    // Once you find the right method, your statement will look like this:
    // (Please note that terms 'TYPE_OR_OBJECT' e 'METHOD' are to be replaced)
    //
    // Encoder encoder = TYPE_OR_OBJECT.METHOD;
    //
    // ********************************************************************************
    Encoder encoder = replaceMe_1; 

    ...
}
```

To actually observe how software programmers interact with code asistants, a logging layer was added to the ordinary code assistants that ship with [Eclipse IDE](https://www.eclipse.org). The logging layer record how many times a particular code assistant was invoked, how long it was active, the user input (if any) once the assistant was invoked and the eventual user choice.

## Extending Eclipse code assistants
The `code-assistants` project was designed to add a logging layer to ordinary code assistants that ship with [Eclipse IDE](https://www.eclipse.org). It does so by creating [org.eclipse.jdt.ui.javaCompletionProposalComputer](http://help.eclipse.org/neon/index.jsp?topic=%2Forg.eclipse.jdt.doc.isv%2Freference%2Fextension-points%2Forg_eclipse_jdt_ui_javaCompletionProposalComputer.html) [extension points](http://www.vogella.com/tutorials/EclipseExtensionPoint/article.html) that extend the ordinary implementations. This extensions access a few internal APIs and thus they do not follow Eclipse plugin coding guidelines.

The `code-assistants` project was designed to build as an ordinary [Maven](https://www.maven.org) project so you can avoid [PDE](https://www.eclipse.org/pde/) intrincacies.
So, to build `code-assistants` run a simple
```sh
$ mvn package
```

### Resulting artifact
Once a build is successful the resulting artifact will be a `hcii17-code-assistants_1.0.0.jar` JAR file that you should place in the `dropins` folder of your [Eclipse Neon 4.6.1](https://eclipse.org/neon/) distribution.

### Enabling and disabling extensions
You can modify the `plugin.xml` file at your own discretion to enable or disable a particular extension. Use XMLs comments marks to do so and remember that you should rebuild `code-assistants` at every change.
```xml
  <!-- This is an extension of the standard code completion assistant -->
  <extension point="org.eclipse.jdt.ui.javaCompletionProposalComputer"
      id="br.edu.fei.hcii17.codeassist.javaCompletionProposalComputer.std"
      name="[HCII17]: Standard">
    <javaCompletionProposalComputer
        activate="true"
        categoryId="br.edu.fei.hcii17.codeassist.std"
        class="br.edu.fei.hcii17.codeassist.StandardCompletionExtension">
    </javaCompletionProposalComputer>   
  </extension>
```

### Log files
Log files should look like this if the default `INFO` level is set.
```
...
INFO 2017-02-01 20:21:57,768 StandardCompletionExtension - Session started.
INFO 2017-02-01 20:21:57,783 StandardCompletionExtension - [Task01.java] - There are 37 completion proposals for 'if (from.'.
INFO 2017-02-01 20:22:01,929 StandardCompletionExtension - Session was active for 4 seconds.
...
```

## Configuring Eclipse


## Log files