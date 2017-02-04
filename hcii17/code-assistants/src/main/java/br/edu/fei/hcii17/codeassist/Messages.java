package br.edu.fei.hcii17.codeassist;

import org.eclipse.osgi.util.NLS;

/**
 * Message bundle.<br />
 * 
 * @see NLS
 * 
 */
public class Messages extends NLS {

    private static final String BUNDLE_NAME = "br.edu.fei.hcii17.codeassist.messages";

    public static String header;
    public static String unknownValue;

    public static String bundle_HasStarted;
    public static String bundle_HasStopped;

    public static String global_PropertiesFileNotFound;
    
    public static String logger_InitializedSuccessfully;
    public static String logger_FailedToLoadDefaultConfig;

    public static String config_DumpingSystemProperties;
    public static String config_SystemPropertyDetails;

    public static String plugin_Loaded;

    public static String session_Started;
    public static String session_Ended;
    public static String session_WasActiveFor;

    public static String completion_HasBegun;
    public static String completion_FailedToComputeIdentifier;
    public static String completion_ProposalDetails;
    public static String completion_SortingProposalsUsingRelevance;
    public static String completion_ProposalWithRelevanceDetails;
    public static String completion_FailedToDetermineContext;
    public static String completion_Summary;
    public static String completion_HasEnded;
    public static String completion_ProposalWasApplied;

    public static String contextComputation_HasBegun;
    public static String contextComputation_HasEnded;
    public static String contextInformation_Details;

    public static String positionGuessing_HasBegun;
    public static String positionGuessing_Details;
    public static String positionGuessing_HasEnded;

    public static String compilationUnit_Details;


    static {
        NLS.initializeMessages(BUNDLE_NAME, Messages.class);
    }

}
