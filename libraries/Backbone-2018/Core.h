//
//  Core.hpp
//  Backbone-2018.Tests
//
//  Created by Harrison Downs on 7/7/18.
//  Copyright © 2018 Harrison Downs. All rights reserved.
//

#ifndef Core_hpp
#define Core_hpp

#include <stdio.h>
#include "BackboneProgram.h"
#include <vector>

using namespace std;

class BackboneCore {
public:
    BackboneCore();
	void initBackbone();
	void runBackbone(int delta);

	int addProgram(BackboneProgram* bp);
	void switchToProgram(int id);

	void receivedMail(String message);
	
	// outgoing functions
	void sendMail(char *message, int size);
	bool hasMail();
	String getMail();
private:
	vector<BackboneProgram*> programs;
	vector<char*> outgoingMail;
	vector<int> outgoingMailSize;
    int programHeapSize;
    BackboneProgram* currentProgram;
    void checkForProgramMail();
};



#endif /* Core_hpp */

