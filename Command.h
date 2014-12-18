#include "Arduino.h"

#ifndef Command_h
#define Command_h

class Command
{
  public:
    Command();
    String name();
    String at(int i);
    int length();
    void parse(String src);
    void reset();
    
  private:
    int p_length;
    int p_maxLength;
    String data[5];
};

#endif
