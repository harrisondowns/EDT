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
//#include "Mail.h"

void initNotepadHome(){
	Serial.println("Home reached");
}

void callNote(int id){
	pushNote = id;
	notepadProgram->pushToState(NOTEPAD_DRAW);
}

void drawNotepadHome(){
    fillScreen(LIGHTGREY);
    for (int i = 0; i < numNotes; i++){
        int n = add_button(20 + i * 70, 100, 60, 60, 2, i + 1, 2, "", WHITE, BLACK, callNote);
        draw_button(n);
    }
    drawText("Notes", 60, 10, BLACK, 8);
}

void runNotepadHome(int delta){
	
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