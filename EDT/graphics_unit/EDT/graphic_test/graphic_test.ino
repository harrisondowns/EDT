#include <graphics.h>

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  graphics_begin();
}

void loop() {
  Serial.println("Drawing");
  // put your main code here, to run repeatedly:
  fillRect(100,100,300,300,RED);
  delay(1000);
}
