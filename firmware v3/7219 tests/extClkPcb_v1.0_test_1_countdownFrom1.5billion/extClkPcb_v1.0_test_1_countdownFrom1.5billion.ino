#include "LedControl.h"

LedControl lc = LedControl(7,6,5,2);

unsigned long n = 1500000000UL;
unsigned long lastTick = 0;

void setup() {
  for (int i = 0; i < 2; i++) {
    lc.shutdown(i,false);
    lc.setIntensity(i,1);
    lc.clearDisplay(i);
  }
}

void displayNumber(unsigned long val) {
  int digits[12];
  for (int i = 0; i < 12; i++) {
    digits[i] = val % 10;
    val /= 10;
  }

  bool leading = true;
  for (int i = 0; i < 12; i++) {
    int d = digits[i];
    int dev = (11 - i) / 8;   // leftmost digits -> device 0, rightmost -> device 1
    int pos = (11 - i) % 8;   // left to right inside device

    bool dp = (i == 3 || i == 6 || i == 9);  // group every three digits from right

    if (leading && d == 0 && i >= 9) {
      lc.setChar(dev,pos,' ',false);
    } else {
      lc.setDigit(dev,pos,d,dp);
      leading = false;
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
