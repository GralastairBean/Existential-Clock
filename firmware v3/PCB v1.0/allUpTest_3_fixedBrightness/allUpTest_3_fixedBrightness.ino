// All Up Test of PCB v1.0
// Fixed brightness (no photo‑resistor)
// RTC calculated time to live

#define FIRMWARE_VERSION "0.1.0" //change this at each new release

#include <Wire.h>
#include <RTClib.h>
#include "LedControl.h"

LedControl lc = LedControl(7, 6, 5, 2); // Arduino pins: D7=DIN, D6=CLK, D5=LOAD/CS, 2=2x7219 driver chips
RTC_DS3231 rtc;

int fixedBrightness = 0; // set the fixed brightness: 0 (dimmest) to 15 (brightest

DateTime deathTime(2073, 11, 22, 00, 00, 00);  // (year, month, day, hour...) of death
unsigned long lastTick = 0;

void setup() {
  Serial.begin(9600);
  if (!rtc.begin()) {
  Serial.println("RTC init fail, check connections");
  delay(1000);  // give time to send before blocking
  while (1);
  }
  Serial.print("Existential Clock Firmware Version ");
  Serial.println(FIRMWARE_VERSION);

  TimeSpan remaining = deathTime - rtc.now();

  Serial.print("RTC Time: ");
  Serial.print(rtc.now().day()); Serial.print("/");
  Serial.print(rtc.now().month()); Serial.print("/");
  Serial.print(rtc.now().year()); Serial.print(" ");
  Serial.print(rtc.now().hour()); Serial.print(":");
  Serial.print(rtc.now().minute()); Serial.print(":");
  Serial.println(rtc.now().second());

  Serial.print("Death Time: ");
  Serial.print(deathTime.day()); Serial.print("/");
  Serial.print(deathTime.month()); Serial.print("/");
  Serial.print(deathTime.year()); Serial.print(" ");
  Serial.print(deathTime.hour()); Serial.print(":");
  Serial.print(deathTime.minute()); Serial.print(":");
  Serial.println(deathTime.second());

  Serial.print("Seconds to death: ");
  Serial.println((unsigned long)remaining.totalseconds());

  for (int i = 0; i < 2; i++) {
    lc.shutdown(i, false);
    lc.clearDisplay(i);
    lc.setIntensity(i, fixedBrightness);
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
