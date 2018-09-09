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
#include "Mail.h"

#define NEW_SET 1
#define KEYBOARD 2

char *title;
char *description;
int cardNumber;
boolean titleSet;
boolean descriptionSet;
boolean settingTitle;

void changeToScreen(int program) {
  flashCardsProgram->pushToState(program);
}

void initNewSet() {
	title = "    ";
	description = " ";
	cardNumber = 0;
	titleSet = false;
	descriptionSet = false;
	settingTitle = false;

}

void setTitle(int screen) {
	settingTitle = true;
	changeToScreen(screen);
}

void setDescription(int screen) {
	descriptionSet = true;
	settingTitle = false;
	changeToScreen(screen);
}

void updateText() {
	if(settingTitle) {
		titleSet = true;
		strcpy(title, get_val());
	}
	else {
		descriptionSet = true;
		strcpy(description, get_val());
	}
}

void saveAndChange(int rip) {
	//writeToFile("FlashCards" + String(cardNumber), strcat(title, description));
	title = "   ";
	description = " ";
	cardNumber++;
	titleSet = false;
	descriptionSet = false;
	settingTitle = false;
	fillRect(55, 78, 250, 20, PURPLE);
	fillRect(55, 180, 20, 200, PURPLE);
}

void drawNewSet() {
	updateText();
	fillScreen(PURPLE);
	add_button(50, 10, 80, 60, 0, KEYBOARD, 2, "Title:", WHITE, BLACK, setTitle);
	if(titleSet) {
		drawText(title, 55, 78, WHITE, 3);
	}
	//else {
	//	fillRect(55, 78, 250, 20, PURPLE);
	//}
	add_button(50, 110, 160, 60, 0, KEYBOARD, 2, "Description:", WHITE, BLACK, setDescription);
	if(descriptionSet){
		drawText(description, 55, 180, WHITE, 1);
	}
	//else {
	//	fillRect(55, 180, 20, 200, PURPLE);
	//}

	add_button(5, 180, 50, 50, 0, 0, 1, "Next", WHITE, BLACK, saveAndChange);

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