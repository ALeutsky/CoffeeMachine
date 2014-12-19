/**
 * Warmer
 * @author Alexander Leutsky
 * @license CC BY-NC-SA
 */

#ifndef Warmer_h

#define Warmer_h

class Warmer
{
  public:
    Warmer();
    
    void attach(int pin);

    bool isActive;
    
    void on();
    void off();
    
  private:
    int pin;
};

#endif
