package br.edu.fei.hcii17.test.internal.tc;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runners.MethodSorters;

import br.edu.fei.hcii17.Task01;
import br.edu.fei.hcii17.test.internal.Messages;
import br.edu.fei.hcii17.test.internal.TestUtils;

@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class Task01Test extends AbstractTestCase {

    private static final String tmpDir = System.getProperty("java.io.tmpdir");
    private static final String fromDirName = "input-";
    private static final String toDirName = "output-";

    private static final Path tmpDirAsPath = Paths.get(tmpDir);
    private static final Path taskTmpDirAsPath = Paths.get(tmpDir, "hcii17", "practice");

    private static final String FILE_PREFIX = "file-";

    private static final String PDF_FILE_EXTENSION = ".pdf";
    private static final String TXT_FILE_EXTENSION = ".txt";

    @Override
    protected void setUp() throws Exception {
        Files.createDirectories(taskTmpDirAsPath);
    }

    public static Path createTempDirectory(String prefix) throws IOException {
        return Files.createTempDirectory(taskTmpDirAsPath, prefix);
    }

    @Test
    public void test01___ParametrosDeEntradaSaoNulos() {

        boolean succeeded = false;

        Path to = null;
        try {
            to = createTempDirectory(toDirName);
            Task01.execute(null, to);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        } finally {
            TestUtils.delete(to);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.global_ParamIsNullOrEmpty, "from"));

        succeeded = false;
        Path from = null;
        try {
            from = createTempDirectory(fromDirName);
            Task01.execute(from, null);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        } finally {
            TestUtils.delete(from);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.global_ParamIsNullOrEmpty, "to"));

    }

    @Test
    public void test02___ParametrosDeEntradaNaoSaoDiretorios() {

        boolean succeeded = false;

        Path from = null;
        Path to = null;
        try {
            from = TestUtils.createTempFile(createTempDirectory(fromDirName), FILE_PREFIX, PDF_FILE_EXTENSION);
            to = TestUtils.createTempFile(createTempDirectory(toDirName), FILE_PREFIX, PDF_FILE_EXTENSION);
            Task01.execute(from, to);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        } finally {
            TestUtils.delete(from);
            TestUtils.delete(to);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.task01_NonExistantDir, "from"));

    }

    @Test
    public void test03___DiretoriosNaoExistem() {

        boolean succeeded = false;

        Path from = tmpDirAsPath.resolve(fromDirName);
        Path to = null;
        try {
            to = createTempDirectory(toDirName);
            Task01.execute(from, to);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        } finally {
            TestUtils.delete(to);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.task01_NonExistantDir, "from"));

        succeeded = false;
        from = null;
        to = tmpDirAsPath.resolve(toDirName);
        try {
            TestUtils.delete(to);
            from = createTempDirectory(fromDirName);
            Task01.execute(from, to);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        } finally {
            TestUtils.delete(from);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.task01_NonExistantDir, "to"));

    }

    @Test
    public void test04___DiretoriosEstaoVazios() {

        boolean succeeded = false;

        Path from = null;
        Path to = null;
        try {
            from = createTempDirectory(fromDirName);
            to = createTempDirectory(toDirName);
            Task01.execute(from, to);
            succeeded = (Files.list(to).count() == 0);
        } catch (Throwable t) {
        } finally {
            TestUtils.delete(from);
            TestUtils.delete(to);
        }
        assertForWrongFunction(succeeded, Messages.global_DidYouChoseTheRightFunction);
    }

    @Test
    public void test05___DiretoriosJaContemArquivos() {

        boolean succeeded = false;

        Path from = null;
        Path to = null;
        try {
            from = createTempDirectory(fromDirName);
            to = createTempDirectory(toDirName);
            TestUtils.createTempFile(from, FILE_PREFIX, PDF_FILE_EXTENSION);
            TestUtils.createTempFile(to, FILE_PREFIX, PDF_FILE_EXTENSION);
            Task01.execute(from, to);
            succeeded = (Files.list(to).count() == 2);
        } catch (Throwable t) {
        } finally {
            TestUtils.delete(from);
            TestUtils.delete(to);
        }

        assertForWrongFunction(succeeded, Messages.global_DidYouChoseTheRightFunction);

    }

    @Test
    public void test06___DiretorioDeEntradaContemApenasPDFs() {

        boolean succeeded = false;

        Path from = null;
        Path to = null;
        try {
            from = createTempDirectory(fromDirName);
            to = createTempDirectory(toDirName);
            Task01.execute(from, to);
            TestUtils.createTempFile(from, FILE_PREFIX, PDF_FILE_EXTENSION);
            TestUtils.createTempFile(from, FILE_PREFIX, PDF_FILE_EXTENSION);
            Task01.execute(from, to);
            succeeded = (Files.list(to).count() == 2);
        } catch (Throwable t) {
        } finally {
            TestUtils.delete(from);
            TestUtils.delete(to);
        }
        assertForWrongFunction(succeeded, Messages.global_DidYouChoseTheRightFunction);

    }

    @Test
    public void test07___DiretorioDeEntradaContemTodoTipoDeArquivo() {

        boolean succeeded = false;

        Path from = null;
        Path to = null;
        try {
            from = createTempDirectory(fromDirName);
            to = createTempDirectory(toDirName);
            Task01.execute(from, to);
            TestUtils.createTempFile(from, FILE_PREFIX, PDF_FILE_EXTENSION);
            TestUtils.createTempFile(from, FILE_PREFIX, PDF_FILE_EXTENSION);
            TestUtils.createTempFile(from, FILE_PREFIX, TXT_FILE_EXTENSION);
            Task01.execute(from, to);
            succeeded = (Files.list(to).count() == 2);
        } catch (Throwable t) {
        } finally {
            TestUtils.delete(from);
            TestUtils.delete(to);
        }
        assertForWrongFunction(succeeded, Messages.global_DidYouChoseTheRightFunction);

    }

    @Test
    public void test08___DiretorioDeEntradaNaoContemPDFs() {

        boolean succeeded = false;

        Path from = null;
        Path to = null;
        try {
            from = createTempDirectory(fromDirName);
            to = createTempDirectory(toDirName);
            TestUtils.createTempFile(from, FILE_PREFIX, TXT_FILE_EXTENSION);
            Task01.execute(from, to);
            succeeded = (Files.list(to).count() == 0);
        } catch (Throwable t) {
        } finally {
            TestUtils.delete(from);
            TestUtils.delete(to);
        }
        assertForWrongFunction(succeeded, Messages.global_DidYouChoseTheRightFunction);

    }

}
