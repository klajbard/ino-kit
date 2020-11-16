void setup() {
  Serial.begin(9600);
}

float light;

void loop() {
  light = analogRead(A0);
  Serial.println(light);
  delay(2000);
}