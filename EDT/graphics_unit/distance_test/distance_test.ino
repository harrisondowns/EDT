#include <NewPing.h>
#include <Servo.h>
#include "Constants.h"

int measurement;
int median_cm;


void setup() {
 
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.print( front_sensor.ping_cm());
Serial.print("   ");
Serial.print(front_left_sensor.ping_cm());
Serial.print("   ");
Serial.print(back_left_sensor.ping_cm());
Serial.print("   ");
Serial.print(front_right_sensor.ping_cm());
Serial.print("   ");
Serial.print(back_right_sensor.ping_cm());
Serial.print("   ");
Serial.println(back_sensor.ping_cm());
delay(1000);
}
