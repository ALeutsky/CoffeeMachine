/**
 * WaterMeter
 * @author Alexander Leutsky
 * @license CC BY-NC-SA
 */

#include "Arduino.h"
#include "WaterMeter.h"


WaterMeter::WaterMeter(int tp, int ep, long h)
{
   pinMode(tp, OUTPUT);
   pinMode(ep, INPUT);
   trigPin = tp;
   echoPin = ep;
   height   = h;
}


long WaterMeter::distance() 
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  p_duration = pulseIn(echoPin, HIGH);
  p_distance = p_duration * 100 / 266 / 2; // 29
  return p_distance;
}


long WaterMeter::level() 
{
  return height - distance();
}


long WaterMeter::avgLevel(int n, int ms) 
{
  int i;
  long avg_level = 0;
  
  for (i = 0; i < n; i++) {
    avg_level += level();
    delay(ms);
  }
  
  return avg_level / n;
}

int WaterMeter::levelToPercent(long lvl) 
{
  return (int)(lvl * 100 / (height - 20));
}
