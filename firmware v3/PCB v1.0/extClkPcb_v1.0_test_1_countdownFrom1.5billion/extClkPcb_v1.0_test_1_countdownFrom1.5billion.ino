// Test of PCB v1.0
// No RTC, No brightness control
// Counts down from ~1.5 billion seconds

#include "LedControl.h"
LedControl lc = LedControl(7,6,5,2); // Arduino pins: D7=DIN, D6=CLK, D5=LOAD/CS, 2= 2x 7219 driver chips

unsigned long n = 1514505600UL;
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
  for (int i = 11; i >= 0; i--) { // start from most significant
    int d = digits[i];
    int dev = (11 - i) / 8;
    int pos = (11 - i) % 8;
    bool dp = (i % 3 == 0 && i != 0);

    if (leading && d == 0) {
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
