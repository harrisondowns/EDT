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
//#include <BackboneProgram.h>

#define GRAPHING_PROGRAM 1

void changeScreen(int program) {
  calcProgram->pushToState(program);
}

void initCalculator(){

}

void drawCalculator(){
    fillScreen(ORANGE);
    add_button(10, 10, 60, 60, 0, GRAPHING_PROGRAM, 6, "graph", GREEN, YELLOW, changeScreen);
    draw_all_buttons();
    drawText("Calculator", 70, 10, BLACK, 8);
}

void runCalculator(int delta){
	
}

BackboneProgram* makeCalculator(){
    BackboneProgram* calculator = new BackboneProgram(0);
    BackboneScreen* main = new BackboneScreen(initCalculator, drawCalculator, runCalculator);
    calculator->addScreen(main);

    calcProgram = calculator;

    return calculator;
}
