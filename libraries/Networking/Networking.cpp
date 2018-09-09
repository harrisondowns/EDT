/*
 *  This sketch sends data via HTTP GET requests to data.sparkfun.com service.
 *
 *  You need to get streamId and privateKey at data.sparkfun.com and paste them
 *  below. Or just customize this script to talk to other HTTP servers.
 *
 */

#include <ESP8266WiFi.h>
#include "Arduino.h"

const char* ssid     = "elias's iPhone";
const char* password = "eeejjjmmm";

const char* host = "cryptic-waters-95987.herokuapp.com";

#define ADMIN false

void setup_wifi() {
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void postToStudent(String dataS){
	WiFiClient client;
  	const int httpPort = 80;
  	if (!client.connect(host, httpPort)) {
   		Serial.println("connection failed");
    	return;
  	}
  
	  // We now create a URI for the request
	String url;
	if (ADMIN) {
	  url = "/teacherPut";
	} else {
	  url = "/studentPut";
	}
	String data = "note=" + dataS;
	  // This will send the request to the server
	 // client.print(String("GET ") + url + " HTTP/1.1\r\n" +
	   //            "Host: " + host + "\r\n" + 
	    //           "Connection: close\r\n\r\n");
	if (ADMIN) {
	  client.println("POST /teacherPut HTTP/1.1");
	} else {
	  client.println("POST /studentPut HTTP/1.1");
	}
    client.println(String("Host: ") + host);
    client.println("Accept: */*");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
	unsigned long timeout = millis();
	while (client.available() == 0) {
	    if (millis() - timeout > 5000) {
	      	Serial.println(">>> Client Timeout !");
	      	client.stop();
	      	return;
	    }
	}
}

String getStudent(){
	WiFiClient client;
  	const int httpPort = 80;
  	if (!client.connect(host, httpPort)) {
   		Serial.println("connection failed");
    	return "";
  	}

	String url;
	if (ADMIN) {
	  url = "/getStudent";
	} else {
	  url = "/getTeacher";
	}
	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
	              "Host: " + host + "\r\n" + 
	               "Connection: close\r\n\r\n");
	
	unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
    //efe  Serial.println(">>> Client Timeout !");
      client.stop();
      return "";
    }
  }
  String line;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    line = client.readStringUntil('\n');
  }
  	return line;
}

void postAnswer(String dataS){
	WiFiClient client;
  	const int httpPort = 80;
  	if (!client.connect(host, httpPort)) {
   		Serial.println("connection failed");
    	return;
  	}
  
	  // We now create a URI for the request
	String url = "/setAnswer";

	String data = "answer=" + dataS;
	  // This will send the request to the server
	 // client.print(String("GET ") + url + " HTTP/1.1\r\n" +
	   //            "Host: " + host + "\r\n" + 
	    //           "Connection: close\r\n\r\n");
	client.println("POST /setAnswer HTTP/1.1");
    client.println(String("Host: ") + host);
    client.println("Accept: */*");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
	unsigned long timeout = millis();
	while (client.available() == 0) {
	    if (millis() - timeout > 5000) {
	      	Serial.println(">>> Client Timeout !");
	      	client.stop();
	      	return;
	    }
	}
}

String getAnswer(){
	WiFiClient client;
  	const int httpPort = 80;
  	if (!client.connect(host, httpPort)) {
   		Serial.println("connection failed");
    	return "";
  	}
  
	String url = "/getAnswer";
	client.print(String("GET ") + url + " HTTP/1.1\r\n" +
	              "Host: " + host + "\r\n" + 
	               "Connection: close\r\n\r\n");
	
	unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
    //efe  Serial.println(">>> Client Timeout !");
      client.stop();
      return "";
    }
  }
  String line;
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    line = client.readStringUntil('\n');
  }
  	return line;
}

char *clickerServer(String choice) {
  if (ADMIN) {
    postAnswer(choice);
    return "set!";
  } else {
    String a = getAnswer();
    if (a == choice) {
      return "Correct!";
    } else {
      return "Wrong :(";
    }
  }
}
