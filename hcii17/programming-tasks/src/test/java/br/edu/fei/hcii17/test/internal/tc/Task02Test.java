package br.edu.fei.hcii17.test.internal.tc;

import java.time.LocalDateTime;

import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runners.MethodSorters;

import br.edu.fei.hcii17.Task02;
import br.edu.fei.hcii17.test.internal.Messages;

@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class Task02Test extends AbstractTestCase {

    private static final LocalDateTime start = LocalDateTime.parse("2000-12-03T10:15:30");
    private static final LocalDateTime end = LocalDateTime.parse("2010-12-03T10:15:30");
    private static final LocalDateTime invalidStart = LocalDateTime.parse("3000-12-03T10:15:30");
    private static final LocalDateTime invalidEnd = LocalDateTime.parse("3010-12-03T10:15:30");

    @Test
    public void test01___ParametrosDeEntradaSaoNulos() {

        boolean succeeded = false;

        try {
            Task02.execute(null, end);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.global_ParamIsNullOrEmpty, "start"));

        succeeded = false;
        try {
            Task02.execute(start, null);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.global_ParamIsNullOrEmpty, "end"));

    }

    @Test
    public void test02___InstanteDeInicioInvalido() {

        boolean succeeded = false;

        try {
            Task02.execute(invalidStart, invalidEnd);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded, Messages.task02_InvalidStart);

    }

    @Test
    public void test03___InstanteDeTerminoInvalido() {

        boolean succeeded = false;

        try {
            Task02.execute(end, start);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded, Messages.task02_InvalidEnd);

    }

    @Test
    public void test04___InstantesIguais() {

        boolean succeeded = false;

        try {
            succeeded = (Task02.execute(start, start) == 0l);
        } catch (Throwable t) {
        }
        assertForInputValidation(succeeded, Messages.task02_ShouldBeZero);

    }

    @Test
    public void test05___InstantesValidos() {

        boolean succeeded = false;

        try {
            succeeded = (Task02.execute(start, end) == 315532800l);
        } catch (Throwable t) {
        }
        assertForInputValidation(succeeded, Messages.task02_ShouldBe315532800);

    }

}