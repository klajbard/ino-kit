#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <Adafruit_BME280.h>

#define mqtt_user "MQTT_USERNAME"
#define mqtt_password "MQTT_PASSWORD"
#define WIFI_RETRIES 20

Adafruit_BME280 bme;

float temperature, humidity, pressure;
int conn_tries = 0;

const char* ssid = "WIFI_SSID";
const char* ss_pswd = "WIFI_PASSWORD";
const char* mqtt_server = "MQTT_SERVER_IP";

WiFiClient EspClient;
PubSubClient client(EspClient);

void wifi_setup() {
  WiFi.forceSleepWake();
  delay(100);
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.begin(ssid, ss_pswd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String ClientId = "ESP8266";
    ClientId += String(random(0xffff), HEX);
    if (client.connect(ClientId.c_str(), mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());
      delay(5000);
    }
  }
}
void sendMQTTMessage(double temperature, double humidity, double pressure) {
  StaticJsonDocument<300> json_data;
  char buffer[512];
 
  json_data["temperature"] = temperature;
  json_data["humidity"] = humidity;
  json_data["pressure"] = pressure;
  serializeJson(json_data, buffer);
  
  Serial.println("");
  Serial.println(buffer);
  Serial.println("sending your message");
  if (!client.connected()) {
    reconnect();  
  }
  if (client.publish("sensor/nodemcubme", buffer, true) == true) {
    Serial.println("Success sending message1");
  } else {
    Serial.println("Error sending message1");
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived: ");
  Serial.println(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
}
bool WiFi_On() {  
  WiFi.forceSleepWake();
  WiFi.mode(WIFI_STA);
  wifi_station_connect();
  WiFi.begin(ssid, ss_pswd);
  
  while ((WiFi.status() != WL_CONNECTED) && (conn_tries++ < WIFI_RETRIES)) {
    delay(100);
  }
  if (WiFi.status() == WL_CONNECTED)
    return (true);
  else
    return (false);
}

bool WiFi_Off() {
  conn_tries = 0;
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();
  while ((WiFi.status() == WL_CONNECTED) && (conn_tries++ < WIFI_RETRIES)) {
    delay(100);
  }
  if (WiFi.status() != WL_CONNECTED)
    return (true);
  else
    return (false);
}

void setup() {  
  Serial.begin(115200);
  delay(200);
  bme.begin(0x76);
  delay(1000);
}

void loop() {
  temperature = bme.readTemperature();
  humidity = bme.readHumidity();
  pressure = bme.readPressure() / 100.0F;
  WiFi_On();
  delay(200);
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  sendMQTTMessage(temperature, humidity, pressure);
  delay(500);
  WiFi.disconnect(true); 
  delay(100);
  Serial.print("Sleeping");
  ESP.deepSleep(30 * 60 * e6, WAKE_RF_DEFAULT); // e6 is 1 second
}
