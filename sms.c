#include <stdio.h>
#include <stdlib.h>

unsigned char CharToSMS(unsigned char X)
{
  unsigned char retVal = 0;

  if (X < 32)
    retVal = 0;
  else if ((X >= 32) && (X <= 45))
    retVal = X + 4;
  else if ((X >= 46) && (X <= 47))
    retVal = X - 45;
  else if ((X >= 48) && (X <= 57))  // 0..9
    retVal = X + 2;
  else if ((X >= 58) && (X <= 64))
    retVal = X - 55;
  else if ((X >= 65) && (X <= 90))  // A..Z
    retVal = X - 55;
  else if ((X >= 91) && (X <= 93))
    retVal = X - 31;
  else if (X == 95)
    retVal = 63;        // underscore character
  else
    retVal = 39;  // All chars not in alphabet are set to '#'

  return retVal;
}

unsigned char SMSToChar(unsigned char X)
{
  unsigned char retVal = 0;

  if (X == 0)
    retVal = 0;
  else if ((X >= 1) && (X <= 2))
    retVal = X + 45;
  else if ((X >= 3) && (X <= 9))  
    retVal = X + 55;
  else if ((X >= 10) && (X <= 35))  // A..Z
    retVal = X + 55;
  else if ((X >= 36) && (X <= 49))
    retVal = X - 4;
  else if ((X >= 50) && (X <= 59)) // 0..9
    retVal = X - 2;
  else if ((X >= 60) && (X <= 62))
    retVal = X + 31;
  else if (X == 63)
    retVal = X + 32;
  else 
    retVal = 0;  // This statement should never be reached

  return retVal;
}

