//
//  Springboard.cpp
//  Backbone-2018.Tests
//
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "Springboard.h"
#include "SpringboardGlobals.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "graphics.h"
#include "Mail.h"
#include <Networking.h>

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
    fillScreen(DARKGREY);
   // add_button(160, 10, 80, 80, 2, 1/*progNum*/, 2, "", WHITE, BLACK, changeProgram);
   // add_button(160, 140, 80, 80, 2, 2/*progNum*/, 2, "", WHITE, BLACK, changeProgram);
   // add_button(10, 90, 80, 80, 2, 3/*progNum*/, 2, "", WHITE, BLACK, changeProgram);
   // add_button(100, 90, 80, 80, 2, 4/*progNum*/, 2, "", WHITE, BLACK, changeProgram);*/

/*
    for (int x = 0; x < 2; x++){
        for (int y = 0; y < 2; y++) {
            add_button(50 + x * 100, 80 + 80 * y, 70, 70, 2, y * 2 + x + 1, 2, programStrings[y * 2 + x], WHITE, BLACK, changeProgram);
        }
    }*/

    drawText("EDT", 10, 10, WHITE, 8);

    for (int i = 0; i < numPrograms; i++){
        add_button(10 + i * 75, 100, 60, 60, 2, i + 1, 2, "", WHITE, BLACK, changeProgram);
        drawText(programStrings[i], 20 + i * 75, 170, WHITE, 1);
    }
    //draw_all_buttons();

    // division (calculator) icon
    fillRect(10, 100, 60, 60, CYAN);
    drawRect(10, 100, 60, 60, BLACK);
    
    fillRect(20, 125, 40, 10, BLUE);
    fillCircle(40, 115, 5, BLUE);
    fillCircle(40, 145, 5, BLUE);


    // Notepad icon
    fillRect(85, 100, 60, 60, PINK);
    drawRect(85, 100, 60, 60, BLACK);
    
    fillRect(100, 110, 33, 40, WHITE);

    for (int i = 0; i < 7; i++){
        drawLine(105, 115 + i * 5, 128, 115 + i * 5, BLACK);
    }

    // Flashcards icon
    fillRect(160, 100, 60, 60, GREENYELLOW);
    drawRect(160, 100, 60, 60, BLACK);

    fillRect(165, 110, 30, 15, WHITE);
    drawRect(165, 110, 30, 15, BLACK);

    fillRect(175, 120, 30, 15, WHITE);
    drawRect(175, 120, 30, 15, BLACK);

    fillRect(185, 130, 30, 15, WHITE);
    drawRect(185, 130, 30, 15, BLACK);

    // Clicker icon
    fillRect(235, 100, 60, 60, YELLOW);
    drawRect(235, 100, 60, 60, BLACK);

    drawText("A", 240, 105, BLACK, 3);
    drawText("B", 270, 105, BLACK, 3);
    drawText("C", 240, 130, BLACK, 3);
    drawText("D", 270, 130, BLACK, 3);

    yield();
    
    drawText((char *)getTime().c_str(), width() - 100, 3, BLACK, 3);
}

void drawSpringboard2(){
    fillScreen(RED);
    
}

void setCore(BackboneCore *c){
    coreSB = c;
}

void runSpringboard(int delta){
  if (delta % 10000 == 0) {
    char *s = (char *)getTime().c_str();
    if (s[0] != '0' && s[0] != '1') {
      return;
    }
    fillRect(width() - 100, 3, 100, 50, DARKGREY);
    drawText(s, width() - 100, 3, BLACK, 3);    
  }
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

