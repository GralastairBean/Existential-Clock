// All Up Test of PCB v1.0
// Auto-brightness control via photo-resistor on A1 Arduino pin
// Prints brightness data to serial for debug
// RTC calculated time to live

#include <Wire.h>
#include <RTClib.h>
#include "LedControl.h"

LedControl lc = LedControl(7,6,5,2); // Arduino pins: D7=DIN, D6=CLK, D5=LOAD/CS, 2= 2x 7219 driver chips
RTC_DS3231 rtc;

const int ldrPin = A1; // One leg connected to 5V, other to ground via 10k R and to pin A1

DateTime deathTime(2073, 11, 22, 00, 00, 00);  // target timestamp

unsigned long lastTick = 0;
unsigned long prevBright = 0;
float smoothLight = 300.0;

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    Serial.println("RTC not found");
    while (1);
  }

  for (int i = 0; i < 2; i++) {
    lc.shutdown(i, false);
    lc.clearDisplay(i);
  }
}

void displayNumber(unsigned long long val) {
  int digits[12];
  for (int i = 0; i < 12; i++) {
    digits[i] = val % 10;
    val /= 10;
  }

  bool leading = true;
  for (int i = 11; i >= 0; i--) {
    int d = digits[i];
    int dev = (11 - i) / 8;
    int pos = (11 - i) % 8;
    bool dp = (i % 3 == 0 && i != 0);

    if (leading && d == 0)
      lc.setChar(dev,pos,' ',false);
    else {
      lc.setDigit(dev,pos,d,dp);
      leading = false;
    }
  }
}

void loop() {
  unsigned long now = millis();

  // brightness update
  if (now - prevBright >= 100) {
    prevBright = now;
    int rawLight = analogRead(ldrPin);
    smoothLight = 0.9f * smoothLight + 0.1f * rawLight;

    float norm = (smoothLight - 100.0f) / (1023.0f - 100.0f);
    if (norm < 0) norm = 0;
    if (norm > 1) norm = 1;
    float shaped = pow(norm, 1.4f);
    int brightness = (int)(shaped * 15.0f);

    lc.setIntensity(0, brightness);
    lc.setIntensity(1, brightness);

    Serial.print("Raw: "); Serial.print(rawLight);
    Serial.print("  Smoothed: "); Serial.print(smoothLight,1);
    Serial.print("  Brightness: "); Serial.println(brightness);
  }

  // countdown update once per second
  if (now - lastTick >= 1000) {
    lastTick = now;

    DateTime current = rtc.now();

    if (current >= deathTime) {
      for (int i=0;i<2;i++) lc.clearDisplay(i);
      lc.setChar(1,7,'0',false);
      Serial.println("Countdown complete");
      return;
    }

    TimeSpan remaining = deathTime - current;
    unsigned long long totalSecs = remaining.totalseconds();

    displayNumber(totalSecs);
  }
}
