**EDT-2018 README**
Created for PennApps XVIII
Team Members: Harrison Downs, James Hopkins, Jason Iskenderian, and Elias Marcopoulos.

EDT is a low-cost tablet device made for seamless integration into the education space. The device is made using a NodeMCU 1.0 ESP8266 Wifi Chip, an ILI9341 2.8” LCD Touch Screen, and it is programmed using Arduino C++. It comes programmed with 4 apps as a proof of concept: a graphing calculator app, a note-sharing app, a flash-card/memory app, and a “clicker” (pop-quiz) app. The total cost of the hardware of is under ~$20 (source: Amazon).

Four Apps:
—Graphing Calculator - Lets the user do basic arithmetic operations, and graph linear equations.
—Notepad - Lets the user make colorful notes and share them with other tablet users.
—FlashCards - Lets the user make virtual flash cards and practice with them as a studying tool.
—Clicker - Let’s teachers do in class pop-quizzes where the students answer using their tablets.

Dependencies:
-XPT2046_Touchscreen
-Adafruit_GFX
-Adafruit_ILI9341
-Backbone-2018
-TaskScheduler
-PainlessMesh
-ArduinoJSON
-ESPAsyncTCP
-StandardCPlusPlus

NOTE: Our libraries folder contains a forked version of the open source Backbone-2018 library that we molded to fit the needs of this project. 90% of the code in libraries/Backbone-2018 was not written for this hackathon. The main things we had to modify it for was removing the use of the “Better Arduino Memory” library and allowing for our custom graphics library. As such, the code in libraries/Backbone-2018 should be ignored as most of it was not made for this hack in particular.

File structure:

EDT/ - Contains the Arduino IDE sketch that runs the program as well as a few test programs.
EDT/EDT.ino - The main sketch file. Responsible for launching all other parts of the program.
libraries/ - Contains all of our .h and cpp files
libraries/Backbone-2018 - Forked version of an open source psuedo-OS library for ESP8266s. See NOTE above.
libraries/Calculator - Contains the code for the graphing calculator program.
libraries/Clicker - Contains the code for the clicker app. Allows teachers to hold in-class quizzes where students use their tablet device to answer.
libraries/FlashCards - Contains the code for the FlashCards app. Lets students make decks of virtual flash cards and use them for studying.
libraries/graphics - Contains our graphics library code that wraps the Adafruit_ILI9341 library functions to allow for easy rendering.
libraries/Networking - Contains the networking library code used to transmit data between tablets.
libraries/Notepad - Contains the code for the Notepad app. Lets students draw/write colorful notes and then share them with a teacher, and lets teachers share notes with students.
libraries/Springboard - The “Home Screen” program that lets the user launch all other apps.
serverFiles/ - Contains all the files that run the backend web server that lets the tablets talk to each other.


