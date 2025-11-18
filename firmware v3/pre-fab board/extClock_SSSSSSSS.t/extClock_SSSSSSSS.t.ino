#include <LedControl.h>
#include <Wire.h>
#include <RTClib.h>

#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 2); // 2 modules = 16 digits
RTC_DS3231 rtc;

// Example "death date"
DateTime deathTime(2070, 9, 5, 0, 0, 0);

// For tenths tracking
unsigned long lastSecondMillis = 0;
int lastRtcSecond = -1;

// Display value + tenths, right‑aligned, with a decimal point on the LAST seconds digit
void displayNumberWithTenths(unsigned long long seconds, int tenth) {
  int pos = 0; // rightmost digit position across 16 digits

  // Place tenths digit (no decimal point!)
  lc.setDigit(1, pos, tenth, false);
  pos++;

  bool dpHere = true;  // flag to light up the last seconds digit's DP
  if (seconds == 0) {
    // Show "0." before tenths
    lc.setDigit(1, pos, 0, dpHere);
    pos++;
  } else {
    while (seconds > 0 && pos < 16) {
      int digit = seconds % 10;
      lc.setDigit(1 - pos/8, pos % 8, digit, dpHere);
      dpHere = false;  // only the very first seconds digit gets the decimal
      seconds /= 10;
      pos++;
    }
  }

  // Blank the rest
  for (; pos < 16; pos++) {
    lc.setChar(1 - pos/8, pos % 8, ' ', false);
  }
}

void setup() {
  if (!rtc.begin()) {
    while (true); // Stop if RTC not found
  }

  for (int module = 0; module < 2; module++) {
    lc.shutdown(module, false);
    lc.setIntensity(module, 2);
    lc.clearDisplay(module);
  }
}

void loop() {
  DateTime now = rtc.now();
  TimeSpan remaining = deathTime - now;
  unsigned long long secsRemaining = remaining.totalseconds();

  // Detect new second tick
  if (now.second() != lastRtcSecond) {
    lastRtcSecond = now.second();
    lastSecondMillis = millis();
  }

  // Tenths based on millis since last RTC second change
  unsigned long elapsed = millis() - lastSecondMillis;
  int tenths = 9 - ((elapsed % 1000) / 100); // countdown 9 → 0
  if (tenths < 0) tenths = 0;

  // Display
  if (now >= deathTime) {
    displayNumberWithTenths(0, 0);
  } else {
    displayNumberWithTenths(secsRemaining, tenths);
  }
}
