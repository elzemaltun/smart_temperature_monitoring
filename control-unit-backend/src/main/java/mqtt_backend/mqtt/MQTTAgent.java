package mqtt_backend.mqtt;

import io.netty.handler.codec.mqtt.MqttQoS;
import io.vertx.core.AbstractVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.buffer.Buffer;
import io.vertx.ext.web.Router;
import io.vertx.ext.web.RoutingContext;
import io.vertx.ext.web.handler.BodyHandler;
import io.vertx.mqtt.MqttClient;
import io.vertx.core.http.HttpServerResponse;
import io.vertx.core.json.JsonArray;
import io.vertx.core.json.JsonObject;

import java.util.ArrayList;
import java.util.List;

public class MQTTAgent extends AbstractVerticle{
	
	private static final String BROKER_ADRESS = "broker.mqtt-dashboard.com";
    private static final String TOPIC_NAME = "temperature";

    // Store the received temperature messages
    private List<String> messageHistory = new ArrayList<>();

	// set the states by ccreating control unit class
	private ControlUnit controlUnit;

    // Constructor for initalization
    public MQTTAgent() {
	}

    // Override start method in the AbstractVerticle class
    @Override
    public void start() {		
		MqttClient client = MqttClient.create(vertx);
        client.connect(1883, BROKER_ADRESS, c-> {

			client.publishHandler(s -> {
			    System.out.println(s.topicName() + ": " + s.payload().toString());
			    System.out.println("QoS: " + s.qosLevel());

                String temperature = s.payload().toString();
                messageHistory.add(temperature);

				float currentTemperature = Float.parseFloat(temperature);
                controlUnit.updateState(currentTemperature);
			})
			.subscribe(TOPIC_NAME, 2);		

			client.publish(TOPIC_NAME,
				  Buffer.buffer("Sent by MQTT Agent"),
				  MqttQoS.AT_LEAST_ONCE,
				  false,
				  false);
		}); 
    }

}