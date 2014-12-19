/**
 * WaterMeter
 * @author Alexander Leutsky
 * @license CC BY-NC-SA
 */


#ifndef WaterMeter_h

#define WaterMeter_h

class WaterMeter
{
  public:
    WaterMeter(int tp, int ep, long h);

    long distance(); // millimeters
    long level();    // millimeters
    long avgLevel(int n, int ms);
    int levelToPercent(long level);
    
    int trigPin;
    int echoPin;

  private:
    
    long height;
    long p_duration;
    long p_distance; // millimeters
};

#endif
