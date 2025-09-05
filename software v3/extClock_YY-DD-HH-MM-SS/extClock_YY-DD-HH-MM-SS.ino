#include <LedControl.h>
#include <Wire.h>
#include <RTClib.h>

#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 2); // 2 modules = 16 digits
RTC_DS3231 rtc;

// Example "death date"
DateTime deathTime(2070, 12, 31, 0, 0, 0); //(year, month, day, hour, minute, second);

void setup() {
  if (!rtc.begin()) {
    while (true); // Stop if RTC not found
  }

  for (int module = 0; module < 2; module++) {
    lc.shutdown(module, false);
    lc.setIntensity(module, 2); // brightness value = 0-15
    lc.clearDisplay(module);
  }
}

// Print a string (up to 16 chars) right‑aligned to the 16 digits
void printToDisplay(const char *buf) {
  int len = strlen(buf);
  int pos = 0;
  // Fill from rightmost digit down to left
  for (int i = len - 1; i >= 0; i--) {
    char c = buf[i];
    int module = 1 - pos / 8;
    int digit = pos % 8;

    if (c == '-') {
      lc.setChar(module, digit, '-', false); // dash
    } else if (c >= '0' && c <= '9') {
      lc.setDigit(module, digit, c - '0', false);
    } else {
      lc.setChar(module, digit, ' ', false); // blank
    }
    pos++;
  }
  // Fill remaining left digits with blanks
  for (; pos < 16; pos++) {
    int module = 1 - pos / 8;
    int digit = pos % 8;
    lc.setChar(module, digit, ' ', false);
  }
}

// Format countdown into YY-DD-HH-MM-SS
void displayCountdown(TimeSpan remaining) {
  // Break down timespan
  long totalDays = remaining.days();
  int years = totalDays / 365;
  int days = totalDays % 365;
  int hours = remaining.hours();
  int mins = remaining.minutes();
  int secs = remaining.seconds();

  char buf[20];
  snprintf(buf, sizeof(buf), "%02d-%03d-%02d-%02d-%02d",
           years, days, hours, mins, secs);

  // Note: %03d for days allows 0–364 with 3 digits
  // If you want exactly 2 digits for days, just use %02d
  printToDisplay(buf);
}

void loop() {
  DateTime now = rtc.now();

  if (now >= deathTime) {
    printToDisplay("00-000-00-00-00");
  } else {
    TimeSpan remaining = deathTime - now;
    displayCountdown(remaining);
  }

  delay(1000);
}
