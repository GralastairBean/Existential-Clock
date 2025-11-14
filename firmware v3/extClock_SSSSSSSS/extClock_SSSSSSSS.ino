#include <LedControl.h>
#include <Wire.h>
#include <RTClib.h>

#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 2); // 2 modules = 16 digits
RTC_DS3231 rtc;

// Example "death date"
DateTime deathTime(2070, 9, 5, 0, 0, 0); //(year, month, day, hour, minute, second);

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

// Display an integer value right‑aligned across 16 digits
void displayNumber(unsigned long long value) {
  for (int module = 1; module >= 0; module--) {   // reverse order for your wiring
    for (int i = 0; i < 8; i++) {
      if (value > 0) {
        int digit = value % 10;
        lc.setDigit(module, i, digit, false);
        value /= 10;
      } else {
        lc.setChar(module, i, ' ', false); // blank leading positions
      }
    }
  }
}

void loop() {
  DateTime now = rtc.now();

  if (now >= deathTime) {
    // Show "0" when expired
    displayNumber(0);
  } else {
    TimeSpan remaining = deathTime - now;
    unsigned long long totalSecs = remaining.totalseconds();
    displayNumber(totalSecs);
  }

  delay(1000);
}
