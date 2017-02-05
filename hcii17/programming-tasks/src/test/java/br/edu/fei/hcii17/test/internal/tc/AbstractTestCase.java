package br.edu.fei.hcii17.test.internal.tc;

import java.lang.reflect.Array;

import br.edu.fei.hcii17.test.internal.Messages;
import junit.framework.TestCase;

public abstract class AbstractTestCase extends TestCase {
    
    private void assertTrueUsingHeaderAndFooter(boolean condition, String header, String footer, Object... arguments) {
        if (condition) {
            return;
        }

        final int length = Array.getLength(arguments);
        if (length == 0) {
            super.fail(header);
        }

        StringBuilder builder = new StringBuilder();
        for (int idx = 0; idx < length; idx++) {
            builder.append(arguments[idx]).append((idx != length - 1) ? "\r\n" : "");
        }
        super.fail(String.format("\r\n%s%s\r\n%s\r\n", header, builder.toString(), (footer == null ? "" : footer)));

    }

    protected void assertForInputValidation(boolean condition, Object... arguments) {
        assertTrueUsingHeaderAndFooter(condition, Messages.header_InputValidation, null, arguments);
    }

    protected void assertForWrongFunction(boolean condition, Object... arguments) {
        assertTrueUsingHeaderAndFooter(condition, Messages.header_WrongFunction,
                Messages.global_DidYouChoseTheRightFunction, arguments);
    }

    protected void failForWrongFunction(Object... arguments) {
        assertTrueUsingHeaderAndFooter(false, Messages.header_WrongFunction,
                Messages.global_DidYouChoseTheRightFunction, arguments);
    }

}
