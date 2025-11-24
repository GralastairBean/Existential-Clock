#include "LedControl.h"

LedControl lc = LedControl(7,6,5,2);  // two chained MAX7219s

void setup() {
  for (int i=0; i<2; i++) {
    lc.shutdown(i,false);
    lc.setIntensity(i,1);
    lc.clearDisplay(i);
    for (int pos=0; pos<8; pos++) {
      lc.setChar(i,pos,'8',true);  // all segments on
    }
  }
}

void loop() {
  // nothing
}
