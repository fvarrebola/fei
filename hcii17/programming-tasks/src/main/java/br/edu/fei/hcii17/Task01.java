package br.edu.fei.hcii17;

import java.io.IOException;
import java.nio.file.FileVisitResult;
import java.nio.file.FileVisitor;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;
import java.nio.file.attribute.BasicFileAttributes;

import br.edu.fei.hcii17.test.Task01Test;

/**
 * <b>TAREFA 01</b><br />
 * <br />
 * <b>OBJETIVO</b>: <br />
 * O objetivo deste experimento é complementar o corpo do método {@link #execute(String, String)} e copiar os arquivos
 * de um diretório de entrada <code>from</code> para um diretório de destino <code>to</code>.<br />
 * <br />
 * 
 * <b>INSTRUÇÕES</b>: <br />
 * Você deve substituir as expressões <code>voceVaiMeSubstituir</code> com base nas dicas deixadas em comentários logo
 * acima da expressão. <br />
 * Para isso, você muito provavelmente irá utilizar um dos assistentes de código disponíveis (aqueles exibidos quando
 * pressionamos a combinação CTRL+SPACE).<br />
 * Para determinar se suas substituições estão corretas sempre utilize os testes unitários disponíveis na classe
 * {@link Task01Test}. E uma vez que todos os testes unitários forem executados com sucesso, a tarefa terminou.
 * 
 */
@SuppressWarnings("unused")
public class Task01 {

    private static final boolean voceVaiMeSubstituir_1 = false;
    private static final Path voceVaiMeSubstituir_2 = null;
    
    /**
     * Copia os arquivos do diretório de entrada <code>from</code> para o diretório de saída <code>to</code>.<br/>
     * 
     * @param from
     *            o {@link Path} que representa o diretório de entrada
     * @param to
     *            o {@link Path} que representa o diretório de saída
     *            
     * @return o {@link Path} que representa o primeiro arquivo do diretório avaliado
     * 
     * @throws IOException
     */
    public static Path execute(Path from, Path to) throws IOException {

        if (from == null || to == null) {
            throw new IllegalArgumentException();
        }

        // ********************************************************************************
        // *
        // * Encontre os métodos que verificam se as variáveis 'from' e 'to' são diretórios
        // *
        // ********************************************************************************
        //
        // Após encontrar os métodos adequados, seu código será similar a:
        // (Note que os termos 'METODO_01', 'METODO_02' e 'PARAMETROS' serão substituídos)
        // (Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)        
        //
        // if (!from.METODO_01(PARAMETROS).METODO_02(PARAMETROS) || !to.METODO_01(PARAMETROS).METODO_02(PARAMETROS)) {
        //     throw new IllegalArgumentException();
        // }
        //
        // ********************************************************************************
        if (voceVaiMeSubstituir_1) {
            throw new IllegalArgumentException();
        }

        final FileVisitor<Path> visitor = new FileVisitor<Path>() {

            @Override
            public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
                return FileVisitResult.CONTINUE;
            }

            @Override
            public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs) throws IOException {
                return FileVisitResult.CONTINUE;
            }

            @Override
            public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
                if (file.toString().endsWith(".pdf")) {
                    Files.copy(file, to.resolve(file.getFileName()), StandardCopyOption.REPLACE_EXISTING);
                }
                return FileVisitResult.CONTINUE;
            }

            @Override
            public FileVisitResult visitFileFailed(Path file, IOException exc) throws IOException {
                return FileVisitResult.CONTINUE;
            }

        };

        // ********************************************************************************
        // *
        // * Encontre o método que lista o diretório de entrada 'from' e utiliza a
        // * variável 'visitor' para realizar a cópia dos arquivos com filtros
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código terá uma única linha, similar a:
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO' e 'PARAMETROS' serão substituídos)
        // (Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)
        //
        // return TIPO_OU_OBJETO.METODO(PARAMETROS);
        //
        // ********************************************************************************
        return voceVaiMeSubstituir_2;

    }

}
