//
//  FlashCards.cpp
//
//  Created by Harrison Downs on 7/8/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "FlashCards.h"
#include "FlashCardsGlobals.h"
#include <BackboneProgram.h>
#include "BackboneScreen.h"
#include <graphics.h>
#include <KeyboardScreen.h>

#define NEW_SET 1
#define KEYBOARD 2

char *title;
char *description;
boolean titleSet;
boolean descriptionSet;
boolean settingTitle;

void changeToScreen(int program) {
  flashCardsProgram->pushToState(program);
}

void initNewSet() {
	title = "    ";
	description = "    ";
	titleSet = false;
	descriptionSet = false;
	settingTitle = false;

}

void setTitle(int screen) {
	titleSet = true;
	settingTitle = true;
	changeToScreen(screen);
}

void setDescription(int screen) {
	descriptionSet = true;
	settingTitle = false;
	changeToScreen(screen);
}

void updataeText() {
	if(settingTitle) {
		title = get_val();
	}
	else {
		description = get_val();
	}
}

void drawNewSet() {
	updataeText();
	fillScreen(PURPLE);
	add_button(50, 10, 80, 60, 0, KEYBOARD, 2, "Title:", WHITE, BLACK, setTitle);
	if(titleSet) {
		drawText(title, 55, 87, WHITE, 3);
	}
	add_button(50, 110, 160, 60, 0, KEYBOARD, 2, "Description:", WHITE, BLACK, setDescription);
	if(descriptionSet){
		drawText(title, 55, 195, WHITE, 1);
	}



	draw_all_buttons();
}

void runNewSet(int delta) {

}

void initFlashCards() {

}

void drawFlashCards() {
	fillScreen(PURPLE);
	drawText("Flash Cards", 35, 10, WHITE, 4);

	add_button(50, 60, 250, 50, 0, NEW_SET, 2, "New Flash Card Set", WHITE, BLACK, changeToScreen);

	draw_all_buttons();


}

void runFlashCards(int delta) {

}

BackboneProgram* makeFlashCards() {
  BackboneProgram* flashCards = new BackboneProgram(0);
  BackboneScreen* main = new BackboneScreen(initFlashCards, drawFlashCards, runFlashCards);
  BackboneScreen* newSet = new BackboneScreen(initNewSet, drawNewSet, runNewSet);
  flashCards->addScreen(main);
  flashCards->addScreen(newSet);
  flashCards->addScreen(getKeyboard(0, flashCards));
  flashCardsProgram = flashCards;
  
  return flashCards;
}