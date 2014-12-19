/**
 * PackDoser
 * @author Alexander Leutsky
 * @license CC BY-NC-SA
 */

#include "Arduino.h"
#include "PackDoser.h"

PackDoser::PackDoser(int p) 
{
  pin = p;
  pinMode(pin, OUTPUT);
  servo.attach(pin);
}
