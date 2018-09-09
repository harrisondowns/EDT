//
//  Springboard.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/8/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "NotepadDraw.h"
#include "NotepadGlobals.h"
#include "Mail.h"
#include "Arduino.h"
#include "Networking.h"
//#include "Mail.h"

void initNotepadDraw(){

}

int shareButtonID = 0;

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
    writeToFile("Notepad" + String(pushNote), String((char*)pixelBuffer));
    yield();
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


    byte currentColor = pixelBuffer[0];
    byte currentCount = 1;

    uint16_t totalBytes = 2;

    for (int i = 1; i < 1600; i++){
        if (pixelBuffer[i] != currentColor || currentCount > 255){
            totalBytes += 2;
            currentCount = 1;
            currentColor = pixelBuffer[i];
        } else{
            currentCount++;
        }
    }
    Serial.print("meh compression is bytes = ");
    Serial.println(totalBytes);
    yield();
   /* for (int i = 0; i < 1600; i++){
       // Serial.print(pixelBuffer[i]);
        if (i % 40 == 0){
           // Serial.println("|");
            yield();
        }
    }*/

/*
    char compressed[totalBytes + 1];

    currentColor = pixelBuffer[0];
    currentCount = 1;

    totalBytes = 2;

    for (int i = 1; i < 1600; i++){
        if (pixelBuffer[i] != currentColor || currentCount > 255){
            compressed[totalBytes] = currentColor + 1;
            compressed[totalBytes + 1] = currentCount;
            totalBytes += 2;

            currentCount = 1;
            currentColor = pixelBuffer[i];
        } else{
            currentCount++;
        }
    }

    
    compressed[totalBytes] = 0;

    Serial.print("COMPRESSED IS : ");
    Serial.println(compressed);*/

    Serial.println("POSTING TO STUDENT");
    //setup_wifi();
    postToStudent(String((char*)pixelBuffer));
    Serial.println("DONE POSTING TO STUDENT");

    fillRect(11, 171, buttSize * 2 + buttSize / 2 - 1, buttSize * 2 - 1, BLUE);
    drawLine(30, 200, 40, 210, WHITE); //checkMark
    drawLine(40, 210, 60, 180, WHITE);
    //10, 170, buttSize * 2 + (buttSize / 2), buttSize * 2


 /*   int sizeMessage = 800;
    char *message = (char*)malloc(sizeMessage);
    message[0] = 'h';
    message[1] = 'u';
    message[2] = 'l';
    message[3] = 'l';
    message[4] = 'o';
    for (int i = 5; i < sizeMessage - 1; i++){
        message[i] = 'o';
    }
    message[sizeMessage - 1] = 0;
    notepadProgram->sendMailOut(message, sizeMessage);*/
}



void drawNotepadDraw(){
    
    fillScreen(BLACK);
    if (fileExists("Notepad" + String(pushNote))){
        String read = readFile("Notepad" + String(pushNote));

        for (int y = 0; y < 40; y++){
            for (int x = 0; x < 40; x++){
               // Serial.print((byte)(read[y * 40 + x]));
                if ((byte)(read[0]) == 0){
                    Serial.println("got a 0");
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

    shareButtonID = add_button(10, 170, buttSize * 2 + (buttSize / 2), buttSize * 2, 2, 0, 2, "SHARE", WHITE, BLUE, notepadShare);
    draw_button(shareButtonID);

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