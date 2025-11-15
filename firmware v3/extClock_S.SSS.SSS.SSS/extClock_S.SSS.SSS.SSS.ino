#include <LedControl.h>
#include <Wire.h>
#include <RTClib.h>

#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 2); // 2 modules = 16 digits
RTC_DS3231 rtc;

// Example "death date"
DateTime deathTime(2025, 11, 16, 0, 0, 0); //(year, month, day, hour, minute, second);

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

// Display number with "comma" separators using decimal points
// Dot goes on the LEFT digit of each 3‑digit group
// Internal zeros are preserved, leading zeros are blanked
void displayNumberWithCommas(unsigned long long value) {
  // Special case: exact zero
  if (value == 0) {
    for (int m = 0; m < 2; m++) {
      lc.clearDisplay(m);
    }
    lc.setDigit(1, 0, 0, false); // just "0"
    return;
  }

  int groupCount = 0;      // digits in the current group of 3
  bool markNext = false;   // whether next digit should get the decimal point
  bool started = false;    // whether we’ve started printing non-blanks

  for (int module = 1; module >= 0; module--) {
    for (int i = 0; i < 8; i++) {
      if (value > 0 || started) {
        if (value > 0) {
          int digit = value % 10;
          value /= 10;
          groupCount++;
          started = true;

          lc.setDigit(module, i, digit, markNext);
          markNext = false;

          if (groupCount == 3 && value > 0) {
            groupCount = 0;
            markNext = true;
          }
        } else {
          // past the last digit, fill with blanks
          lc.setChar(module, i, ' ', false);
        }
      } else {
        // if nothing has started, blank it
        lc.setChar(module, i, ' ', false);
      }
    }
  }
}

void loop() {
  DateTime now = rtc.now();

  if (now >= deathTime) {
    displayNumberWithCommas(0);
  } else {
    TimeSpan remaining = deathTime - now;
    unsigned long long totalSecs = remaining.totalseconds();
    displayNumberWithCommas(totalSecs);
  }

  delay(1000);
}
