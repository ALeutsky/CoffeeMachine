#include "Arduino.h"
#include "SandDoser.h"

SandDoser::SandDoser(int p)
{
  pin = p;
  pinMode(pin, OUTPUT);
  servo.attach(pin);
}
