#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "WIFI_SSID"; 
const char* password = "WIFI_PWD";
const char* host = "http://192.168.1.27";
String port = ":8123"; 
String path = "/api/services/switch/turn_on";
String auth = "HASSIO_AUTH_TOKEN";

const int RECV_PIN = 4; 
IRrecv irrecv(RECV_PIN); 
decode_results results;

unsigned long interval = 5000;
unsigned long previousMillis = millis();

void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1000);
  while (!Serial) { }
  irrecv.enableIRIn();
}

void connect_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void post_data(char* buffer) {
  WiFiClient client;
  if (!client.connect(host, 8123)) {
    Serial.println("Failed to connect host");
  }
  String address = host + port + path;
  HTTPClient http;
  http.begin(address);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + auth);
  int httpCode = http.POST(buffer);
  Serial.println(httpCode);
  String payload = http.getString();
  Serial.println(payload)
  http.end();
}


void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
    Serial.println("Going to sleep");
    delay(100);
    ESP.deepSleep(0);
  }

  if (irrecv.decode(&results)) {
    serialPrintUint64(results.value, HEX);
    char codes[] = {0xE0E06798, 0x96693CCD, 0x79BDAFF6};
    if (std::find(std::begin(codes), std::end(codes), results.value) != std::end(codes)) {
      // Create JSON
      char json[] = "{\"entity_id\":\"switch.smart_plug\"}";
      post_data(json); // Post data to Home Assistant
      connect_wifi();
    }
    delay(100);
    Serial.println("");
    irrecv.resume();
  }
}
