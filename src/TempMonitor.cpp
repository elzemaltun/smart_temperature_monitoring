#include <WiFi.h>
#include <PubSubClient.h>
#include "TempSensor.h"
#define MSG_BUFFER_SIZE  50

const char* ssid = "TIM-32566672";
const char* password = "YsEkKN5C3TUFFt44thCz2seF";
const char* mqtt_server = "broker.mqtt-dashboard.com";

/* MQTT topic */
const char* topic = "temperature";

// LEDs and TMP pins
#define GREEN_LED 5
#define RED_LED 13
#define TEMP_PIN 34

// Temp calculation
TempSensor tempSensor(TEMP_PIN);

/* MQTT client management */
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsgTime = 0;
char msg[MSG_BUFFER_SIZE];
int value = 0;

void setup_wifi() {
  delay(10);
  Serial.println(String("Connecting to ") + ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

/* MQTT subscribing callback */
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println(String("Message arrived on [") + topic + "] len: " + length );
}

void reconnect() {
  
  // Loop until we're reconnected  
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Create a random client ID
    String clientId = String("esiot-2023-client-")+String(random(0xffff), HEX);

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.subscribe(topic);
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  randomSeed(micros());
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  float temp = tempSensor.readTemperatureC();

  unsigned long now = millis();
  if (now - lastMsgTime > 10000) {
    lastMsgTime = now;
    value++;
    String tempStr = String(temp);

    /* creating a msg in the buffer */
    snprintf (msg, MSG_BUFFER_SIZE, tempStr.c_str(), value);
    Serial.println(String("Publishing message: ") + msg);    

    /* publishing the msg */
    client.publish(topic, tempStr.c_str());  
  }
}
