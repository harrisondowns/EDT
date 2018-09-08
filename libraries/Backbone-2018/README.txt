BACKBONE README 2018

Backbone is a lightweight Pseudo-OS meant to run on embedded arduino-enabled chips like the ESP32E.

It supports the implementation of multiple "programs," of which one can be running at
any given time. Programs can be in different states, called "screens," which allow for
the program to transition between major UI's (a main menu versus a game, for instance).

It also allows for programs to communicate with each other through a "mail" system that
stores files in Flash Memory. 

Files:
--Core.hpp/cpp - The Core of the program. Keeps track of all programs and transitions between them
as necessary.
--BackboneProgram.hpp/cpp - Class for declaring a program. Programs can have multiple states (called
"screens"), global variables, and can communicate with other programs through the mail service.
--BackboneScreen.hpp/cpp - Program states. Have three associated functions: "init" (called when pushed
to), "draw" (for UI stuff if desired), and "run" (business logic, should be called in a loop).
--Mail.hpp/cpp - Handles inter-program communication through the File system.

Dependencies: 
--Arduino Better Memory