#include <LedControl.h>
#include <Wire.h>
#include <RTClib.h>

#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

// Potentiometer pin
#define POT_PIN A0

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 2);
RTC_DS3231 rtc;

DateTime deathTime(2070, 9, 5, 0, 0, 0); //(year, month, day, hour, minute, second)

// Track brightness changes
int lastBrightness = -1;

// Track time updates
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(9600);

  if (!rtc.begin()) {
    while (1);  
  }
  for (int module = 0; module < 2; module++) {
    lc.shutdown(module, false);
    lc.setIntensity(module, 3);   // temporary startup brightness
    lc.clearDisplay(module);
  }
}

// Show number with dashes every 3 digits
void displayNumberWithDashes(unsigned long long number) {
  int digitCount = 0; // count since last dash

  for (int module = 1; module >= 0; module--) {
    for (int i = 0; i < 8; i++) {
      if (number > 0 || digitCount == 0) {
        int digit = number % 10;
        lc.setDigit(module, i, digit, false);
        number /= 10;
        digitCount++;

        // every 3 digits → insert dash in next position
        if (digitCount == 3 && (number > 0)) {
          if (i < 7) {
            lc.setChar(module, i + 1, '-', false);
            i++; // skip the dash slot
          } else if (module > 0) {
            lc.setChar(module - 1, 0, '-', false);
          }
          digitCount = 0;
        }
      } else {
        lc.setChar(module, i, ' ', false);
      }
    }
  }
}

void loop() {
  // --- Brightness control ---
  int potValue = analogRead(POT_PIN);                 // 0–1023
  int brightness = map(potValue, 0, 1000, 0, 15);     // 0–15

  if (brightness != lastBrightness) {
    for (int module = 0; module < 2; module++) {
      lc.setIntensity(module, brightness);
    }
    Serial.print("Brightness: ");
    Serial.println(brightness);
    lastBrightness = brightness;
  }

  // --- Countdown update once per second ---
  unsigned long currentMillis = millis();
  if (currentMillis - lastUpdate >= 1000) {
    lastUpdate = currentMillis;

    DateTime now = rtc.now();

    if (now >= deathTime) {
      lc.clearDisplay(0);
      lc.clearDisplay(1);
      lc.setChar(1, 7, '0', false);
    } else {
      TimeSpan remaining = deathTime - now;
      unsigned long long totalSecs = remaining.totalseconds();

      displayNumberWithDashes(totalSecs);
    }
  }
}
