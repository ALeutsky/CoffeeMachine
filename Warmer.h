/*

*/

#ifndef Warmer_h

#define Warmer_h

class Warmer
{
  public:
    Warmer(int pin);

    bool isActive;
    
    void on();
    void off();
    
  private:
    int pin;
};

#endif
