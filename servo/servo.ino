#include <Servo.h>
 
Servo myservo;
 
void setup()
{
  myservo.attach(2);
}
 
 
void loop()
{
  int pos;

  // Goes from 0° to 180° by 1°
  for (pos = 0; pos <= 180; pos += 1) {
    myservo.write(pos);
    // needs some delay because servo will not turn into position in zero time
    delay(20);
  }
  // Goes from 180° to 0° by 1°
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(20);
  }

  // Goes to 0°
  myservo.write(0);
  delay(2000);

  // Goes to 90°
  myservo.write(90);
  delay(2000);

  // Goes to 180°
  myservo.write(180);
  delay(2000);
}
