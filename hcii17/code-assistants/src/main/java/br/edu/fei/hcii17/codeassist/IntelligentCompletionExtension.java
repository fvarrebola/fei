package br.edu.fei.hcii17.codeassist;

import java.util.Map;
import java.util.logging.Logger;

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

/**
 * This is the standard intelligent code completion extension.<br />
 * 
 * @see AbstractIntelligentCompletionExtension
 * 
 */
@SuppressWarnings({ "rawtypes" })
public class IntelligentCompletionExtension extends AbstractIntelligentCompletionExtension {

    @Inject
    public IntelligentCompletionExtension(CompletionRcpPreferences preferences, IAstProvider astProvider,
            SharedImages images, Map<CompletionContextKey, ICompletionContextFunction> functions,
            Provider<IEditorPart> editorRetriever) {
        super(preferences, astProvider, images, functions, editorRetriever);
        this.logger = Logger.getLogger(IntelligentCompletionExtension.class.getSimpleName());
    }

    @Override
    protected void doComputeCompletionProposals(ContentAssistInvocationContext context, IProgressMonitor monitor) {

    }

    @Override
    protected void doFilterCompletionProposals(ContentAssistInvocationContext context, IProgressMonitor monitor) {
    }

}
