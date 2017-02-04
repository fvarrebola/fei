package br.edu.fei.hcii17.codeassist;

import java.time.Duration;
import java.time.LocalDateTime;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.logging.Level;
import java.util.logging.Logger;

import javax.inject.Inject;
import javax.inject.Provider;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.jdt.ui.text.java.ContentAssistInvocationContext;
import org.eclipse.jface.text.BadLocationException;
import org.eclipse.jface.text.IDocument;
import org.eclipse.jface.text.IRegion;
import org.eclipse.jface.text.contentassist.ICompletionProposal;
import org.eclipse.recommenders.completion.rcp.CompletionContextKey;
import org.eclipse.recommenders.completion.rcp.ICompletionContextFunction;
import org.eclipse.recommenders.completion.rcp.processable.IProcessableProposal;
import org.eclipse.recommenders.completion.rcp.processable.IntelligentCompletionProposalComputer;
import org.eclipse.recommenders.internal.completion.rcp.CompletionRcpPreferences;
import org.eclipse.recommenders.rcp.IAstProvider;
import org.eclipse.recommenders.rcp.SharedImages;
import org.eclipse.ui.IEditorPart;

import br.edu.fei.hcii17.codeassist.utils.JdtUtils;

/**
 * Abstract intelligent completion proposal class to be extended by custom completion extensions.<br />
 * 
 * It simply extends the @link{IntelligentCompletionProposalComputer} standard implementation to keep track of
 * activations and applied completion proposals.<br />
 * 
 * @see IntelligentCompletionProposalComputer
 * 
 */
@SuppressWarnings({ "rawtypes" })
public abstract class AbstractIntelligentCompletionExtension extends IntelligentCompletionProposalComputer {

    protected Logger logger;

    protected IDocument document;
    protected LocalDateTime startedAt;
    protected List<ICompletionProposal> proposals;
    protected String unitName;

    @Inject
    public AbstractIntelligentCompletionExtension(CompletionRcpPreferences preferences, IAstProvider astProvider,
            SharedImages images, Map<CompletionContextKey, ICompletionContextFunction> functions,
            Provider<IEditorPart> editorRetriever) {
        super(preferences, astProvider, images, functions, editorRetriever);
        this.logger = Logger.getLogger(IntelligentCompletionExtension.class.getSimpleName());
        this.proposals = Collections.emptyList();
    }

    @Override
    public void sessionStarted() {
        super.sessionStarted();
        if (logger.isLoggable(Level.INFO)) {
            logger.info(Messages.session_Started);
        }
        this.startedAt = LocalDateTime.now();
    }

    @Override
    public void sessionEnded() {
        super.sessionEnded();

        if (logger.isLoggable(Level.INFO)) {
            logger.info(Messages.session_Ended);
            logger.info(Messages.bind(Messages.session_WasActiveFor,
                    Duration.between(this.startedAt, LocalDateTime.now()).getSeconds()));
        }

        if (logger.isLoggable(Level.FINE)) {
            logger.info(Messages.bind(Messages.compilationUnit_Details, this.document.get()));
        }

    }

    /**
     * Computes completion proposals.<br />
     * This method can be used to override the default completion behavior.<br />
     * 
     * @param context
     *            the context of the content assist invocation
     * @param monitor
     *            a progress monitor to report progress
     */
    protected abstract void doComputeCompletionProposals(ContentAssistInvocationContext context,
            IProgressMonitor monitor);

    /**
     * Filters completion proposals.<br />
     * 
     * @param context
     *            the context of the content assist invocation
     * @param monitor
     *            progress monitor to report progress
     */
    protected abstract void doFilterCompletionProposals(ContentAssistInvocationContext context,
            IProgressMonitor monitor);

    @Override
    public List<ICompletionProposal> computeCompletionProposals(ContentAssistInvocationContext context,
            IProgressMonitor monitor) {

        if (logger.isLoggable(Level.FINE)) {
            logger.fine(Messages.completion_HasBegun);
        }

        this.proposals.clear();
        doComputeCompletionProposals(context, monitor);
        if (this.proposals.isEmpty()) {
            this.proposals = super.computeCompletionProposals(context, monitor);
        }
        doFilterCompletionProposals(context, monitor);

        CompletionListenerRegistrationHelper.register(this.contentAssist, this);

        if (logger.isLoggable(Level.FINER)) {
            logger.finer(Messages.completion_SortingProposalsUsingRelevance);
            for (ICompletionProposal proposal : this.proposals) {
                if (proposal instanceof IProcessableProposal) {
                    IProcessableProposal proposalEx = (IProcessableProposal) proposal;
                    logger.finer(Messages.bind(Messages.completion_ProposalWithRelevanceDetails,
                            proposalEx.getStyledDisplayString(), proposalEx.getRelevance()));
                } else {
                    logger.finer(Messages.bind(Messages.completion_ProposalDetails, proposal.getDisplayString()));
                }
            }
        }

        String identifier = Messages.unknownValue;
        try {

            this.document = context.getDocument();
            this.unitName = JdtUtils.getUnitName(context);

            final int invocationOffset = context.getInvocationOffset();
            final IRegion region = document.getLineInformationOfOffset(invocationOffset);

            identifier = document.get(region.getOffset(), invocationOffset - region.getOffset());
            if (identifier != null) {
                identifier = identifier.trim();
            }
        } catch (BadLocationException ex) {
            logger.warning(Messages.completion_FailedToComputeIdentifier);
        }

        if (logger.isLoggable(Level.INFO)) {
            logger.info(Messages.bind(Messages.completion_Summary,
                    new Object[] { this.unitName, this.proposals.size(), identifier }));
        }

        if (logger.isLoggable(Level.FINE)) {
            logger.fine(Messages.completion_HasEnded);
        }

        return proposals;

    }

    @Override
    public void applied(ICompletionProposal proposal) {
        super.applied(proposal);
        if (logger.isLoggable(Level.INFO)) {
            final int index = this.proposals.indexOf(proposal);
            logger.info(Messages.bind(Messages.completion_ProposalWasApplied,
                    new Object[] { this.unitName, proposal.getDisplayString(), ((index > -1) ? index + 1 : "?") }));
        }

    }

}
