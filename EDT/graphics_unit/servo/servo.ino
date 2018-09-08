#include <Servo.h>

Servo s1;
int pin = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
  s1.attach(pin);
  Serial.begin(9600);


}

void loop() {
  Serial.print(s1.read());
  s1.write(10);
  delay(500);
  s1.write(89);
  delay(1500);

  // put your main code here, to run repeatedly:

}
