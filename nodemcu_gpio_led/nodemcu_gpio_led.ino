void setup() {
  Serial.begin(115200);              // set up serial communication
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}
void loop() {                        // run continuously
  Serial.println("Hello!");          // prints to serial
  delay(2000);                       // wait 2 seconds
  Serial.println("How are you?");    // prints to serial
  delay(2000);                       // wait 2 seconds
  Serial.println("I'm under the program.");  // prints to serial
  delay(10000);                      // wait 10 seconds
}
