// Arduino pins: D7=DIN, D6=CLK, D5=CS.
// two MAX7219 driving 3x4=12 digits.

#include "LedControl.h"

LedControl lc = LedControl(7,6,5,2);  

void setup() {
  for (int i=0; i<2; i++) {
    lc.shutdown(i,false);
    lc.setIntensity(i,6);
    lc.clearDisplay(i);
  }
}

void loop() {
  for (int n=0; n<=9; n++) {
    for (int dev=0; dev<2; dev++) {
      for (int d=0; d<8; d++) {
        lc.setDigit(dev, d, n, false);
      }
    }
    delay(250);
  }
}
