/*
3-73
*/

#ifndef SandDoser_h

#define SandDoser_h

#include <Servo.h>

class SandDoser
{
  public:
    SandDoser(int pin);
    
  private:
    int pin;
    Servo servo;
};

#endif
