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

#define MAIN 0
#define NEW_SET 1
#define KEYBOARD 2
#define QUIZ 3

const int MAX_CARDS = 10;
char **title = (char **) malloc(sizeof (char *) * MAX_CARDS);
char **description = (char **) malloc(sizeof(char*) * MAX_CARDS);
int cardNumber;
boolean titleSet;
boolean descriptionSet;
boolean settingTitle;

boolean titleUp;
int cardIterator;

void clear_text() {
        drawText(title[cardNumber], 55, 78, PURPLE, 3);
        drawText(description[cardNumber], 55, 180, PURPLE, 2);
}

void changeToScreen(int program) {
  flashCardsProgram->pushToState(program);
}

void initNewSet() {
	title[cardNumber] = new char[18];
	description[cardNumber] = new char[18];
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
		strcpy(title[cardNumber], get_val());

	}
	else {
		descriptionSet = true;
		strcpy(description[cardNumber], get_val());
	}
}

void saveAndChange(int rip) {
	Serial.println("-----");
	Serial.println(cardNumber);
	Serial.println("~~~~~");
	if (titleSet and descriptionSet) {
               clear_text();
               cardNumber++;
	       title[cardNumber] = new char[18];
	       description[cardNumber] = new char[18];
	       titleSet = false;
	       descriptionSet = false;
	       settingTitle = false;
    }
}

void popBack(int screen) {
	if(titleSet and descriptionSet) {
		cardNumber++;
		title[cardNumber] = new char[18];
	    description[cardNumber] = new char[18];
		titleSet = false;
		descriptionSet = false;
		settingTitle = false;
	}
	flashCardsProgram->popState(screen);
}

void drawNewSet() {
	updateText();
	fillScreen(PURPLE);
	add_button(25, 10, 80, 60, 0, KEYBOARD, 2, "Title:", WHITE, BLACK, setTitle);
	if(titleSet) {
		drawText(title[cardNumber], 55, 78, WHITE, 3);
	}
	add_button(25, 110, 150, 60, 0, KEYBOARD, 2, "Description:", WHITE, BLACK, setDescription);
	if(descriptionSet){
		drawText(description[cardNumber], 55, 180, WHITE, 2);
	}

	add_button(210, 10, 100, 50, 0, 0, 2, "Next", WHITE, BLACK, saveAndChange);
	add_button(210, 110, 100, 50, 0, MAIN, 2, "Done", WHITE, BLACK, popBack);

	draw_all_buttons();
}

void runNewSet(int delta) {

}

void initFlashCards() {

}

void exitProgram(int rip) {
	flashCardsProgram->popState(rip);
}

void drawFlashCards() {
	fillScreen(PURPLE);
	drawText("Flash Cards", 35, 10, WHITE, 4);

	add_button(50, 60, 250, 50, 0, NEW_SET, 2, "New Flash Card Set", WHITE, BLACK, changeToScreen);

	add_button(50, 140, 150, 50, 0, QUIZ, 3, "QUIZ!", WHITE, BLACK, changeToScreen);

	add_button(225, 140, 75, 50, 0, 0, 2, "Back", PURPLE, WHITE, exitProgram);

	draw_all_buttons();


}

void runFlashCards(int delta) {

}

void initQuiz() {
	titleUp = true;
	cardIterator = 0;
}

void flipCard(int rip) {
	if(titleUp) {
		titleUp = false;
		drawText(title[cardIterator], 90, 105, BLACK, 4);
		drawText(description[cardIterator], 90, 105, WHITE, 3);
	}
	else {
		titleUp = true;
		drawText(description[cardIterator], 90, 105, BLACK, 3);
		drawText(title[cardIterator], 90, 105, WHITE, 4);
	}

}

void nextCard(int rip) {
	if(titleUp) {
		drawText(title[cardIterator], 90, 105, BLACK, 4);
	}
	else {
		drawText(description[cardIterator], 90, 105, BLACK, 3);
	}
	if(cardIterator < cardNumber - 1){
		cardIterator++;
	}
	titleUp = true;
	drawText(title[cardIterator], 90, 105, WHITE, 4);
	
}

void prevCard(int rip) {
	if(titleUp) {
		drawText(title[cardIterator], 90, 105, BLACK, 4);
	}
	else {
		drawText(description[cardIterator], 90, 105, BLACK, 3);
	}
	if(cardIterator > 0){
		cardIterator--;
	}
	titleUp = true;
	drawText(title[cardIterator], 90, 105, WHITE, 4);
}

void popOutOfQuiz(int screen) {
	flashCardsProgram->popState(screen);
}

void drawQuiz() {
	fillScreen(BLACK);
	
	add_button(90, 105, 150, 100, 0, 0, 4, "", WHITE, BLACK, flipCard);
	add_button(width() - 100, height() - 50, 50, 50, 0, 0, 3, "->", WHITE, BLACK, nextCard);
	add_button(0, height() - 50, 100, 50, 0, 0, 3, "<-", WHITE, BLACK, prevCard);
	add_button(0, 0, 75, 50, 0, MAIN, 2, "Back", BLACK, PINK, popOutOfQuiz);

	draw_all_buttons();
	drawText(title[0], 90, 105, WHITE, 4);

}

void runQuiz(int delta) {

}

BackboneProgram* makeFlashCards() {
  BackboneProgram* flashCards = new BackboneProgram(0);
  BackboneScreen* main = new BackboneScreen(initFlashCards, drawFlashCards, runFlashCards);
  BackboneScreen* newSet = new BackboneScreen(initNewSet, drawNewSet, runNewSet);
  BackboneScreen* quiz = new BackboneScreen(initQuiz, drawQuiz, runQuiz);
  flashCards->addScreen(main);
  flashCards->addScreen(newSet);
  flashCards->addScreen(getKeyboard(0, flashCards));
  flashCards->addScreen(quiz);
  flashCardsProgram = flashCards;

  return flashCards;
}