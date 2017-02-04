package br.edu.fei.hcii17.codeassist;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

import org.eclipse.jface.text.contentassist.ICompletionListener;
import org.eclipse.jface.text.source.ContentAssistantFacade;

/**
 * Completion listener registration helper.<br />
 * It ensures that only one of our custom listeners is registered at any given time using a local cache.<br />
 * 
 */
public class CompletionListenerRegistrationHelper {

    private static List<ICompletionListener> cache = new ArrayList<ICompletionListener>();

    /**
     * Registers a completion listener.<br />
     * 
     * @param contentAssist
     *            the {@link ContentAssistantFacade} that allows access to the given content assistant
     * @param listener
     *            the {@link ICompletionListener} to be registered
     */
    public static void register(ContentAssistantFacade contentAssist, ICompletionListener listener) {

        if (contentAssist == null || listener == null) {
           return;
        }

        contentAssist.removeCompletionListener(listener);
        cache.forEach(new Consumer<ICompletionListener>() {
            @Override
            public void accept(ICompletionListener element) {
                contentAssist.removeCompletionListener(element);
            }
        });
        cache.clear();

        contentAssist.addCompletionListener(listener);
        cache.add(listener);

    }

}
