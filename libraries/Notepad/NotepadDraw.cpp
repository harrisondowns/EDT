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
#include "Mail.h"
#include "Arduino.h"
//#include "Mail.h"

void initNotepadDraw(){

}

uint16_t colors[8] = {WHITE, BLACK, DARKGREY, RED, BLUE, GREEN, ORANGE, PINK};

int buttSize = 28;

int conX = 10;
int conY = 45;

int currentColor = 0;

byte pixelBuffer[1600];


void swapColor(int x){
    if (x != currentColor){
        int currentColorX = currentColor % 2;
        int currentColorY = currentColor / 2;
        drawRect(currentColorX * buttSize + 1 + conX, currentColorY * buttSize + conY, buttSize + 1, buttSize + 1, WHITE);
        currentColor = x;
        currentColorX = currentColor % 2;
        currentColorY = currentColor / 2;
        drawRect(currentColorX * buttSize + 1 + conX, currentColorY * buttSize + conY, buttSize + 1, buttSize + 1, RED);
    }
}

void notepadPop(int x){
    notepadProgram->popState(0);
}
void notepadShare(int a){
    /*for (int i = 0; i < 1600; i++){
        Serial.print(pixelBuffer[i]);
        if (i % 40 == 0){
            Serial.println("|");
            yield();
        }
    }*/

    writeToFile("Notepad" + String(pushNote), String((char*)pixelBuffer));
    yield();
    char *message = (char*)malloc(6);
    message[0] = 'h';
    message[1] = 'u';
    message[2] = 'l';
    message[3] = 'l';
    message[4] = 'o';
    message[5] = 0;
    notepadProgram->sendMailOut(message, 6);
}

void drawNotepadDraw(){
    
    fillScreen(BLACK);
    if (fileExists("Notepad" + String(pushNote))){
        String read = readFile("Notepad" + String(pushNote));

        for (int y = 0; y < 40; y++){
            for (int x = 0; x < 40; x++){
               // Serial.print((byte)(read[y * 40 + x]));
                if ((byte)(read[0]) == 0){
                    pixelBuffer[40 * y + x] = 64; 
                }
                else{
                    pixelBuffer[40 * y + x] = read[y * 40 + x];
                }
            }
           // Serial.println("");
            yield();
        }
    
   
        for (int y = 0; y < 40; y++){
            for (int x = 0; x < 40; x++){
                fillRect(80 + (x * 6), 0 + (y * 6), 6, 6, colors[pixelBuffer[y * 40 + x] - 64]);
            }
            yield();
        }
    } else{
        for (int i = 0; i < 1600; i++){
            pixelBuffer[i] = 64;
        }
        fillRect(80, 0, 240, 240, WHITE);
    }
    

    

    drawLine(0 + conX, 0 + conY, 0 + conX, buttSize * 4 + conY, WHITE); // left line
    drawLine(buttSize * 2 + 1 + conX, 0 + conY, buttSize * 2 + 1 + conX, buttSize * 4 + conY, WHITE); // right line
    

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
    swapColor(1);

    int n = add_button(10, 2, buttSize * 2 + (buttSize / 2), buttSize, 2, 0, 2, "BACK", WHITE, BLUE, notepadPop);
    draw_button(n);

    n = add_button(10, 200, buttSize * 2 + (buttSize / 2), buttSize, 2, 0, 2, "SHARE", WHITE, BLUE, notepadShare);
    draw_button(n);

}


void runNotepadDraw(int delta){
	TS_Point pt = check_touch();
    if (pt.x != -1 && pt.y != -1){
        if (pt.x >= 80){
            int x = (pt.x / 6) * 6;
            int y = (pt.y / 6) * 6;
            int px = ((pt.x - 80) / 6);
            int py = (pt.y / 6);
            pixelBuffer[py * 40 + px] = currentColor + 64;
            fillRect(px * 6 + 80, py * 6, 6, 6, colors[currentColor]);
        }
    }
}