#include "LedControl.h"

// Arduino pin 7 → DIN, 6 → CLK, 5 → LOAD
LedControl lc = LedControl(7,6,5,1);

void setup() {
  lc.shutdown(0,false);   // wake up
  lc.setIntensity(0,15);  // max brightness
  lc.clearDisplay(0);     // clear

  for(int i=0;i<4;i++){
    lc.setChar(0,i,'8',false);   // all segments on
  }
}

void loop() {
  // nothing
}
