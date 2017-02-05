package br.edu.fei.hcii17.test.internal.tc;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import javax.script.ScriptException;

import org.junit.FixMethodOrder;
import org.junit.Test;
import org.junit.runners.MethodSorters;

import br.edu.fei.hcii17.Task04;
import br.edu.fei.hcii17.test.internal.Messages;
import br.edu.fei.hcii17.test.internal.TestUtils;

@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class Task04Test extends AbstractTestCase {

    private static final String tmpDir = System.getProperty("java.io.tmpdir");
    private static final Path taskTmpDirAsPath = Paths.get(tmpDir, "hcii17", "task04");
    private static final String FILE_PREFIX = "file-";
    private static final String JS_FILE_EXTENSION = ".js";

    private static final String HELLO_WORLD = "Hello World.";
    private static final String INVALID_SCRIPT = ";----;";
    private static final String UNDEFINED_FUNCTION_SCRIPT = "undefined-function();";
    private static final String HELLO_WORLD_SCRIPT = "print('" + HELLO_WORLD + "');";

    @Override
    protected void setUp() throws Exception {
        Files.createDirectories(taskTmpDirAsPath);
    }

    @Test
    public void test01___ParametrosDeEntradaSaoNulos() {

        boolean succeeded = false;

        Path path = null;
        try {
            path = TestUtils.createTempFile(taskTmpDirAsPath, FILE_PREFIX, JS_FILE_EXTENSION);
            Task04.execute(null, path);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        } finally {
            TestUtils.delete(path);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.global_ParamIsNullOrEmpty, "script"));

        try {
            Task04.execute(HELLO_WORLD_SCRIPT, null);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.global_ParamIsNullOrEmpty, "path"));
    }

    @Test
    public void test02___ScriptVazio() {

        boolean succeeded = false;

        Path path = null;
        try {
            path = TestUtils.createTempFile(taskTmpDirAsPath, FILE_PREFIX, JS_FILE_EXTENSION);
            Task04.execute("", path);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        } finally {
            TestUtils.delete(path);
        }
        assertForInputValidation(succeeded, Messages.bind(Messages.global_ParamIsNullOrEmpty, "script"));

    }

    @Test
    public void test03___ScriptMuitoExtenso() {

        boolean succeeded = false;

        Path path = null;
        try {
            path = TestUtils.createTempFile(taskTmpDirAsPath, FILE_PREFIX, JS_FILE_EXTENSION);
            Task04.execute(TestUtils.repeat(HELLO_WORLD_SCRIPT, 128), path);
        } catch (Throwable t) {
            succeeded = (t instanceof IllegalArgumentException);
        } finally {
            TestUtils.delete(path);
        }
        assertForInputValidation(succeeded, Messages.task04_ScriptTooBig);

    }

    @Test
    public void test04___ScriptInvalido() {

        boolean succeeded = false;

        Path path = null;
        try {
            path = TestUtils.createTempFile(taskTmpDirAsPath, FILE_PREFIX, JS_FILE_EXTENSION);
            Task04.execute(INVALID_SCRIPT, path);
        } catch (Throwable t) {
            succeeded = (t instanceof ScriptException);
        } finally {
            TestUtils.delete(path);
        }
        assertForWrongFunction(succeeded, Messages.task04_InvalidScript);

        succeeded = false;
        try {
            path = TestUtils.createTempFile(taskTmpDirAsPath, FILE_PREFIX, JS_FILE_EXTENSION);
            Task04.execute(UNDEFINED_FUNCTION_SCRIPT, path);
        } catch (Throwable t) {
            succeeded = (t instanceof ScriptException);
        } finally {
            TestUtils.delete(path);
        }
        assertForWrongFunction(succeeded, Messages.task04_InvalidScript);

    }

    @Test
    public void test05___ScriptValido() {

        boolean succeeded = false;

        Path path = null;
        boolean outputWasSaved = false;
        try {
            path = TestUtils.createTempFile(taskTmpDirAsPath, FILE_PREFIX, JS_FILE_EXTENSION);
            Object output = Task04.execute(HELLO_WORLD_SCRIPT, path);
            String fileOutput = new String(Files.readAllBytes(path));
            outputWasSaved = (fileOutput != null && fileOutput.startsWith(HELLO_WORLD));
            succeeded = (output == null && outputWasSaved);
        } catch (Throwable t) {
        } finally {
            TestUtils.delete(path);
        }
        
        if (outputWasSaved) {
            assertForWrongFunction(succeeded, Messages.task04_ScriptExecutionFailed);
        } else {
            assertForWrongFunction(succeeded, Messages.task04_OutputFileIsEmpty);
        }

    }

}