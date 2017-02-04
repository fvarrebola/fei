package br.edu.fei.hcii17.codeassist;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.jdt.ui.text.java.ContentAssistInvocationContext;

import br.edu.fei.hcii17.codeassist.ctx.FilteringContext;
import br.edu.fei.hcii17.codeassist.ctx.FilteringContextHelper;

/**
 * This is the standard type-filtering code completion proposal extension.<br />
 * 
 * @see AbstractCompletionExtension
 * 
 */
public final class StandardTypeFilteringCompletionExtension extends AbstractCompletionExtension {

    /**
     * Constructor.<br />
     */
    public StandardTypeFilteringCompletionExtension() {
        super();
    }

    @Override
    protected void doComputeCompletionProposals(ContentAssistInvocationContext context, IProgressMonitor monitor) {
    }

    @Override
    protected void doFilterCompletionProposals(ContentAssistInvocationContext context, IProgressMonitor monitor) {

        FilteringContext filteringCtx = FilteringContextHelper.detect(context);
        if (filteringCtx.isEmpty()) {
            return;
        }

        FilteringContextHelper.filter(filteringCtx, this.proposals);
    }

}
