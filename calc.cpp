#include <arduino.h>

#include "calc.h"
#include "config.h"

// calculated BPM value based on a percentage of the minimum and maximum BPM's
// linear TODO: investigate curves
float calculatedBPM (int value) {
  float bpm = (float((float) value / 1023) * (MAX_BPM - MIN_BPM)) + MIN_BPM;

  return bpm;
}

float calculatedPercentage (int value) {
  float fvalue = (float) value;
  float percent = abs((fvalue - (BIAS * 2))) / 1023;

  return percent;
}

float tickDuration (float bpm) {
  return 60000 / bpm;
}

char *ftoa (char *str, float f, int precision) {
  long p[] = {0,10,100,1000,10000,100000,1000000,10000000,100000000};
  char *ret = str;
  long pre = (long) f;

  itoa(pre, str, 10);

  // advance to the end
  while (*str != '\0') {
    str++;
  }

  *str++ = '.';

  long dec = abs((long)((f - pre) * p[precision]));
  itoa(dec, str, 10);

  return ret;
}
