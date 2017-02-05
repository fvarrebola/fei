package br.edu.fei.hcii17;

import java.io.Writer;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

import javax.script.ScriptContext;
import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import javax.script.SimpleScriptContext;

import br.edu.fei.hcii17.test.Task04Test;

/**
 * <b>TAREFA 04</b><br />
 * <br/>
 * <b>OBJETIVO</b>: <br />
 * O objetivo deste experimento é complementar o corpo do método {@link #execute(String, Path)}, executando um
 * <code>script</code> JavaScript e direcionando a saída da execução para um arquivo.<br />
 * <br />
 * <b>INSTRUÇÕES</b>: <br />
 * Você deve substituir as expressões <code>voceVaiMeSubstituir</code> com base nas dicas deixadas em comentários logo
 * acima da expressão. <br />
 * Para isso, você muito provavelmente irá utilizar um dos assistentes de código disponíveis (aqueles exibidos quando
 * pressionamos a combinação CTRL+SPACE).<br />
 * Para determinar se suas substituições estão corretas sempre utilize os testes unitários disponíveis na classe
 * {@link Task04Test}. E uma vez que todos os testes unitários forem executados com sucesso, a tarefa terminou.
 * 
 */
@SuppressWarnings({ "unused", "javadoc" })
public class Task04 {

    private static final Writer voceVaiMeSubstituir_1 = null;
    private static final ScriptEngine voceVaiMeSubstituir_2 = null;
    private static final Object voceVaiMeSubstituir_3 = null;
    
    private static final int MAX_SCRIPT_LENGTH = 256;
    private static final String JS_ENGINE = "JavaScript";

    /**
     * Executa um script JavaScript e armazena a saída em um arquivo.<br />
     * 
     * @param script
     *            o {@link String} que representa o script
     * 
     * @return o {@link Object} que representa o resultado da execução do script
     * 
     * @throws Exception
     *             caso a execução do script falhe
     */
    public static Object execute(String script, Path path) throws Exception {

        if (script == null || path == null) {
            throw new IllegalArgumentException();
        }

        if ((script.isEmpty() || script.length() > MAX_SCRIPT_LENGTH) || !Files.isWritable(path)) {
            throw new IllegalArgumentException();
        }

        ScriptContext context = new SimpleScriptContext();
        ScriptEngineManager scriptEngineManager = new ScriptEngineManager();
        
        
        // ********************************************************************************
        // *
        // * Encontre o método que obtém um writer derivado de 'path'
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código terá uma única linha, similar a:
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO' e 'PARAMETROS' serão substituídos.
        // Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)
        //
        // context.setWriter(TIPO_OU_METODO.METODO(PARAMETROS));
        //
        // ********************************************************************************
        context.setWriter(voceVaiMeSubstituir_1);

        
        // ********************************************************************************
        // *
        // * Encontre o método que obtém um engine Javascript
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código terá uma única linha, similar a:
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO' e 'PARAMETROS' serão substituídos.
        // Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)
        //
        //  ScriptEngine engine = TIPO_OU_OBJETO.METODO(PARAMETROS);
        //
        // ********************************************************************************
        ScriptEngine engine = voceVaiMeSubstituir_2; 
        
        
        // ********************************************************************************
        // *
        // * Encontre o método que executa o script 'script' e utiliza o contexto 'context'
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código terá uma única linha, similar a:
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO' e 'PARAMETROS' serão substituídos.
        // Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)
        //
        // return TIPO_OU_OBJETO.METODO(PARAMETROS);
        //
        // ********************************************************************************
        return voceVaiMeSubstituir_3; 

    }

}
