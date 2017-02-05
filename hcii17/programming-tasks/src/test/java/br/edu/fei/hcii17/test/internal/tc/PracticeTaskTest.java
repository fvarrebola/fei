package br.edu.fei.hcii17.test.internal.tc;

import java.util.Arrays;

import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runners.MethodSorters;

import br.edu.fei.hcii17.PracticeTask;
import br.edu.fei.hcii17.test.internal.Messages;

@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class PracticeTaskTest extends AbstractTestCase {

    private static final String TEXT = "This is a practice task.";
    private static final String ENCODED_TEXT = "VGhpcyBpcyBhIHByYWN0aWNlIHRhc2su";

    @Test
    public void test01___ParametroDeEntradaEhNuloParaFuncaoEncode() {

        boolean succeeded = false;

        try {
            PracticeTask.encode(null);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded,
                Messages.bind(Messages.global_ParamIsNullOrEmpty, "input da funcao encode(byte[])"),
                Messages.global_ShouldThrowIllegalArgumentEx);
    }

    @Test
    public void test02___ParametroDeEntradaEhNuloParaFuncaoDecode() {

        boolean succeeded = false;
        try {
            PracticeTask.decode(null);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded,
                Messages.bind(Messages.global_ParamIsNullOrEmpty, "input da funcao encode(String)"),
                Messages.global_ShouldThrowIllegalArgumentEx);

    }

    @Test
    public void test03___ParametroDeEntradaEhVazioParaFuncaoEncode() {

        boolean succeeded = false;

        try {
            PracticeTask.encode(new byte[] {});
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded,
                Messages.bind(Messages.global_ParamIsNullOrEmpty, "input da funcao encode(byte[])"),
                Messages.global_ShouldThrowIllegalArgumentEx);
    }

    @Test
    public void test04___ParametroDeEntradaEhVazioParaFuncaoDecode() {

        boolean succeeded = false;
        try {
            PracticeTask.decode("");
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded,
                Messages.bind(Messages.global_ParamIsNullOrEmpty, "input da funcao encode(String)"),
                Messages.global_ShouldThrowIllegalArgumentEx);

    }

    @Test
    public void test05___CodficandoUmVetorDeBytesEmBase64() {
        boolean succeeded = false;
        try {
            succeeded = ENCODED_TEXT.equals(PracticeTask.encode(TEXT.getBytes()));
        } catch (Throwable t) {
        }
        assertForWrongFunction(succeeded, Messages.practice_FailedToEncode, Messages.global_DidYouChoseTheRightFunction);
    }

    @Test
    public void test06___DecodficandoUmaStringBase64() {
        boolean succeeded = false;
        try {
            succeeded = Arrays.equals(TEXT.getBytes(), PracticeTask.decode(ENCODED_TEXT));
        } catch (Throwable t) {
        }
        assertForWrongFunction(succeeded, Messages.practice_FailedToDecode, Messages.global_DidYouChoseTheRightFunction);

    }

}
