package br.edu.fei.hcii17;

import java.lang.reflect.Array;
import java.util.Base64;
import java.util.List;
import java.util.Base64.Decoder;
import java.util.Base64.Encoder;
import java.util.function.Predicate;

/**
 * <b>TAREFA DE ADAPTAÇÃO</b><br />
 * <br/>
 * <b>OBJETIVO</b>: <br />
 * O objetivo deste experimento é complementar o corpo dos métodos {@link #encode(byte)} e
 * {@link #decode(String)}.<br />
 * O método {@link #encode(byte)} recebe um vetor de bytes <code>input</code> que deve ser codificado para um
 * {@link String} Base64. Já o método {@link #decode(String)} faz o inverso; recebe um {@link String} <code>input</code>
 * em Base64 que deve ser decodificado para um vetor de bytes. <br />
 * <br />
 * <b>INSTRUÇÕES</b>: <br />
 * Você deve substituir as expressões <code>voceVaiMeSubstituir</code> com base nas dicas deixadas em comentários logo
 * acima da expressão. <br />
 * Para isso, você muito provavelmente irá utilizar um dos assistentes de código disponíveis (aqueles exibidos quando
 * pressionamos a combinação CTRL+SPACE).<br />
 * Para determinar se suas substituições estão corretas sempre utilize os testes unitários disponíveis na classe
 * {@link PracticeTaskTest}. E uma vez que todos os testes unitários forem executados com sucesso, a tarefa terminou.
 * 
 */
@SuppressWarnings("unused")
public class PracticeTask {

    private static final Encoder voceVaiMeSubstituir_1 = null;
    private static final String voceVaiMeSubstituir_2 = null;
    private static final Decoder voceVaiMeSubstituir_3 = null;
    private static final byte[] voceVaiMeSubstituir_4 = null;

    /**
     * Codifica um vetor de bytes em base64.<br />
     * 
     * @param input
     *            o vetor de bytes que representa o valor a ser convertido
     * 
     * @return o {@link String} que representa o vetor original convertido em base64
     */
    public static String encode(byte[] input) {

        if (input == null || Array.getLength(input) == 0) {
            throw new IllegalArgumentException();
        }
        
        // ********************************************************************************
        // *
        // * Encontre o método que obtém um codificador (encoder) Base64
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código será similar a:
        // (Note que os termos 'TIPO_OU_OBJETO' e 'METODO' serão substituídos)
        //
        // Encoder encoder = TIPO_OU_OBJETO.METODO;
        //
        // ********************************************************************************
        Encoder encoder = voceVaiMeSubstituir_1; 

        // ********************************************************************************
        // *
        // * Encontre o método codifica o byte[] 'input' e retorna uma String
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código vai terá única linha, similar a:
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO' e 'PARAMETROS' serão substituídos)
        //
        // TIPO_OU_OBJETO.METODO(PARAMETROS);
        //
        // ********************************************************************************
        return voceVaiMeSubstituir_2; 
        
    }

    /**
     * Decodifica um {@link String} em base64.<br />
     * 
     * @param input
     *            o {@link String} que representa o valor a ser decodificado
     * 
     * @return o o byte array que representa o valor decodificado
     */
    public static byte[] decode(String input) {

        if (input == null || input.isEmpty()) {
            throw new IllegalArgumentException();
        }

        // ********************************************************************************
        // *
        // * Encontre o método que obtém um decodificador (decoder) Base64
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código será similar a:
        // (Note que os termos 'TIPO_OU_OBJETO' e 'METODO' serão substituídos)
        //
        // Decoder decoder = TIPO_OU_OBJETO.METODO;
        //
        // ********************************************************************************
        Decoder decoder = voceVaiMeSubstituir_3; 

        // ********************************************************************************
        // *
        // * Encontre o método decodifica o String 'input' e retorna um byte[]
        // *
        // ********************************************************************************
        //
        // Após encontrar o método adequado, seu código terá uma única linha, similar a:
        // (Note que os termos 'TIPO_OU_OBJETO', 'METODO' e 'PARAMETROS' serão substituídos)
        //
        // TIPO_OU_OBJETO.METODO(PARAMETROS);
        //
        // ********************************************************************************
        return voceVaiMeSubstituir_4; 

    }
}
