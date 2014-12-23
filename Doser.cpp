/**
 * Doser
 * @author Alexander Leutsky
 * @license CC BY-NC-SA
 */

#include "Arduino.h"
#include "Doser.h"

Doser::Doser(int pin, int minPos, int maxPos, int portionSize) : pin(pin), minPos(minPos), maxPos(maxPos), portionSize(portionSize)
{
  pinMode(pin, OUTPUT);
  servo = new Servo();
  servo->attach(pin);
  
  reset();
}

Doser::~Doser() 
{
  delete servo;
}

void Doser::shift(int portions) 
{
  int i;
  
  for (i = 0; i < portions; i++) {
    servo->write(maxPos);
    delay(500);
    servo->write(minPos);
    delay(500);
  }
}

void Doser::reset()
{
  servo->write(minPos);
}
