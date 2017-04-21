# HCII17

Here you will find all Java projects and instructions to conduct the experiment reported on 
_On Source Code Completion Assistants and the Need of a Context-Aware Approach_.

## Experiment overview
The experiment aims to collect and interpret usage information regarding two code assistants that differ in the approaches used to filter and sort the list of possible completions. The first assistant is the longtime default option that ships with the [Eclipse IDE](https://eclipse.org), which filters completions according to the restrictions of code structure and method and variable visibility and scope, and sorts completions alphabetically and eventually according to the expected return type of an expression. The second assistant is the popular [Code Recommenders](https://eclipse.org/recommenders) that adds sorting features that rely upon predefined statistical usage models.

### The programming tasks
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

### Observing interactions and extending code assistants
To actually observe how software programmers interact with code asistants we created the `code-assistants` project. It adds a logging layer to the ordinary code assistants that ship with [Eclipse IDE](https://www.eclipse.org) which records how many times a particular code assistant was invoked, how long it was active, the user input (if any) once the assistant was invoked and the eventual user choice.
In order to do so we define a few [extension points](http://www.vogella.com/tutorials/EclipseExtensionPoint/article.html) of type `org.eclipse.jdt.ui.javaCompletionProposalComputer` (see reference documentation [here](http://help.eclipse.org/neon/index.jsp?topic=%2Forg.eclipse.jdt.doc.isv%2Freference%2Fextension-points%2Forg_eclipse_jdt_ui_javaCompletionProposalComputer.html)) that extend the ordinary implementations (take a look at the [plugin.xml](/code-assistants/src/main/resources/plugin.xml) file to see how extension points are defined) [1].
You can modify implementations at your own will, and since the `code-assistants` project was designed to build as an ordinary [Maven](https://www.maven.org) then all you have to do to build it is to run a simple
```sh
$ mvn package
```

Once a build is successful the resulting artifact will be an ordinary JAR file named `hcii17-code-assistants_1.0.0.jar` (or whatever version you are building).

[1]: However, please note that despite functional, these extensions access a few internal APIs and thus they do not follow Eclipse plugin coding guidelines.

#### Enabling and disabling custom extensions
You can also modify the [plugin.xml](/code-assistants/src/main/resources/plugin.xml) file at your own discretion to enable or disable a particular extension. Use XMLs comment marks to do so and remember that since `plugin.xml` is embedded in the JAR file you should rebuild `code-assistants` at every change.
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

#### Log files
Log files are defined in [logging.properties](/code-assistants/src/main/resources/logging.properties) file, which is also embedded in the JAR file. You can set the log location and log level, but a standard log file should like this once the `INFO` level is set.
```
...
INFO 2017-02-01 20:21:57,768 StandardCompletionExtension - Session started.
INFO 2017-02-01 20:21:57,783 StandardCompletionExtension - [Task01.java] - There are 37 completion proposals for 'if (from.'.
INFO 2017-02-01 20:22:01,929 StandardCompletionExtension - Session was active for 4 seconds.
...
```

## Running the experiment
Once you got your subjects you should prepare a custom [Eclipse Neon 4.6.1](https://eclipse.org/neon/) distribution.

### Configuring Eclipse
This is the most demanding task. You should add 

### Choosing the programming tasks
Select the programming tasks that are more suitable to your target audience and create a workspace.


## Log files


 that you should place in the `dropins` folder of your [Eclipse Neon 4.6.1](https://eclipse.org/neon/) distribution