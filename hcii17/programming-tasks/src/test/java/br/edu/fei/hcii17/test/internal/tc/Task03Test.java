package br.edu.fei.hcii17.test.internal.tc;

import java.util.Arrays;
import java.util.List;
import java.util.function.IntPredicate;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.Stream;

import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runners.MethodSorters;

import br.edu.fei.hcii17.Task03;
import br.edu.fei.hcii17.test.internal.Messages;

@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class Task03Test extends AbstractTestCase {

    private static List<String> DATA = Arrays
            .asList(new String[] { "elementB", "eLeMenTC", "ELEMENTA", "removeMe", "keepMe", "dontRemoveMe" });

    private static List<String> EXPECTED_RESULT = Arrays
            .asList(new String[] { "DONTREMOVEME", "ELEMENTA", "ELEMENTB", "ELEMENTC", "KEEPME" });

    private static Predicate<String> PREDICATE = new Predicate<String>() {
        @Override
        public boolean test(String t) {
            return !t.startsWith("remove");
        }
    };

    private static boolean wasPredicateApplied(Stream<String> stream) {
        return stream.noneMatch(new Predicate<String>() {
            @Override
            public boolean test(String arg0) {
                return arg0.toLowerCase().startsWith("remove");
            }
        });
    }

    private static boolean wasFunctionApplied(Stream<String> stream) {
        return stream.noneMatch(new Predicate<String>() {
            @Override
            public boolean test(String arg0) {
                return arg0.chars().anyMatch(new IntPredicate() {
                    @Override
                    public boolean test(int value) {
                        return (value > 96 && value < 123);
                    }
                });
            }
        });
    }

    @Test
    public void test01___ParametrosDeEntradaSaoNulos() {

        boolean succeeded = false;

        try {
            Task03.execute(null, PREDICATE);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.global_ParamIsNullOrEmpty, "list"));

        try {
            Task03.execute(DATA, null);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.global_ParamIsNullOrEmpty, "predicate"));

    }

    @Test
    public void test02___ListaInvalida() {

        boolean succeeded = false;

        try {
            Task03.execute(Arrays.asList(new String[] {}), PREDICATE);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded, Messages.task03_InvalidList);

    }

    @Test
    public void test03___PredicateNaoFoiAplicado() {

        boolean succeeded = false;

        try {
            Stream<String> stream = Task03.execute(DATA, PREDICATE);
            if (stream == null) {
                failForWrongFunction(Messages.task03_NullStream);
            }
            succeeded = wasPredicateApplied(stream);
        } catch (Exception ex) {
        }
        assertForWrongFunction(succeeded, Messages.task03_PredicateHasNotBeenApplied);

    }

    @Test
    public void test04___FunctionNaoFoiAplicado() {

        boolean succeeded = false;

        try {
            Supplier<Stream<String>> supplier = () -> Task03.execute(DATA, PREDICATE);
            if (supplier.get() == null) {
                failForWrongFunction(Messages.task03_NullStream);
            }
            if (!wasPredicateApplied(supplier.get())) {
                failForWrongFunction(Messages.task03_PredicateHasNotBeenApplied);
            }
            succeeded = wasFunctionApplied(supplier.get());
        } catch (Exception ex) {
        }
        assertForWrongFunction(succeeded, Messages.task03_FunctionHasNotBeenApplied);

    }

    @Test
    public void test05___StreamNaoEstaOrdenado() {

        boolean succeeded = false;

        try {
            Supplier<Stream<String>> supplier = () -> Task03.execute(DATA, PREDICATE);
            if (supplier.get() == null) {
                failForWrongFunction(Messages.task03_NullStream);
            }
            if (!wasPredicateApplied(supplier.get())) {
                failForWrongFunction(Messages.task03_PredicateHasNotBeenApplied);
            }
            if (!wasFunctionApplied(supplier.get())) {
                failForWrongFunction(Messages.task03_FunctionHasNotBeenApplied);
            }
            succeeded = Arrays.equals(EXPECTED_RESULT.toArray(), supplier.get().toArray());

        } catch (Exception ex) {
        }
        assertForWrongFunction(succeeded, Messages.task03_UnsortedStream);

    }

}