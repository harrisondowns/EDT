//
//  Calculator.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/8/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "Calculator.h"
#include "CalculatorGlobals.h"
#include <graphics.h>
#include <KeyboardScreen.h>

#define MAIN_SCREEN 0
#define GRAPHER_SCREEN 1
#define GRAPH_SCREEN 2
#define KEYBOARD 3

double slope;
double intercept;
boolean slopeSet;
boolean interceptSet;
boolean settingSlope;

void changeScreen(int screen) {
  calcProgram->pushToState(screen);
}

void popScreen(int screen) {
  calcProgram->popState(screen);
}

void setSlope(int screen) {
  settingSlope = true;
  changeScreen(screen);
}

void setIntercept(int screen) {
  settingSlope = false;
  changeScreen(screen);
}

void checkParams() {
  if (check_flag()) {
    char *num = get_val();
    int offset = 1;
    if (settingSlope) {
      slopeSet = true;
      slope = atoi(num);
    } else {
      interceptSet = true;
      intercept = atoi(num);
    }
  }

}

void initGrapher(){
}

void drawGrapher(){
  checkParams();
  fillScreen(WHITE);
  int h = height();
  int w = width();
  drawText("Slope:",  w / 4, h / 4, BLACK, 3);
  drawText("Intercept:", w / 4, h / 2, BLACK, 3);
  // graph it button
  add_button(w / 4, //x
	     h * 3 / 4, //y
	     175,//w
	     35, //h
	     0, //r
	     GRAPH_SCREEN, //screen
	     3, //textSize
	     "graph it!", //text
	     BLACK, //textColor
	     BLUE, //ScreenColor
	     changeScreen ); //changeScreen
  char *text = "__            \0";
  // slope button
  if (slopeSet) {
    itoa(slope, text, 10);
  }
  add_button(w * 3 / 4 + 10, //x
	     h / 4, //y
	     40,//w
	     15,//h
	     0, //r
	     KEYBOARD, //screen
	     2, //textSize
	     text, //text
	     BLACK, //textColor
	     LIGHTGREY, //ScreenColor
	     setSlope //changeScreen
	     );
  // intercept button
  text = "__               \0";
  if (interceptSet) {
    text = itoa(intercept, text, 10);
  }
  add_button(w * 3 / 4 + 10, //x
	     h / 2, //y
	     40,//w
	     15,//h
	     0, //r
	     KEYBOARD, //screen
	     2, //textSize
	     text, //text
	     BLACK, //textColor
	     LIGHTGREY, //ScreenColor
	     setIntercept //changeScreen
	     );
  add_button(3, //x
	     3, //y
	     50,//w
	     19,//h
	     0, //r
	     GRAPHER_SCREEN, //screen
	     2, //textSize
	     "back", //text
	     BLACK, //textColor
	     PINK, //ScreenColor
	     popScreen //changeScreen
	     );
  draw_all_buttons();
}

void runGrapher(int delta){
}

void initGraph(){
  
}

void drawGraph(){
  fillScreen(WHITE);
  // go back button
  add_button(3, //x
	     3, //y
	     50,//w
	     19,//h
	     0, //r
	     GRAPHER_SCREEN, //screen
	     2, //textSize
	     "back", //text
	     BLACK, //textColor
	     PINK, //ScreenColor
	     popScreen //changeScreen
	     );
  if (slopeSet and interceptSet) {
    int h = height();
    int w = width();
    double xmax;
    double ymax;
    double xmin;
    double ymin;
    double numTicks = 10;
    double maxMax = numTicks / 2;
    // vertical axis
    drawLine(w / 2, 0, w / 2, h, BLACK);
    // horizontal axis
    drawLine(0, h / 2, w, h / 2, BLACK);
    // vertical ticks
    for (int i = 0; i < h; i = i + h / numTicks) {
      drawLine(w / 2 - 4, i, w / 2 + 4, i, BLACK);
    }
    // horizontal ticks
    for (int i = 0; i < w; i = i + w / numTicks) {
      drawLine(i, h / 2 - 4, i, h / 2 + 4, BLACK);
    }
    // the line:
    
      //y = mx + b => if y is 5 then
      //             (5 - b) / m = x
    xmax = (maxMax - intercept) / slope;
    Serial.println("max b m x");
    Serial.println(maxMax);
    Serial.println(intercept);
    Serial.println(slope);
    Serial.println(xmax);
    if (xmax > maxMax) {
      // y = mx + b => if x is 5 then
      //               y = m * 5 + b
      ymax = maxMax * slope + intercept;
      xmax = maxMax;
    } else {
      ymax = maxMax;
    }
      // repeat logic with -maxMax
    xmin = (-maxMax - intercept) / slope;
    if (xmin < -maxMax) {
      ymin = -maxMax * slope + intercept;
      xmin = -maxMax;
    } else {
      ymin = -maxMax;
    }

      // scale it: divide by maxMax, multiply by w / 2, h / 2 (for x, y), and that nmis the shift from the screen center
    int x1 = (xmax / maxMax) * (w / 2) + w / 2;
    int y1 = -(ymax / maxMax) * (h / 2) + h / 2;
    int x2 = (xmin / maxMax) * (w / 2) + w / 2;
    int y2 = -(ymin / maxMax) * (h / 2) + h / 2;

    Serial.println("printing x1 y1 x2 y2");
    Serial.println(x1);
    Serial.println(y1);
    Serial.println(x2);
    Serial.println(y2);
    
    drawLine(x2, y2, x1, y1, RED);
    
  } else {
    drawText("Please set       both slope       and intercept", 3, 40, RED, 3);
  }
  draw_all_buttons();
}

void runGraph(int delta){

}

void initCalculator(){

}

void drawCalculator(){
    fillScreen(ORANGE);
    add_button(10, 10, 60, 60, 0, GRAPHER_SCREEN, 6, "graph", GREEN, YELLOW, changeScreen);
    draw_all_buttons();
    drawText("Calculator", 70, 10, BLACK, 8);
}

void runCalculator(int delta){
	
}

BackboneProgram* makeCalculator(){
  BackboneProgram* calculator = new BackboneProgram(0);
  BackboneScreen* main = new BackboneScreen(initCalculator, drawCalculator, runCalculator);
  BackboneScreen* graphHome = new BackboneScreen(initGrapher, drawGrapher, runGrapher);
  BackboneScreen* graph = new BackboneScreen(initGraph, drawGraph, runGraph);
  calculator->addScreen(main);
  calculator->addScreen(graphHome);
  calculator->addScreen(graph);
  calculator->addScreen(getKeyboard(1, calculator));
  calcProgram = calculator;
  
  return calculator;
}
