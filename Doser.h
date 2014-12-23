#ifndef Doser_h
#define Doser_h

#include <Servo.h>

class Doser
{
  public:
    Doser(int pin, int minPos, int maxPos, int portionSize);
    ~Doser();
    
    void shift(int portions);
    void reset();
  
  private:
    Servo* servo;
    int pin;
    int minPos;
    int maxPos;
    int portionSize;
};

#endif
