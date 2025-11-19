#include "LedControl.h"

LedControl lc = LedControl(7,6,5,2);  // two chained MAX7219s

unsigned long n = 1500000000UL;  // start value
unsigned long lastTick = 0;

void setup() {
  for (int i=0; i<2; i++) {
    lc.shutdown(i,false);
    lc.setIntensity(i,6);
    lc.clearDisplay(i);
  }
}

void displayNumber(unsigned long val) {
  for (int d=0; d<12; d++) {
    if (val > 0) {
      int digit = val % 10;
      val /= 10;
      int dev = d / 8;
      int pos = d % 8;
      lc.setDigit(dev,pos,digit,false);
    } else {
      int dev = d / 8;
      int pos = d % 8;
      lc.setChar(dev,pos,' ',false);  // blank leading digits
    }
  }
}

void loop() {
  unsigned long now = millis();
  if (now - lastTick >= 1000) {
    lastTick = now;
    displayNumber(n);
    if (n > 0) n--;
  }
}
