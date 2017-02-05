package br.edu.fei.hcii17;

import java.time.LocalDateTime;

import br.edu.fei.hcii17.test.Task02Test;

/**
 * <b>TAREFA 02</b><br />
 * <br/>
 * <b>OBJETIVO</b>: <br />
 * O objetivo deste experimento é complementar o corpo do método {@link #execute(LocalDateTime, LocalDateTime)},
 * calculando a diferença em segundos entre um instante de início <code>start</code> e um instante de término
 * <code>end</code>. <br />
 * <br />
 * <b>INSTRUÇÕES</b>: <br />
 * Você deve substituir as expressões <code>voceVaiMeSubstituir</code> com base nas dicas deixadas em comentários logo
 * acima da expressão. <br />
 * Para isso, você muito provavelmente irá utilizar um dos assistentes de código disponíveis (aqueles exibidos quando
 * pressionamos a combinação CTRL+SPACE).<br />
 * Para determinar se suas substituições estão corretas sempre utilize os testes unitários disponíveis na classe
 * {@link Task02Test}. E uma vez que todos os testes unitários forem executados com sucesso, a tarefa terminou.
 * 
 */
@SuppressWarnings({"unused", "javadoc"})
public class Task02 {

    private static final boolean voceVaiMeSubstituir_1 = false;
    private static final long voceVaiMeSubstituir_2 = -1l;

    /**
     * Determina a diferença em segundos entre dois instantes de tempo.<br />
     * 
     * @param start
     *            o {@link LocalDateTime} que representa o instante inicial
     * @param end
     *            o {@link LocalDateTime} que representa o instante final
     *            
     * @return a diferença em segundos
     */
    public static long execute(LocalDateTime start, LocalDateTime end) {

        if (start == null || end == null) {
            throw new IllegalArgumentException();
        }

        // ********************************************************************************
        // *
        // * Encontre o método que verifica se 'start' eh superior ao instante atual
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código será similar a:
        // (Note que os termos 'METODO' e 'PARAMETROS' serão substituídos)
        // (Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)        
        //
        // if (start.METODO(PARAMETROS)) {
        //     throw new IllegalArgumentException();
        // }
        //
        // ********************************************************************************
        if (voceVaiMeSubstituir_1) {
            throw new IllegalArgumentException();
        }

        // ********************************************************************************
        // *
        // * Encontre o método que verifica se 'end' eh anterior ao instante 'start'
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código será similar a:
        // (Note que os termos 'METODO' e 'PARAMETROS' serão substituídos)
        // (Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)
        //
        // if (end.METODO(PARAMETROS)) {
        //     throw new IllegalArgumentException();
        // }
        //
        // ********************************************************************************
        if (voceVaiMeSubstituir_1) { 
            throw new IllegalArgumentException();
        }

        // ********************************************************************************
        // *
        // * Encontre os métodos que determinam a duracao entre 'start' e 'end' em segundos
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código terá uma única linha, similar a:
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO' e 'PARAMETROS' serão substituídos)
        // (Note também que o termo 'PARAMETROS' representa 0 ou mais elementos)
        //
        // return TIPO_OU_OBJETO.METODO(PARAMETROS).METODO(PARAMETROS)
        //
        // ********************************************************************************
        return voceVaiMeSubstituir_2;

    }

}