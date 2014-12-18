#include "Command.h"

Command::Command()
{
  p_maxLength = 5;
  
  reset();
}


String Command::name()
{
  return data[0];
}


String Command::at(int i)
{
  if (p_length > 0 && i < p_length && i >= 0) {
    return data[i];
  } else {
    return "";
  }
}


int Command::length()
{
  return p_length;
}


void Command::parse(String src) 
{
  reset();
  
  int i = 0;
  int pos;
  int lastPos = 0;
  String part;
  
  while (i < p_maxLength) {
    pos = src.indexOf(',', lastPos);
    if (pos != -1) {
      data[i] = src.substring(lastPos, pos);
      lastPos = pos + 1;
    } else {
      data[i] = src.substring(lastPos, src.length());
    }
    
    i++;
  }
  
  p_length = i;
}


void Command::reset()
{
  int i;
  
  for (i = 0; i < p_maxLength; i++) {
    data[i] = "";
  }
  
  p_length = 0;
}
