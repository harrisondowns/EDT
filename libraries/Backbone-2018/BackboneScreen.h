//
//  BackboneScreen.hpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/7/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#ifndef BackboneScreen_hpp
#define BackboneScreen_hpp

#include <stdio.h>
#include "Arduino.h"

class BackboneScreen {
public:
    typedef void (*DrawFunc)();
    typedef void (*RunFunc)(int delta); // the int arg is the delta
    typedef void (*InitFunc)();
    
    void init();
    void draw();
    void run(int delta);
    int pollForStateChange();

    
    BackboneScreen(InitFunc i, DrawFunc d, RunFunc r);
private:
    InitFunc initF;
    DrawFunc drawF;
    RunFunc runF;
    int shouldChangeState;
    bool initialized;
    void pushToState(int state);
    void popState(int rip);
    
};

#endif /* BackboneScreen_hpp */
