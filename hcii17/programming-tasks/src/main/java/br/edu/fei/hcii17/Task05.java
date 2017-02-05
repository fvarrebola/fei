package br.edu.fei.hcii17;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;
import java.util.stream.Stream;

import br.edu.fei.hcii17.test.Task01Test;
import br.edu.fei.hcii17.test.internal.Messages;

/**
 * <b>TAREFA 05</b><br />
 * <br />
 * <b>OBJETIVO</b>: <br />
 * O objetivo deste experimento é complementar o corpo do método {@link #execute(path)} e ler o conteúdo de um arquivo
 * de entrada, removendo as linha duplicadas.<br />
 * <br />
 * 
 * <b>INSTRUÇÕES</b>: <br />
 * Você deve substituir as expressões <code>voceVaiMeSubstituir</code> com base nas dicas deixadas em comentários logo
 * acima da expressão. <br />
 * Para isso, você muito provavelmente irá utilizar um dos assistentes de código disponíveis (aqueles exibidos quando
 * pressionamos a combinação CTRL+SPACE).<br />
 * Para determinar se suas substituições estão corretas sempre utilize os testes unitários disponíveis na classe
 * {@link Task05Test}. E uma vez que todos os testes unitários forem executados com sucesso, a tarefa terminou.
 * 
 */
@SuppressWarnings({ "unused", "javadoc" })
public class Task05 {

    private static final boolean voceVaiMeSubstituir_1 = false;
    private static final boolean voceVaiMeSubstituir_2 = false;
    private static final Stream<String> voceVaiMeSubstituir_3 = null;

    /**
     * Lê o conteúdo de um arquivo.<br/>
     * 
     * @param path
     *            o {@link Path} que representa o caminho para o arquivo
     * 
     * @return o {@link Stream} de {@link String} que representa as linhas do arquivo
     * 
     * @throws IOException
     */
    public static Stream<String> execute(Path path) throws IOException {

        if (path == null) {
            throw new IllegalArgumentException();
        }

        // ********************************************************************************
        // *
        // * Encontre os métodos que verificam se a variável 'path' é um arquivo
        // *
        // ********************************************************************************
        //
        // Após encontrar os métodos adequados, seu código será similar a:
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO_01', 'METODO_02' e 'PARAMETROS' 
        // serão substituídos. Note também que o termo 'PARAMETROS' representa 0 ou mais 
        // elementos)
        //
        // if (!TIPO_OU_OBJETO.METODO_01(PARAMETROS).METODO_02(PARAMETROS)) {
        //     throw new IllegalArgumentException(Messages.task05_OnlyFilesShouldBeAccepted);
        // }
        //
        // Alternativamente, seu código também poderá ser similar a:
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO' e 'PARAMETROS' serão substituídos.
        // Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)
        //
        // if (!TIPO_OU_OBJETO.METODO(PARAMETROS)) {
        //     throw new IllegalArgumentException(Messages.task05_OnlyFilesShouldBeAccepted);
        // }
        //
        // ********************************************************************************
        if (voceVaiMeSubstituir_1) {
            throw new IllegalArgumentException(Messages.task05_OnlyFilesShouldBeAccepted);
        }

        // ********************************************************************************
        // *
        // * Encontre os métodos que verificam se o arquivo 'path' pode ser lido
        // *
        // ********************************************************************************
        //
        // Após encontrar os métodos adequados, seu código será similar a:
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO' e 'PARAMETROS' serão substituídos.
        // Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)
        //
        // if (!TIPO_OU_OBJETO.METODO(PARAMETROS)) {
        //     throw new IllegalArgumentException(Messages.task05_FileIsUnreadable);
        // }
        //
        // ********************************************************************************
        if (voceVaiMeSubstituir_2) {
            throw new IllegalArgumentException(Messages.task05_FileIsUnreadable);
        }

        // ********************************************************************************
        // *
        // * Encontre os métodos que lêem todas as linhas do arquivo 'path' e retornam 
        // * apenas as linhas distintas (removendo as linhas duplicadas)
        // *
        // ********************************************************************************
        //
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO_01', 'METODO_02' e 'PARAMETROS' 
        // serão substituídos. Note também que o termo 'PARAMETROS' representa 0 ou mais 
        // elementos)
        //
        // return TIPO_OU_OBJETO.METODO_01(PARAMETROS).METODO_02(PARAMETROS);
        //
        // ********************************************************************************
        return voceVaiMeSubstituir_3;

    }
}
