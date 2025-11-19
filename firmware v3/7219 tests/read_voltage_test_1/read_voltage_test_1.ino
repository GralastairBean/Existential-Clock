#include "LedControl.h"

LedControl lc = LedControl(7,6,5,1);
const int analogPin = A0;   // voltage input pin

void setup() {
  lc.shutdown(0,false);
  lc.setIntensity(0,1);
  lc.clearDisplay(0);
}

void displayVoltage(float voltage) {
  if (voltage > 9.999) voltage = 9.999;
  int val = (int)(voltage * 1000);

  int d0 = val % 10;
  int d1 = (val / 10) % 10;
  int d2 = (val / 100) % 10;
  int d3 = (val / 1000) % 10;

  lc.setDigit(0,3,d0,false);
  lc.setDigit(0,2,d1,false);
  lc.setDigit(0,1,d2,false);
  lc.setDigit(0,0,d3,true);   // DP on the most significant digit → X.XXX
}

void loop() {
  int raw = analogRead(analogPin);
  float voltage = raw * (5.0 / 1023.0);
  displayVoltage(voltage);
  delay(500);
}
