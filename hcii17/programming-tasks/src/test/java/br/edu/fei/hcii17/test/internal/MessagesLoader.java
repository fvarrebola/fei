package br.edu.fei.hcii17.test.internal;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;
import java.text.MessageFormat;
import java.util.MissingResourceException;
import java.util.ResourceBundle;

/**
 * Classe abstrata para carregamento de mensagens dos testes unitários.<br />
 * 
 * @author arrebola
 *
 */
public abstract class MessagesLoader {

    private static ResourceBundle bundle;

    /**
     * Inicializa as mensagens de um <i>resource bundle</i>.
     * 
     * @param baseName
     *            o {@link String} que representa o nome base do <i>bundle</i>
     * @param clazz
     *            o {@link Class} que representa a classe a ser carregada
     */
    public static void initializeMessages(final String baseName, final Class<?> clazz) {

        if (baseName == null || clazz == null) {
            throw new IllegalArgumentException();
        }

        try {
            bundle = ResourceBundle.getBundle(baseName);
        } catch (MissingResourceException ex) {
            return;
        }

        Field[] fields = clazz.getDeclaredFields();
        for (Field field : fields) {
            final int mod = field.getModifiers();
            if (Modifier.isPublic(mod) && Modifier.isStatic(mod) && !field.isAccessible()) {
                field.setAccessible(true);
            }
            try {
                field.set(clazz, bundle.getString(field.getName()));
            } catch (Exception ex) {
            }
        }

    }

    /**
     * Retorna a mensagem formatada de acordo com os parâmetros informados.<br />
     * 
     * @param message
     *            o @link{String} que representa a mensagem
     * @param params
     *            o vetor de {@link Object} que representa os parâmetros para a mensagem
     * 
     * @return o {@link String} que representa a mensagem
     */
    public static String bind(String message, Object... params) {
        return MessageFormat.format(message, params);
    }

}
