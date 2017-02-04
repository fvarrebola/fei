package br.edu.fei.hcii17.codeassist;

import java.util.Map;

import javax.inject.Inject;
import javax.inject.Provider;

import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.jdt.ui.text.java.ContentAssistInvocationContext;
import org.eclipse.recommenders.completion.rcp.CompletionContextKey;
import org.eclipse.recommenders.completion.rcp.ICompletionContextFunction;
import org.eclipse.recommenders.internal.completion.rcp.CompletionRcpPreferences;
import org.eclipse.recommenders.rcp.IAstProvider;
import org.eclipse.recommenders.rcp.SharedImages;
import org.eclipse.ui.IEditorPart;

import br.edu.fei.hcii17.codeassist.ctx.FilteringContext;
import br.edu.fei.hcii17.codeassist.ctx.FilteringContextHelper;

/**
 * This is the code completion extension that combines intelligent and type-filtering completion features.<br />
 * 
 * @see AbstractIntelligentCompletionExtension
 * 
 */
@SuppressWarnings({ "rawtypes" })
public class IntelligentTypeFilteringCompletionExtension extends AbstractIntelligentCompletionExtension {

    @Inject
    public IntelligentTypeFilteringCompletionExtension(CompletionRcpPreferences preferences,
            IAstProvider astProvider, SharedImages images,
            Map<CompletionContextKey, ICompletionContextFunction> functions, Provider<IEditorPart> editorRetriever) {
        super(preferences, astProvider, images, functions, editorRetriever);
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
