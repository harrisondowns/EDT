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
#include "graphics.h"
#include "Mail.h"


/*
int checkForMessage(byte progNum);
    
void readMail(byte progNum, char *buffer, int size);


void sendMailOut(char *mail, int32_t size);
*/
int counter = 0;
void initSpringboard(){

}

void changeProgram(int x){
    coreSB->switchToProgram(x);
}

void drawSpringboard(){
    fillScreen(LIGHTGREY);
    for (int i = 0; i < numPrograms; i++){
        add_button(20 + i * 70, 100, 60, 60, 2, i + 1, 2, programStrings[i], WHITE, BLACK, changeProgram);
    }
    draw_all_buttons();
    drawText("Home", 60, 10, BLACK, 8);
}

void drawSpringboard2(){
    fillScreen(RED);
    
}

void setCore(BackboneCore *c){
    coreSB = c;
}

void runSpringboard(int delta){
	
}

void runFakeboard(int delta){
    int mailSize = checkForMessage(1);
    
    if (mailSize > 0){
        Serial.println("GOT MAIL");
        char buffer[mailSize + 1];
        readMail(1, buffer, mailSize);
        buffer[mailSize] = 0;
        Serial.print("receivedMail: ");
        Serial.println(buffer);
    }
    char *a = (char*)malloc(6);
    a[0] = 'h';
    a[1] = 'u';
    a[2] = 'l';
    a[3] = 'l';
    a[4] = 'o';
    a[5] = 0;

    program->sendMailOut(a, 12);
   // program->pushToState(1);
}

void runSpringboard2(int delta){
	Serial.println("hello world2");
	program->popState(0);
}

BackboneProgram* makeSpringboard(){
    BackboneProgram* springboard = new BackboneProgram(0);
    BackboneScreen* main = new BackboneScreen(initSpringboard, drawSpringboard, runSpringboard);
    springboard->addScreen(main);

    program = springboard;

    return springboard;
}

BackboneProgram* makeSpringboard2(){
    BackboneProgram* springboard = new BackboneProgram(0);
    BackboneScreen* main = new BackboneScreen(initSpringboard, drawSpringboard2, runFakeboard);
    springboard->addScreen(main);

    BackboneScreen* second = new BackboneScreen(initSpringboard, drawSpringboard2, runSpringboard2);
    springboard->addScreen(second);

    program = springboard;

    return springboard;
}

