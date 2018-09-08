//
//  BackboneScreen.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/7/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "BackboneScreen.h"

BackboneScreen::BackboneScreen(InitFunc i, DrawFunc d, RunFunc r){
    initF = i;
    drawF = d;
    runF = r;
    shouldChangeState = -2;
    initialized = false;
}

void BackboneScreen::init(){
    if (initialized == false){
        shouldChangeState = -2;
        initialized = true;
        initF();
    }
}

void BackboneScreen::draw(){
    shouldChangeState = -2;
    drawF();
}

void BackboneScreen::run(int delta){
    runF(delta);
}

int BackboneScreen::pollForStateChange(){
    return shouldChangeState;
}

void BackboneScreen::popState(int rip){
    shouldChangeState = -1;
}

void BackboneScreen::pushToState(int state){
    shouldChangeState = state;
}
