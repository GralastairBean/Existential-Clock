
// Proof of concept to drive a single 4 digit 7-segment display
// Arduino pins: D7=DIN, D6=CLK, D5=LOAD/CS

#include "LedControl.h"

LedControl lc = LedControl(7,6,5,1);

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,6);
  lc.clearDisplay(0);
}

void displayNumber(int num) {
  int d0 = num % 10;
  int d1 = (num / 10) % 10;
  int d2 = (num / 100) % 10;
  int d3 = (num / 1000) % 10;

  // reverse digit order for natural left‑to‑right counting
  lc.setDigit(0,3,d0,false);
  lc.setDigit(0,2,d1,false);
  lc.setDigit(0,1,d2,false);
  lc.setDigit(0,0,d3,false);
}

void loop() {
  for(int n = 9999; n >= 0; n--) {
    displayNumber(n);
    delay(1000);
  }
}
