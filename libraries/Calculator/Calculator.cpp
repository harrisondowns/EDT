//
//  Springboard.cpp
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

int slope;
int intercept;

void changeScreen(int program) {
  calcProgram->pushToState(program);
}

void initGrapher(){
}

void drawGrapher(){
  fillScreen(WHITE);
  int h = height();
  int w = width();
  drawText("Slope:",  w / 4, h / 4, BLACK, 3);
  drawText("Intercept:", w / 4, h / 2, BLACK, 3);
  // graph it button
  add_button(w / 2, //x
	     h * 3 / 4, //y
	     40,//w
	     15,//h
	     0, //r
	     GRAPH_SCREEN, //screen
	     3, //textSize
	     "graph it!", //text
	     BLACK, //textColor
	     LIGHTGREY, //ScreenColor
	     changeScreen ); //changeScreen
  // slope button
  add_button(w * 3 / 4, //x
	     h / 4, //y
	     40,//w
	     15,//h
	     0, //r
	     KEYBOARD, //screen
	     3, //textSize
	     "__", //text
	     BLACK, //textColor
	     LIGHTGREY, //ScreenColor
	     changeScreen //changeScreen
	     );
  // intercept button
  add_button(w * 3 / 4, //x
	     h / 2, //y
	     40,//w
	     15,//h
	     0, //r
	     KEYBOARD, //screen
	     3, //textSize
	     "__", //text
	     BLACK, //textColor
	     LIGHTGREY, //ScreenColor
	     changeScreen //changeScreen
	     );
}

void runGrapher(int delta){

}

void initGraph(){
  
}

void drawGraph(){
  fillScreen(WHITE);
  // go back button
  add_button(20, //x
	     30, //y
	     40,//w
	     15,//h
	     0, //r
	     GRAPHER_SCREEN, //screen
	     3, //textSize
	     "go back!", //text
	     BLACK, //textColor
	     LIGHTGREY, //ScreenColor
	     changeScreen //changeScreen
	     );
	     
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
  Serial.println("hi");
  BackboneProgram* calculator = new BackboneProgram(0);
  Serial.println("by");
  BackboneScreen* main = new BackboneScreen(initCalculator, drawCalculator, runCalculator);
  Serial.println("yo");
  BackboneScreen* graphHome = new BackboneScreen(initGrapher, drawGrapher, runGrapher);
  Serial.println("dsf");
  BackboneScreen* graph = new BackboneScreen(initGraph, drawGraph, runGraph);
  Serial.println("yike");
  calculator->addScreen(main);
  Serial.println("ni");
  calculator->addScreen(graphHome);
  Serial.println("sdf");
  calculator->addScreen(graph);
  Serial.println("done");
  //    calculator->addScreen(getKeyboard(1));
  calcProgram = calculator;
  
  return calculator;
}
