#include "LedControl.h"

LedControl lc = LedControl(7,6,5,1);

const int ldrPin = A1;  // LDR voltage divider output

unsigned long prevBright = 0;
float smoothLight = 300.0;  // initial low‑med value for smoothing

void setup() {
  lc.shutdown(0,false);
  lc.clearDisplay(0);
  // Serial.begin(9600); //uncomment to allow serial debug
}

void displayNumber(int num) {
  int d0 = num % 10;
  int d1 = (num / 10) % 10;
  int d2 = (num / 100) % 10;
  int d3 = (num / 1000) % 10;

  lc.setDigit(0,3,d0,false);
  lc.setDigit(0,2,d1,false);
  lc.setDigit(0,1,d2,false);
  lc.setDigit(0,0,d3,false);
}

void loop() {
  unsigned long now = millis();

  if (now - prevBright >= 100) {
    prevBright = now;

    int rawLight = analogRead(ldrPin);
    smoothLight = 0.9 * smoothLight + 0.1 * rawLight;

    // normalize and apply non‑linear shaping
    float norm = (float)(smoothLight - 100) / (1023 - 100);
    if (norm < 0) norm = 0;
    if (norm > 1) norm = 1;
    
    float shaped = pow(norm, 1.4); // tweak exponent for response curve 
    // Larger exponent (> 1) → suppresses low‑end brightness (dimmer in dim light).
    int brightness = (int)(shaped * 15);

    lc.setIntensity(0, brightness);
    displayNumber(brightness);

    Serial.print("Raw LDR: ");
    Serial.print(rawLight);
    Serial.print("  Smoothed: ");
    Serial.print(smoothLight);
    Serial.print("  Norm: ");
    Serial.print(norm,3);
    Serial.print("  Brightness: ");
    Serial.println(brightness);
  }
}
