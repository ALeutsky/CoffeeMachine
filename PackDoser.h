/*
0-120
*/

#ifndef PackDoser_h

#define PackDoser_h

#include <Servo.h>

class PackDoser
{
  public:
    PackDoser(int pin);
    
  private:
    int pin;
    Servo servo;
};

#endif
