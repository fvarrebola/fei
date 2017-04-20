# HCII17

Here you will find all Java projects and instructions to conduct the experiments reported on 
_On Source Code Completion Assistants and the Need of a Context-Aware Approach_.

## Experiment overview
The experiment aims to collect and interpret usage information regarding two code assistants that differ in the approaches used to filter and sorte the list of possible completions. The first assistant is the longtime default option that ships with the [Eclipse](https://eclipse.org) IDE. It filters completions according to the restrictions of code structure and method and variable visibility and scope. It also sorts completions alphabetically and eventually according to the expected return type of an expression. The second assistant is the popular [Code Recommenders](https://eclipse.org/recommenders) that sorts completions according to statiscal usage models.

## Programming tasks
A number of programming tasks were designed to observe how professional software developers use code code assistants. All tasks can be found in project `programming-tasks` and they all considered the _fill-in-the-blanks_ approach seen below, in which software developers should replace invalid or incomplete statements accpording to a set of given instructions.
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

To actually observe how software programmers interact with code asistants, a logging layer was added to the ordinary code assistants that ship with [Eclipse](https://www.eclipse.org) IDE. The logging layer record how many times a particular code assistant was invoked, how long it was active, the user input (if any) once the assistant was invoked and the eventual user choice.



## Extending Eclipse code assistants
The `code-assistants` Java project was designed to add a logging layer to ordinary code assistants that ship with Eclipse Neon 4.6.1. It was designed to build as an ordinary [Maven](https://www.maven.org) project so you can avoid [PDE](https://www.eclipse.org/pde/) intrincacies.
So, to build `code-assistants` run a simple
```sh
$ mvn package
```

You should modify the `plugin.xml` file at your own discretion to enable or disable a particular extension. By default, the extensions `br.edu.fei.hcii17.codeassist.StandardCompletionExtension` and `br.edu.fei.hcii17.codeassist.IntelligentCompletionExtension` are enabled.
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

## Configuring Eclipse


## Log files