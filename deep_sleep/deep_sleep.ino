void setup() {
  Serial.begin(115200);
  while(!Serial) { }

  // To allow wake up on button press uncomment the following lines
  // Serial.println("I'm awake, but I'm going into deep sleep mode until RESET pin is connected to a LOW signal");
  // ESP.deepSleep(0);
}

void loop() {
  Serial.println("Deep sleep in 5 seconds...");
  ESP.deepSleep(5e6); // 5e6 is 5 seconds
}
