//
//  Clicker.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/8/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "Clicker.h"
#include "ClickerGlobals.h"
#include <graphics.h>
#include <KeyboardScreen.h>
#include <Networking.h>

void submitResponse(int selection) {
  String s;
  fillRect(70, 50, 210, 35, BLACK);
  yield();

  switch (selection) {
  case 0:
    s = "A";
    break;
  case 1:
    s = "B";
    break;
  case 2:
    s = "C";
    break;
  case 3:
    s = "D";
    break;
  }
  char *text = clickerServer(s);
  drawText(text, 72, 50, WHITE, 4);
}

void quitClicker(int screen) {
  clickerProgram->popState(screen);
}

void initClicker(){
}

void drawClicker(){
    fillScreen(PINK);
    drawText("Clicker", 70, 10, BLACK, 4);
    fillRect(70, 50, 210, 35, BLACK);
    int w = width();
    add_button(w / 2 - 20, //x
	       90, //y
	       40,//w
	       30,//h
	       0, //r
	       0, //screen
	       3, //textSize
	       "A", //text
	       BLACK, //textColor
	       PURPLE, //ScreenColor
	       submitResponse //changeScreen
	       );
    add_button(w / 2 - 20, //x
	       125, //y
	       40,//w
	       30,//h
	       0, //r
	       1, //screen
	       3, //textSize
	       "B", //text
	       BLACK, //textColor
	       PURPLE, //ScreenColor
	       submitResponse //changeScreen
	       );
    add_button(w / 2 - 20, //x
	       160, //y
	       40,//w
	       30,//h
	       0, //r
	       2, //screen
	       3, //textSize
	       "C", //text
	       BLACK, //textColor
	       PURPLE, //ScreenColor
	       submitResponse //changeScreen
	       );
    add_button(w / 2 - 20, //x
	       195, //y
	       40,//w
	       30,//h
	       0, //r
	       3, //screen
	       3, //textSize
	       "D", //text
	       BLACK, //textColor
	       PURPLE, //ScreenColor
	       submitResponse //changeScreen
	       );
    add_button(3, //x
	       3, //y
	       50,//w
	       19,//h
	       0, //r
	       0, //screen
	       2, //textSize
	       "back", //text
	       BLACK, //textColor
	       PINK, //ScreenColor
	       quitClicker //changeScreen
	       );
    draw_all_buttons();
}

void runClicker(int delta){
	
}

BackboneProgram* makeClicker(){
  BackboneProgram* clicker = new BackboneProgram(0);
  BackboneScreen* main = new BackboneScreen(initClicker, drawClicker, runClicker);
  clicker->addScreen(main);
  clickerProgram = clicker;
  
  return clicker;
}