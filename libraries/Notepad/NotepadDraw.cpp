//
//  Springboard.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/8/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "NotepadDraw.h"
#include "NotepadGlobals.h"
#include "graphics.h"
//#include "Mail.h"

void initNotepadDraw(){
    Serial.println("hullo");
}

uint16_t colors[8] = {WHITE, BLACK, DARKGREY, RED, BLUE, GREEN, ORANGE, PINK};

int buttSize = 28;

int conX = 10;
int conY = 45;

int currentColor = 0;

void swapColor(int x){
    Serial.print("currentColor is START ");
    Serial.println(currentColor);
    if (x != currentColor){
        Serial.print("currentColor is A ");
        Serial.println(currentColor);
        int currentColorX = currentColor % 2;
        int currentColorY = currentColor / 2;
        drawRect(currentColorX * buttSize + 1 + conX, currentColorY * buttSize + conY, buttSize + 1, buttSize + 1, WHITE);
        Serial.print("currentColor is B ");
        Serial.println(currentColor);
        currentColor = x;
        Serial.print("currentColor is C ");
        Serial.println(currentColor);
        currentColorX = currentColor % 2;
        currentColorY = currentColor / 2;
        drawRect(currentColorX * buttSize + 1 + conX, currentColorY * buttSize + conY, buttSize + 1, buttSize + 1, RED);
    }
}

void drawNotepadDraw(){
    
    fillScreen(BLACK);
    fillRect(80, 0, 240, 240, WHITE);

    

    drawLine(0 + conX, 0 + conY, 0 + conX, buttSize * 4 + conY, WHITE); // left line
    drawLine(buttSize * 2 + 1 + conX, 0 + conY, buttSize * 2 + 1 + conX, buttSize * 4 + conY, WHITE); // right line
    //drawLine(0, 0, buttSize * 2 + 1, buttSize * 8, WHITE);

    

    drawLine(0 + conX, 0 + conY, buttSize * 2 + 1 + conX, 0 + conY, WHITE); // top line



    drawLine(0 + conX, buttSize * 4 + 1 + conY, buttSize * 2 + 1 + conX, buttSize * 4 + 1 + conY, WHITE); // bottom line

    for (int y = 0; y < 4; y++){
        for (int x = 0; x < 2; x++){
            int counter = y * 2 + x;
            int n = add_button(1 + x * buttSize + conX, 1 + y * buttSize + conY, buttSize, buttSize, 2, counter, 2, "", colors[counter], colors[counter], swapColor);

            draw_button(n);
        }
        drawLine(0 + conX, y * buttSize + conY, buttSize * 2 + 1 + conX, y * buttSize + conY, WHITE);
    }
    drawLine(buttSize + 1 + conX, 0 + conY, buttSize + 1 + conX, buttSize * 4 + conY, WHITE); // middle line
    Serial.print("currentColor is Q ");
    Serial.println(currentColor);
    swapColor(1);

}



void runNotepadDraw(int delta){
	TS_Point pt = check_touch();
    if (pt.x != -1 && pt.y != -1){
        if (pt.x >= 80){
            int x = (pt.x / 8) * 8;
            int y = (pt.y / 8) * 8;
            fillRect(x, y, 8, 8, colors[currentColor]);
        }
    }
}