/**
 * CoffeeMachine
 * @author Alexander Leutsky
 * @license CC BY-NC-SA
 */

#include <Servo.h>
#include "./Command.h"
#include "./WaterDoser.h"
#include "./Doser.h"

#define WARMER_PIN 2
#define WM_TRIG_PIN 4
#define WM_ECHO_PIN 5
#define TANK_HEIGHT 128
#define COFFEE_DOSER_PIN 6
#define TEA_DOSER_PIN 7


WaterDoser* waterDoser;
Doser* coffeeDoser;
Doser* teaDoser;

Command inCmd;
String serialInputString;
bool hasNewCommand;
bool processing;


// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  serialInputString.reserve(40);
  serialInputString = "";
  hasNewCommand = false;
  processing = false;
  
  waterDoser  = new WaterDoser(WARMER_PIN, WM_TRIG_PIN, WM_ECHO_PIN, TANK_HEIGHT);
  coffeeDoser = new Doser(COFFEE_DOSER_PIN, 10, 73, 2);
  teaDoser    = new Doser(TEA_DOSER_PIN, 0, 130, 2);
}

// the loop routine runs over and over again forever:
void loop() {
  int error;
  int portions;
  
  waterDoser->refresh(); // ~ 150ms
  
  if (processing && !waterDoser->isActive()) {
    processing = false;
    Serial.println("$READY");
  }
  
  if (hasNewCommand) {
    hasNewCommand = false;
    
    if (inCmd.name() == "$STATE") {
      Serial.print("$STATE,");
      Serial.print(processing ? "PROCESSING," : "WAITING,");
      Serial.println(waterDoser->levelPercent);
      
    } else if (inCmd.name() == "$DO") { // $DO,DRINK_NAME,CUPS,PORTION
      if (processing) {
        Serial.println("$ERROR,BUSY");
      } else {
        error = 0;
        
        if (inCmd.at(1) == "COFFEE") {
          portions = inCmd.at(2).toInt();
          error = waterDoser->start(inCmd.at(2).toInt());
          
          if (!error) {
            coffeeDoser->shift(portions * inCmd.at(3).toInt());
          }
          
        } else if (inCmd.at(1) == "TEA") {
          portions = inCmd.at(2).toInt();
          error = waterDoser->start(inCmd.at(2).toInt());
          
          if (!error) {
            teaDoser->shift(portions * inCmd.at(3).toInt());
          }
          
        } else {
          error = -1;
        }
        
        if (error == 0) {
          processing = true;
        } else {
          Serial.print("$ERROR,");
          
          switch(error) {
            case -1:
              Serial.println("UNKNOWN DRINK");
              break;
            case 1:
              Serial.println("NO WATER");
              break;
            case 2:
              Serial.println("NOT ENOUGH WATER");
              break;
            default:
              Serial.println("UNKNOWN ERROR");
          }
        }      
      }
      
    } else {
      Serial.println("$ERROR,UNKNOWN COMMAND");
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
