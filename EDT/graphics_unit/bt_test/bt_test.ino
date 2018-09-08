/*
* Bluetooh Basic: LED ON OFF - Avishkar
* Coder - Mayoogh Girish
* Website - http://bit.do/Avishkar
* Download the App : https://github.com/Mayoogh/Arduino-Bluetooth-Basic
* This program lets you to control a LED on pin 13 of arduino using a bluetooth module
*/
char data = 0;            //Variable for storing received data
void setup()
{
    Serial.begin(9600);   //Sets the baud for serial data transmission                               
}
void loop()
{
   if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      Serial.print(data);          //Print Value inside data in Serial monitor
      Serial.print("\n");        
      if(data == '1')              // Checks whether value of data is equal to 1
         Serial.print("ON");   //If value is 1 then LED turns ON
      else if(data == '0')         //  Checks whether value of data is equal to 0
         Serial.print("OFF");    //If value is 0 then LED turns OFF
   }
}