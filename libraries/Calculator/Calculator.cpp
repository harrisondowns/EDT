//
//  Springboard.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/8/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "Calculator.h"
#include "CalculatorGlobals.h"
#include "graphics.h"

#define MAIN_SCREEN 0
#define GRAPHING_SCREEN 1

void changeScreen(int program) {
  calcProgram->pushToState(program);
}

void initGrapher(){
}

void drawGrapher(){

}

void runGrapher(int delta){

}

void initCalculator(){

}

void drawCalculator(){
    fillScreen(ORANGE);
    add_button(10, 10, 60, 60, 0, GRAPHING_SCREEN, 6, "graph", GREEN, YELLOW, changeScreen);
    draw_all_buttons();
    drawText("Calculator", 70, 10, BLACK, 8);
}

void runCalculator(int delta){
	
}

BackboneProgram* makeCalculator(){
    BackboneProgram* calculator = new BackboneProgram(0);
    BackboneScreen* main = new BackboneScreen(initCalculator, drawCalculator, runCalculator);
    BackboneScreen* graph = new BackboneScreen(initGrapher, drawGrapher, runGrapher);
    calculator->addScreen(main);
    calculator->addScreen(main);
    calcProgram = calculator;

    return calculator;
}
