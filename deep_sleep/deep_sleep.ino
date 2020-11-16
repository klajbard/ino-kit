void setup() {
  Serial.begin(115200);
  while(!Serial) { }
}

void loop() {
  Serial.println("Deep sleep in 5 seconds...");
  ESP.deepSleep(5e6); // 5e6 is 5 seconds
}
