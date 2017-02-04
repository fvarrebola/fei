package br.edu.fei.hcii17.codeassist.ctx;

import java.io.IOException;
import java.io.InputStream;
import java.util.List;
import java.util.Properties;
import java.util.function.Predicate;
import java.util.logging.Logger;

import org.eclipse.jdt.core.Signature;
import org.eclipse.jdt.internal.ui.text.java.LazyGenericTypeProposal;
import org.eclipse.jdt.ui.text.java.ContentAssistInvocationContext;
import org.eclipse.jdt.ui.text.java.JavaContentAssistInvocationContext;
import org.eclipse.jface.text.contentassist.ICompletionProposal;

import br.edu.fei.hcii17.codeassist.Messages;
import br.edu.fei.hcii17.codeassist.utils.JdtUtils;
import br.edu.fei.hcii17.codeassist.utils.StringUtils;

/**
 * Filtering context detection helper.<br />
 * 
 */
public class FilteringContextHelper {

    private static final String PROPERTIES = "known.contexts.properties";

    private static final Logger logger = Logger.getLogger(FilteringContextHelper.class.getSimpleName());

    /**
     * Splits a property value read from the given {@link Properties}.<br />
     * 
     * @param properties
     *            the given {@link Properties}
     * @param propertyName
     *            the {@link String} that represents the property name
     * 
     * @return the array of {@link String} representing the property values
     */
    private static String[] tokenizeProperty(Properties properties, String propertyName) {
        return StringUtils.tokenize(properties.getProperty(propertyName));
    }

    /**
     * Tries to establish a filtering context given the content assistant invocation context.<br />
     * 
     * @param invocationCtx
     *            the {@link ContentAssistInvocationContext} that represents the content assistant invocation context
     * 
     * @return the {@link FilteringContext} context
     */
    public static FilteringContext detect(ContentAssistInvocationContext invocationCtx) {

        FilteringContext filteringCtx = new FilteringContext();
        if (!(invocationCtx instanceof JavaContentAssistInvocationContext)) {
            return filteringCtx;
        }

        final String unitName = JdtUtils.getUnitName(invocationCtx);

        Properties properties = new Properties();
        final ClassLoader loader = FilteringContextHelper.class.getClassLoader();
        try (InputStream inputStream = loader.getResourceAsStream(PROPERTIES)) {
            properties.load(inputStream);
            for (String knownCtx : tokenizeProperty(properties, "known-contexts")) {
                if (StringUtils.startsWithAny(unitName, tokenizeProperty(properties, knownCtx + ".units"))) {
                    filteringCtx.addPreferredClasses(tokenizeProperty(properties, knownCtx + ".preferredClasses"));
                    filteringCtx.addPreferredPackages(tokenizeProperty(properties, knownCtx + ".preferredPackages"));
                }
            }
        } catch (IOException ex) {
            logger.severe(Messages.completion_FailedToDetermineContext);
        }

        return filteringCtx;
    }

    /**
     * Filters the given proposals according to the filtering context settings.<br />
     * 
     * @param filteringCtx
     *            the {@link FilteringContext} that represents the filtering context
     * @param proposals
     *            the {@link List} of {@link ICompilationProposal} that represents the list of proposals
     * 
     * @return <code>true</code> if any elements were removed; <code>false</code> otherwise
     */
    public static boolean filter(FilteringContext filteringCtx, List<ICompletionProposal> proposals) {

        if (filteringCtx == null || proposals == null) {
            throw new IllegalArgumentException();
        }

        final String[] preferredClasses = filteringCtx.getPreferredClasses();
        final String[] preferredPkgs = filteringCtx.getPreferredPackages();

        return proposals.removeIf(new Predicate<ICompletionProposal>() {
            @Override
            public boolean test(ICompletionProposal proposal) {

                if (!(proposal instanceof LazyGenericTypeProposal)) {
                    return false;
                }

                boolean shouldKeepDuePkgPrefs = false;
                boolean shouldKeepDueClassPrefs = false;

                final LazyGenericTypeProposal lazyTypeProposal = (LazyGenericTypeProposal) proposal;
                final String qualifiedTypeName = lazyTypeProposal.getQualifiedTypeName();
                shouldKeepDuePkgPrefs = StringUtils.startsWithAny(qualifiedTypeName, preferredPkgs);

                final String simpleName = Signature.getSimpleName(qualifiedTypeName);
                shouldKeepDueClassPrefs = StringUtils.startsWithAny(simpleName, preferredClasses);

                return !(shouldKeepDuePkgPrefs || shouldKeepDueClassPrefs);

            }
        });
    }

}
