package br.edu.fei.hcii17.test.internal.tc;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runners.MethodSorters;

import br.edu.fei.hcii17.Task05;
import br.edu.fei.hcii17.test.internal.Messages;
import br.edu.fei.hcii17.test.internal.TestUtils;

@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class Task05Test extends AbstractTestCase {

    private static final String tmpDir = System.getProperty("java.io.tmpdir");
    private static final String dirName = "dir-";
    private static final Path taskTmpDirAsPath = Paths.get(tmpDir, "hcii17", "task05");

    private static final String FILE_PREFIX = "file-";
    private static final String TXT_FILE_EXTENSION = ".txt";

    @Override
    protected void setUp() throws Exception {
        Files.createDirectories(taskTmpDirAsPath);
    }

    public static Path createTempDirectory(String prefix) throws IOException {
        return Files.createTempDirectory(taskTmpDirAsPath, prefix);
    }

    @Test
    public void test01___ParametroDeEntradaNulo() {

        boolean succeeded = false;

        try {
            Task05.execute(null);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        } finally {
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.global_ParamIsNullOrEmpty, "path"));

    }

    @Test
    public void test02___ParametrosDeEntradaEhDiretorio() {

        boolean succeeded = false;

        Path path = null;
        try {
            path = createTempDirectory(dirName);
            Task05.execute(path);
        } catch (Throwable t) {
            succeeded = ((t instanceof IllegalArgumentException)
                    && Messages.task05_OnlyFilesShouldBeAccepted.equals(t.getMessage()));
        } finally {
            TestUtils.delete(path);
        }
        assertForWrongFunction(succeeded, Messages.bind(Messages.task05_OnlyFilesShouldBeAccepted));

    }

    @Test
    public void test03___ArquivoNaoPodeSerLido() {

        boolean succeeded = false;

        Path path = null;
        try {
            path = TestUtils.createTempFile(taskTmpDirAsPath, FILE_PREFIX, TXT_FILE_EXTENSION);
            TestUtils.denyReading(path);
            Task05.execute(path);
        } catch (Throwable t) {
            succeeded = ((t instanceof IllegalArgumentException)
                    && Messages.task05_FileIsUnreadable.equals(t.getMessage()));
        } finally {
            TestUtils.delete(path);
        }
        assertForWrongFunction(succeeded, Messages.bind(Messages.task05_FileIsUnreadable));

    }

    @Test
    public void test05___ArquivoVazio() {

        boolean succeeded = false;

        Path path = null;
        try {
            path = TestUtils.createTempFile(taskTmpDirAsPath, FILE_PREFIX, TXT_FILE_EXTENSION);
            succeeded = (Task05.execute(path).count() == 0);
        } catch (Throwable t) {
        } finally {
            TestUtils.delete(path);
        }
        assertForWrongFunction(succeeded, Messages.bind(Messages.task05_CouldNotReadFile));

    }

    @Test
    public void test06___ArquivoValido() {

        boolean succeeded = false;

        long count = 0;
        final long expectedCount = 3;

        Path path = null;
        try {
            path = TestUtils.createTempFile(taskTmpDirAsPath, FILE_PREFIX, TXT_FILE_EXTENSION);
            Files.write(path, Messages.task05_randomContent.getBytes());
            count = Task05.execute(path).count();
            succeeded = (count == expectedCount);
        } catch (Throwable t) {
        } finally {
            TestUtils.delete(path);
        }

        if (count != expectedCount) {
            assertForWrongFunction(succeeded, Messages.bind(Messages.task05_UnexpectedLineCount, expectedCount, count));
        } else {
            assertForWrongFunction(succeeded, Messages.bind(Messages.task05_CouldNotReadFile));
        }

    }

}
