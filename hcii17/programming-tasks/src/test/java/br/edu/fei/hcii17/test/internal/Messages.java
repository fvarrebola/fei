package br.edu.fei.hcii17.test.internal;

/**
 * Classe utilitária para mensagens dos testes unitários.<br />
 * 
 * @author arrebola
 *
 */
public class Messages extends MessagesLoader {

    private static final String BUNDLE_NAME = "br.edu.fei.hcii17.test.internal.messages";

    public static String header_InputValidation;
    public static String header_WrongFunction;

    public static String global_ParamIsNullOrEmpty;
    public static String global_ShouldThrowIllegalArgumentEx;
    public static String global_DidYouChoseTheRightFunction;

    public static String practice_FailedToEncode;
    public static String practice_FailedToDecode;

    public static String task01_NonExistantDir;

    public static String task02_InvalidStart;
    public static String task02_InvalidEnd;
    public static String task02_ShouldBeZero;
    public static String task02_ShouldBe315532800;

    public static String task03_InvalidList;
    public static String task03_NullStream;
    public static String task03_PredicateHasNotBeenApplied;
    public static String task03_FunctionHasNotBeenApplied;
    public static String task03_UnsortedStream;

    public static String task04_InvalidScript;
    public static String task04_ScriptTooBig;
    public static String task04_ScriptExecutionFailed;
    public static String task04_OutputFileIsEmpty;
    
    public static String task05_OnlyFilesShouldBeAccepted;
    public static String task05_FileIsUnreadable;
    public static String task05_CouldNotReadFile;
    public static String task05_UnexpectedLineCount;
    public static String task05_randomContent;
    
    public static String junit_Header;
    public static String junit_TestStarted;
    public static String junit_TestRunFinished;
    public static String junit_TaskCompleted;
    
    static {
        Messages.initializeMessages(BUNDLE_NAME, Messages.class);
    }

}
