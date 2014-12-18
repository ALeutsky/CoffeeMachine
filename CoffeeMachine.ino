#include <Servo.h>
#include "./Command.h"
#include "./Warmer.h"
#include "./WaterMeter.h"

#define warmerPin 2
#define wmTrigPin 4
#define wmEchoPin 5
#define sandDoserPin 6
#define packDoserPin 7


Warmer warmer(warmerPin);
WaterMeter waterMeter(wmTrigPin, wmEchoPin, 128);

Command inCmd;
String serialInputString;
bool hasNewCommand;


// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(19200);
  serialInputString.reserve(40);
  serialInputString = "";
  hasNewCommand = false;
}

// the loop routine runs over and over again forever:
void loop() {
  long level = waterMeter.avgLevel(10, 30); // ~ 300ms
  //Serial.print("The level:");
  //Serial.println(level); // ~ 300m
  
  if (hasNewCommand) {
    hasNewCommand = false;
    
    if (inCmd.name() == "$STATE") {
      Serial.print("$STATE,");
      Serial.print("WAITING,");
      Serial.println(waterMeter.levelToPercent(level));
    } else if (inCmd.name() == "$DO") {
      
    } else {
      Serial.println("UNKNOWN COMMAND");
    }
  }
}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read(); 
    
    if (inChar == '\n') {
      inCmd.parse(serialInputString);
      serialInputString = "";
      hasNewCommand = true;
    } else {
      serialInputString += inChar;
    }
  }
}
