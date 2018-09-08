//Jason - KeyboardScreen.h
//WHERE ARE THE KEYBOARDS

#ifndef KeyboardScreen_h
#define KeyboardScreen_h

#include <BackboneScreen.h>
#include <BackboneProgram.h>

BackboneScreen *getKeyboard(int, BackboneProgram *);
void numDraw();
void KeyboardRun(int);
boolean check_flag();
char *get_val();

#endif
