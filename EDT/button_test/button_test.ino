#include <graphics.h>
#include <Memory.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

void button_print(int);

void setup() {
  Serial.begin(9600);
 // Serial.println("Before");
  //delay(1000);
  //memInit();
 // delay(1000);
 // Serial.println("After");
  graphics_begin();
  Serial.println("ABOUT TO ADD");
  int size = add_button(50,50, 100, 100, 10, 1, 10, "BUTTON", WHITE, WHITE, button_print);
  Serial.println("BUTTON ADDED"); 
  Serial.print("Size: ");
  Serial.println(size);
  draw_button(0);
  Serial.println("BUTTON DRAWN");
  // put your setup code here, to run once:

}

void loop() {

  TS_Point point = check_touch();
  Serial.println(point.x);
  Serial.println(point.y);
  // put your main code here, to run repeatedly:

}

void button_print(int i) {
  (void) i;
  Serial.println("Pressed");
}
