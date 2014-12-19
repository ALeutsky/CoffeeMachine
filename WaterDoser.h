/**
 * WaterDoser
 * @author Alexander Leutsky
 * @license CC BY-NC-SA
 */
 
#include "Arduino.h"
#include "WaterMeter.h"
#include "Warmer.h"
 
#ifndef WaterDoser_h
#define WaterDoser_h
 
class WaterDoser
{
  public:
    WaterDoser(int warmerPin, int trigPin, int echoPin, int tankHeight);
    
    Warmer* warmer;
    WaterMeter* meter;
    
    long level;
    int levelPercent;
    
    bool isActive();
    int start(long cups);
    void stop();
    void refresh();
    //int level();
    //int avgLevel(int n, int ms);
    
    
  private:
    bool p_isActive;
    int p_cupSize;
    long p_startLevel;
    long p_endLevel;
    long p_minLevel;
};

#endif
