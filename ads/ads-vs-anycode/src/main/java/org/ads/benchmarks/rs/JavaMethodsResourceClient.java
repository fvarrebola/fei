package org.ads.benchmarks.rs;

import java.util.ArrayList;
import java.util.List;

import javax.validation.constraints.NotNull;
import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.Response.Status;

import org.ads.langs.java.model.JavaMethod;
import org.ads.web.rs.GenericResource;

import com.google.common.reflect.TypeToken;
import com.google.gson.Gson;

/**
 * RESTful client.
 * 
 * @author arrebola
 *
 */
public class JavaMethodsResourceClient {

    private Gson gson;
    
    /**
     * Constructor.<br />
     */
    public JavaMethodsResourceClient() {
        super();
        this.gson = new Gson();
    }

    static TypeToken<GenericResource<JavaMethod>> typeToken = new TypeToken<GenericResource<JavaMethod>>() {
        private static final long serialVersionUID = -7712896744679522266L;
    };
    
    @NotNull
    public List<JavaMethod> list(String input, String nlp, String options) {

        List<JavaMethod> methods = new ArrayList<JavaMethod>();

        Client client = ClientBuilder.newClient();

        WebTarget target = client.target("http://localhost:8080/ads").path("api/java/methods/scenarios")
                .queryParam("input", input).queryParam("nlp", nlp).queryParam("options", options);

        final Response response = target.request(MediaType.APPLICATION_JSON_TYPE).get();
        final int status = response.getStatus();
        if (status == Status.OK.getStatusCode()) {
            final String jsonString = response.readEntity(String.class);
            final GenericResource<JavaMethod> resource = this.gson.fromJson(jsonString, typeToken.getType());
            methods = resource.getItems();
        }

        response.close();
        client.close();

        return methods;

    }

}
