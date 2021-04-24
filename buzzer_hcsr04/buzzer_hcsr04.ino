const int buzzPin = 8;
const int trigPin = 6;
const int echoPin = 5;

long duration, cm;

void setup(){
  Serial.begin (115200);
  pinMode(buzzPin, OUTPUT); // Initiate buzzer on GPIO 8
  pinMode(trigPin, OUTPUT); // Ultrasonic output on GPIO 6
  pinMode(echoPin, INPUT); // Ultrasonic echo on GPIO 5
}

void loop() {
  // Sends "HIGH" signal
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Calculate distance if echo is received
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  // Activate buzzer with frequency based on distance
  if (100 > cm) {
    analogWrite(buzzPin, 255);
    delay(50);
    analogWrite(buzzPin, 0);
    delay(cm*10);
  } else {
    analogWrite(buzzPin, 255);
    delay(50);
    analogWrite(buzzPin, 0);
    delay(1000);
  }
}
