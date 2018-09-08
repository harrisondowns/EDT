
/*
 ESP8266 Blink by Simon Peter
 Blink the blue LED on the ESP-01 module
 This example code is in the public domain
 
 The blue LED on the ESP-01 module is connected to GPIO1 
 (which is also the TXD pin; so we cannot use Serial.print() at the same time)
 
 Note that this sketch uses BUILTIN_LED to find the pin with the internal LED
*/

#include <Core.h>
#include <Springboard.h>
#include <painlessMesh.h>
#include <FS.h>
#include <graphics.h>
#include <Calculator.h>

Scheduler userScheduler;
BackboneCore *core = new BackboneCore();
painlessMesh network;
int lastTime = 0;
void sendMessage();
void runBackboneCall();
Task taskSendMessage(TASK_SECOND * 1, TASK_FOREVER, &sendMessage);
Task runBackbone(TASK_SECOND * 0, TASK_FOREVER, &runBackboneCall);

void setup() {
  SPIFFS.begin();
  graphics_begin();
  setCore(core);
  network.init("ESP MESH", "notwiththatattitude", 5555);
  network.onReceive (&receivedCallback);
  network.onNewConnection (&newConnectionCallback);
  Serial.begin(9600); 
  
  core->addProgram(makeSpringboard());
  core->addProgram(makeCalculator());
  core->addProgram(makeSpringboard2());
  core->initBackbone();

  userScheduler.addTask(taskSendMessage);
  userScheduler.addTask(runBackbone);

  runBackbone.enable();
  taskSendMessage.enable();
  Serial.println("DONE SETUP");
}

void receivedCallback(uint32_t from, String &msg){
  Serial.printf("Got a new message from %d = %s", from, msg.c_str());
  core->receivedMail(msg);
}

void newConnectionCallback( bool adopt ) {
  Serial.printf("New Connection, adopt=%d\n", adopt);
}

void sendMessage(){
  Serial.println("Send message!");
  if (core->hasMail()){
      String msg = core->getMail();
      network.sendBroadcast(msg);
      Serial.printf("Sending message: %s\n", msg.c_str());
  }
  taskSendMessage.setInterval( random(TASK_SECOND * 1, TASK_SECOND * 5));
}

void runBackboneCall(){
 // Serial.println("CALL RUN");
  int delta = millis();
  delta = delta - lastTime;
  lastTime = delta; 
  core->runBackbone(delta);
}

// the loop function runs over and over again forever
void loop() {

  userScheduler.execute(); // it will run mesh scheduler as well
  network.update();
}
