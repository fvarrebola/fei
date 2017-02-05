package br.edu.fei.hcii17;

import java.util.List;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Stream;

import br.edu.fei.hcii17.test.Task03Test;

/**
 * <b>TAREFA 03</b><br />
 * <br/>
 * <b>OBJETIVO</b>: <br />
 * O objetivo deste experimento é complementar o corpo do método {@link #execute(List, Predicate)}, filtrando o
 * <code>list</code> de entrada com o <code>predicate</code>, e modificando e ordenando o conteúdo da lista
 * resultante.<br />
 * <br />
 * <b>INSTRUÇÕES</b>: <br />
 * Você deve substituir as expressões <code>voceVaiMeSubstituir</code> com base nas dicas deixadas em comentários logo
 * acima da expressão. <br />
 * Para isso, você muito provavelmente irá utilizar um dos assistentes de código disponíveis (aqueles exibidos quando
 * pressionamos a combinação CTRL+SPACE).<br />
 * Para determinar se suas substituições estão corretas sempre utilize os testes unitários disponíveis na classe
 * {@link Task03Test}. E uma vez que todos os testes unitários forem executados com sucesso, a tarefa terminou.
 * 
 */
@SuppressWarnings({"unused", "javadoc"})
public class Task03 {

    private static final Stream<String> voceVaiMeSubstituir_1 = null;
    private static final Stream<String> voceVaiMeSubstituir_2 = null;

    /**
     * Filtra, modifica e ordena o conteúdo de uma lista.<br />
     * 
     * @param list
     *            o {@link List} que representa a lista a ser filtrada, modificada e ordenada
     * @param predicate
     *            o {@link Predicate} que representa função de filtro
     *            
     * @return o {@link Stream} que representa a lista filtrada, modificada e ordenada
     */
    public static Stream<String> execute(List<String> list, Predicate<String> predicate) {

        Stream<String> stream = null;

        if (list == null || list.isEmpty() || predicate == null) {
            throw new IllegalArgumentException();
        }

        // ********************************************************************************
        // *
        // * Encontre os métodos que aplicam o 'predicate' no 'list'
        // *
        // ********************************************************************************
        //
        // Após encontrar os métodos adequados, seu código terá uma única linha, similar a:
        // (Note que os termos 'METODO_01' e 'METODO_02' serão substituídos)
        // (Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)
        //
        // stream = list.METODO_01(PARAMETROS).METODO_02(PARAMETROS);
        //
        // ********************************************************************************
        stream = voceVaiMeSubstituir_1;

        Function<String, String> function = new Function<String, String>() {
            @Override
            public String apply(String t) {
                return t.toUpperCase();
            }
        };

        // ********************************************************************************
        // *
        // * Encontre os métodos que aplicam o 'function' no 'stream' e fazem ordenação
        // *
        // ********************************************************************************
        //
        // Após encontrar os métodos adequados, seu código terá uma única linha, similar a:
        // (Note que os termos 'METODO_01' e 'METODO_02' serão substituídos)
        // (Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)
        //
        // return stream.METODO_01(PARAMETROS).METODO_02(PARAMETROS);
        //
        // ********************************************************************************
        return voceVaiMeSubstituir_2; 

    }

}
