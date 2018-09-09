//
//  BackboneProgram.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/7/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "BackboneProgram.h"
#include "Arduino.h"
#include "graphics.h"



BackboneProgram::BackboneProgram(int defaultState){
    OS_STATE = defaultState;
}

void BackboneProgram::initProgram(){
    currentScreen = screens[OS_STATE];
    pushToState(OS_STATE);
}

void BackboneProgram::run(int delta){
    currentScreen->run(delta);
    //checkForStateChange();
}

void BackboneProgram::addScreen(BackboneScreen *bs){
    screens.push_back(bs);
}

void BackboneProgram::checkForStateChange(){
    if (currentScreen->pollForStateChange() != NO_CHANGE){
        int change = currentScreen->pollForStateChange();
        if (change == POP_STATE){
            popState(0);
        }
        else if (change >= 0){
            pushToState(change);
        }
    }
}

void BackboneProgram::pushToState(int state){
    clear_buttons();
    stack.push_back(currentScreen);
    
    currentScreen = screens[state];

    currentScreen->init();
    currentScreen->draw();
}

void BackboneProgram::popState(int rip){
    clear_buttons();
    if (stack.size() > 1){
        currentScreen = stack.back();
        currentScreen->init();
        currentScreen->draw();
        stack.pop_back();
    }
    else{
        stack.pop_back();
        goToSpringboard = true;
    }
}

boolean validMail = false;

void BackboneProgram::sendMailOut(char *mail, int32_t size){
  Serial.println("sendMailOut");
  Serial.println(mail);
  Serial.println(size);
    if (bufferSize == 0){
        buffer = mail;
        bufferSize = size;
	validMail = true;
    }
    else{
        free(mail);
    }
}

int32_t BackboneProgram::pollForMail(){
  if (validMail) {
    return bufferSize;
  }
  return 0;
}

char* BackboneProgram::getMail(){
    bufferSize = 0;
    Serial.println("buffer is");
    Serial.println(buffer);
    validMail = false;
    return buffer;
}



