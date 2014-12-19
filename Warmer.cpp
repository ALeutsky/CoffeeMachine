/**
 * Warmer
 * @author Alexander Leutsky
 * @license CC BY-NC-SA
 */

#include "Arduino.h"
#include "Warmer.h"

Warmer::Warmer(int p)
{
  pin = p;
  pinMode(pin, OUTPUT);
  off();
}

void Warmer::on() 
{
  digitalWrite(pin, LOW);
  isActive = true;
}

void Warmer::off() 
{
  digitalWrite(pin, HIGH);
  isActive = false;
}
  
