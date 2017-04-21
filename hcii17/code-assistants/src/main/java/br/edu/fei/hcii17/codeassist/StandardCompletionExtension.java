package br.edu.fei.hcii17.codeassist;

import java.util.logging.Logger;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.jdt.ui.text.java.ContentAssistInvocationContext;

/**
 * This is the standard code completion extension.<br />
 * 
 * @see AbstractCompletionExtension
 * 
 */
public final class StandardCompletionExtension extends AbstractCompletionExtension {

    /**
     * Constructor.<br />
     */
    public StandardCompletionExtension() {
        super();
        this.logger = Logger.getLogger(StandardCompletionExtension.class.getSimpleName());
    }

    @Override
    protected void doComputeCompletionProposals(ContentAssistInvocationContext invocationCtx,
            IProgressMonitor monitor) {
    }

    @Override
    protected void doFilterCompletionProposals(ContentAssistInvocationContext invocationCtx, IProgressMonitor monitor) {
    }

}
