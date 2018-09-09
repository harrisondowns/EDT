#ifndef NotepadGlobals_hpp
#define NotepadGlobals_hpp

#include "BackboneProgram.h"

#define NOTEPAD_HOME 0
#define NOTEPAD_DRAW 1

extern uint16_t colors[8];

extern BackboneProgram* notepadProgram;

extern int numNotes;

extern int pushNote;

#endif /* NotepadGlobals */