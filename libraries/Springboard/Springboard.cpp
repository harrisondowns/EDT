//
//  Springboard.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/8/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "Springboard.h"
#include "SpringboardGlobals.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"

// For the Adafruit shield, these are the default.
#define TFT_DC D1
#define TFT_CS D2

// Use hardware SPI (on Uno, #13, #12, #11) and the above for CS/DC
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

int counter = 0;
void initSpringboard(){
    tft.begin();
}

void drawSpringboard(){
  tft.fillScreen(ILI9341_BLACK);
  yield();
  tft.fillScreen(ILI9341_RED);
  yield();
  tft.fillScreen(ILI9341_GREEN);
  yield();
  tft.fillScreen(ILI9341_BLUE);
  yield();
  tft.fillScreen(ILI9341_BLACK);
  yield();
}

void runSpringboard(int delta){
	
	Serial.println("hello world");
	program->pushToState(1);
}

void runSpringboard2(int delta){
	Serial.println("hello world2");
	program->popState(0);
}

BackboneProgram* makeSpringboard(){
    BackboneProgram* springboard = new BackboneProgram(0);
    BackboneScreen* main = new BackboneScreen(initSpringboard, drawSpringboard, runSpringboard);
    springboard->addScreen(main);

    BackboneScreen* second = new BackboneScreen(initSpringboard, drawSpringboard, runSpringboard2);
    springboard->addScreen(second);

    program = springboard;

    return springboard;
}
