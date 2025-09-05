#include <Wire.h>
#include <RTClib.h>
#include <LedControl.h>

// Pins for the MAX7219
#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

// Two MAX7219 modules, chained
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 2);

// RTC
RTC_DS3231 rtc;

void setup() {
  for (int display = 0; display < 2; display++) {
    lc.shutdown(display, false);    // Wake up
    lc.setIntensity(display, 2);    // Brightness (0–15)
    lc.clearDisplay(display);       // Clear
  }

  if (!rtc.begin()) {
    while (true); // Stop if RTC not found
  }
}

void loop() {
  DateTime now = rtc.now();

  int tenths = (millis() % 1000) / 100; // 0–9 tenths

  displayDate(0, now.day(), now.month(), now.year());
  displayTime(1, now.hour(), now.minute(), now.second(), tenths);

  delay(100); // refresh every 0.1s
}

// Show date as DDMMYYYY
void displayDate(int display, int day, int month, int year) {
  int digits[8];

  digits[0] = day / 10;
  digits[1] = day % 10;
  digits[2] = month / 10;
  digits[3] = month % 10;
  digits[4] = (year / 1000) % 10;
  digits[5] = (year / 100) % 10;
  digits[6] = (year / 10) % 10;
  digits[7] = year % 10;

  for (int i = 0; i < 8; i++) {
    lc.setDigit(display, 7 - i, digits[i], false);
  }
}

// Show time as [blank]HHMMSS.t
void displayTime(int display, int hours, int minutes, int seconds, int tenths) {
  // Positions: left=7 ... right=0
  // Target format: [blank][H][H][M][M][S][S.][t]

  // Blank separator at left
  lc.setChar(display, 7, ' ', false);

  // Hours
  lc.setDigit(display, 6, (hours / 10) % 10, false);
  lc.setDigit(display, 5, hours % 10, false);

  // Minutes
  lc.setDigit(display, 4, minutes / 10, false);
  lc.setDigit(display, 3, minutes % 10, false);

  // Seconds
  lc.setDigit(display, 2, seconds / 10, false);
  // Ones of seconds with decimal point
  lc.setDigit(display, 1, seconds % 10, true);

  // Tenths, no decimal
  lc.setDigit(display, 0, tenths, false);
}
