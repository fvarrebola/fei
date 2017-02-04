package br.edu.fei.hcii17.codeassist.utils;

import org.eclipse.jdt.core.ICompilationUnit;
import org.eclipse.jdt.ui.text.java.ContentAssistInvocationContext;
import org.eclipse.jdt.ui.text.java.JavaContentAssistInvocationContext;

/**
 * JDT utility class.<br />
 * 
 */
public class JdtUtils {

    /**
     * Gets the name of the unit given a content assistant invocation context.<br />
     * 
     * @param context
     *            the ContentAssistInvocationContext
     *            
     * @return the String that represents the unit name
     */
    public static String getUnitName(ContentAssistInvocationContext context) {

        String unitName = null;

        if (context instanceof JavaContentAssistInvocationContext) {
            ICompilationUnit unit = ((JavaContentAssistInvocationContext) context).getCompilationUnit();
            if (unit != null) {
                unitName = unit.getElementName();
            }
        }

        return unitName;
    }

}
