//
//  BackboneProgram.hpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/7/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#ifndef BackboneProgram_hpp
#define BackboneProgram_hpp

#include <stdio.h>
#include <vector>
//#include <Memory.h>
#include "Arduino.h"
#include "BackboneScreen.h"

using namespace std;

class BackboneProgram{
public:

    BackboneProgram(int defaultState);
    
    void initProgram();
    void addScreen(BackboneScreen *bs);
    void run(int delta);
    void pushToState(int state);
    void popState(int rip);

    void sendMailOut(char *mail, int32_t size);

    int32_t pollForMail();
    char* getMail();

    byte progNum = 0;
    
private:
    char *buffer;
    int32_t bufferSize;
    vector<BackboneScreen*> screens;
    vector<BackboneScreen*> stack;
    int OS_STATE;
    BackboneScreen* currentScreen;
    void checkForStateChange();
    
    // concept of a "buffer" - memory that the program can store on disk
    
};


#endif /* BackboneProgram_hpp */
