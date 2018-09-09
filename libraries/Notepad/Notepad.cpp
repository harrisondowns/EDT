//
//  Springboard.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/8/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "Notepad.h"
#include "NotepadGlobals.h"
#include "graphics.h"
#include "NotepadDraw.h"
#include "Mail.h"
//#include "Mail.h"

void initNotepadHome(){
	Serial.println("Home reached");
	if (fileExists("NotepadCount")){
		numNotes = readFile("NotepadCount").toInt();
	}
	else{
		writeToFile("NotepadCount", "1");
		numNotes = 1;
	}
}

void callNote(int id){
	pushNote = id;
	if (pushNote == numNotes){
		numNotes++;
		writeToFile("NotepadCount", String(numNotes));
	}
	notepadProgram->pushToState(NOTEPAD_DRAW);
}

void popToSb(int rip){
	notepadProgram->popState(rip);
}

void drawNotepadHome(){
    fillScreen(LIGHTGREY);

    drawText("Notes", 60, 10, BLACK, 8);

    int n = add_button(10, 10, 40, 40, 2, 0, 1, "BACK", WHITE, BLACK, popToSb);
    draw_button(n);

    for (int i = 0; i < numNotes; i++){
    	int defX = 10 + (i % 6) * 50;
    	int defY = 100 + (i / 6) * 70;
        n = add_button(defX, defY, 40, 40, 2, i + 1, 2, "", WHITE, BLACK, callNote);
        draw_button(n);
        if (numNotes != i + 1){
        	String r = readFile("Notepad" + String(i + 1));
        	for (int y = 0; y < 40; y++){
        		for (int x = 0; x < 40; x++){
        			fillRect(defX + x, defY + y, 1, 1, colors[r[y * 40 + x] - 64]);
        		}
    		}
    	}
    }
    
}

void runNotepadHome(int delta){
	int mailSize = checkForMessage(2);
    
    if (mailSize > 0){
        Serial.println("GOT MAIL");
        char buffer[mailSize + 1];
        readMail(1, buffer, mailSize);
        buffer[mailSize] = 0;
        Serial.print("receivedMail: ");
        Serial.println(buffer);
    }
}


BackboneProgram* makeNotepad(){
    BackboneProgram* notepad = new BackboneProgram(0);
    BackboneScreen* main = new BackboneScreen(initNotepadHome, drawNotepadHome, runNotepadHome);
    notepad->addScreen(main);

    BackboneScreen* draw = new BackboneScreen(initNotepadDraw, drawNotepadDraw, runNotepadDraw);
    notepad->addScreen(draw);

    notepadProgram = notepad;

    return notepad;
}