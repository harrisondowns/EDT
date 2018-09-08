//
//  Core.cpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/7/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#include "Core.h"
#include "Arduino.h"
#include "Mail.h"
#include "graphics.h"


BackboneCore::BackboneCore(){
    programHeapSize = 0;
}

void BackboneCore::initBackbone(){
    switchToProgram(0);
}

void BackboneCore::runBackbone(int delta){
    check_touch();
    currentProgram->run(delta);
    checkForProgramMail();
}

void BackboneCore::checkForProgramMail(){
    if (currentProgram->pollForMail() > 0){
        int32_t size = currentProgram->pollForMail();
        sendMail(currentProgram->getMail(), size);
    }
}

int BackboneCore::addProgram(BackboneProgram* bp){
    programs.push_back(bp);
    return (int)programs.size() - 1;
}

void BackboneCore::switchToProgram(int id){
    currentProgram = programs[id];
    currentProgram->initProgram();
}

void BackboneCore::receivedMail(String message){
    newMessage(message);
}

void BackboneCore::sendMail(char *message, int32_t size){
    if (outgoingMail.size() < 100){
        outgoingMail.push_back(message);
        outgoingMailSize.push_back(size);
    }
    else{
        free(message);
    }
}

bool BackboneCore::hasMail(){
    return outgoingMail.size() > 0;
}

String BackboneCore::getMail(){
    char *m = outgoingMail.back();
    Serial.println(m);
    int32_t size = outgoingMailSize.back();
    outgoingMail.pop_back();
    outgoingMailSize.pop_back();
    String s = String(m);
    free(m);
    Serial.print("S after free is ");
    Serial.println(s);
    return s;
}



