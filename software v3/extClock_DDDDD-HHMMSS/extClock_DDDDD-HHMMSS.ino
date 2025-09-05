#include <LedControl.h>
#include <Wire.h>
#include <RTClib.h>

#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 2); // 2 chained modules
RTC_DS3231 rtc;

// Example "death date"
DateTime deathTime(2070, 9, 5, 0, 0, 0); //(year, month, day, hour, minute, second);

void setup() {
  if (!rtc.begin()) {
    while (true); // Halt if RTC not found
  }

  for (int module = 0; module < 2; module++) {
    lc.shutdown(module, false);
    lc.setIntensity(module, 2);
    lc.clearDisplay(module);
  }
}

// Display text using only digits, '-' or space
void displayText(const char* txt) {
  int len = strlen(txt);

  // Fill from rightmost digit, module=1 down to module=0
  int pos = len - 1;
  for (int module = 1; module >= 0; module--) {
    for (int i = 0; i < 8; i++) {
      char c = (pos >= 0) ? txt[pos--] : ' ';

      if (c >= '0' && c <= '9') {
        lc.setDigit(module, i, c - '0', false);
      } else if (c == '-') {
        lc.setChar(module, i, '-', false);
      } else {
        lc.setChar(module, i, ' ', false);
      }
    }
  }
}

void loop() {
  DateTime now = rtc.now();

  if (now >= deathTime) {
    displayText("EXP-");
  } else {
    TimeSpan remaining = deathTime - now;
    long totalSecs = remaining.totalseconds();

    long days = totalSecs / 86400;
    totalSecs %= 86400;
    int hours = totalSecs / 3600;
    totalSecs %= 3600;
    int minutes = totalSecs / 60;
    int seconds = totalSecs % 60;

    // Format: DDDDD-HH-MM-SS
    char buf[17];
    snprintf(buf, sizeof(buf), "%05ld-%02d-%02d-%02d", days, hours, minutes, seconds);

    displayText(buf);
  }

  delay(1000);
}
