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

void quitClicker(int screen) {
  clickerProgram->popState(screen);
}

void initClicker(){
}

void drawClicker(){
    fillScreen(PINK);
    drawText("Clicker", 70, 10, BLACK, 4);
    fillRect(70, 50, 180, 35, BLACK);
    int w = width();
    add_button(w / 2 - 20, //x
	       90, //y
	       40,//w
	       25,//h
	       0, //r
	       0, //screen
	       3, //textSize
	       "back", //text
	       BLACK, //textColor
	       PINK, //ScreenColor
	       quitClicker //changeScreen
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
