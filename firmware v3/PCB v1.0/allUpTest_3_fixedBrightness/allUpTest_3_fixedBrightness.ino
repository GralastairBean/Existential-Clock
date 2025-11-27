// All Up Test of PCB v1.0
// Fixed brightness (no photo‑resistor)
// RTC calculated time to live

#include <Wire.h>
#include <RTClib.h>
#include "LedControl.h"

LedControl lc = LedControl(7,6,5,2); // Arduino pins: D7=DIN, D6=CLK, D5=LOAD/CS, 2=2x7219 driver chips
RTC_DS3231 rtc;

DateTime deathTime(2073, 11, 22, 00, 00, 00);  // target timestamp
unsigned long lastTick = 0;

void setup() {
  if (!rtc.begin()) {
    while (1);
  }

  for (int i = 0; i < 2; i++) {
    lc.shutdown(i, false);
    lc.clearDisplay(i);
    lc.setIntensity(i, 0);  // fixed brightness 0 (dimmest)
  }
}

// Show number with dots every 3 digits
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
      lc.setChar(dev, pos, ' ', false);
    else {
      lc.setDigit(dev, pos, d, dp);
      leading = false;
    }
  }
}

void loop() {
  unsigned long now = millis();

  // countdown update every 500ms to keep good time (no drift) will still only tick once per second
  if (now - lastTick >= 500) {
    lastTick = now;

    DateTime current = rtc.now();

    if (current >= deathTime) {
      for (int i = 0; i < 2; i++) lc.clearDisplay(i);
      return;
    }

    TimeSpan remaining = deathTime - current;
    unsigned long long totalSecs = remaining.totalseconds();
    displayNumber(totalSecs);
  }
}
