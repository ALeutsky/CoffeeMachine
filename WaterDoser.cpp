/**
 * WaterDoser
 * @author Alexander Leutsky
 * @license CC BY-NC-SA
 */

#include "WaterDoser.h"

WaterDoser::WaterDoser(int warmerPin, int trigPin, int echoPin, int tankHeight)
{
  warmer = new Warmer(warmerPin);
  meter  = new WaterMeter(trigPin, echoPin, tankHeight);
  
  p_isActive = false;
  p_cupSize = 15; // mm
  p_minLevel = 5; // mm
}


bool WaterDoser::isActive()
{
  return p_isActive;
}


int WaterDoser::start(long cups)
{
  if (level <= p_minLevel) {
    return 1;
  }
  
  if (cups <= 0 || ((level - p_minLevel) < (p_cupSize * cups))) {
    return 2;
  }
  
  p_isActive = true;
  p_startLevel = level;
  p_endLevel = p_startLevel - p_cupSize * cups;
  
  warmer->on();
  
  return 0;
}


void WaterDoser::stop()
{
  if (p_isActive) {
    p_isActive = false;
    warmer->off();
  }
}


void WaterDoser::refresh()
{
  level = meter->avgLevel(5, 30); // ~150ms
  levelPercent = meter->levelToPercent(level);
  
  if (p_isActive) {
    if (level < p_endLevel || level < p_minLevel) {
      stop();
    }
  }
}
