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

// Add death date and time below
DateTime deathTime(2050, 11, 15, 20, 0, 0); //(year, month, day, hour, minute, second)

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
    lc.setIntensity(module, 3);   // Temporary startup brightness
    lc.clearDisplay(module);
  }
}

// Show number with dots every 3 digits
void displayNumberWithDots(unsigned long long number) {
  int digitCount = 0; // Total digits we've processed

  for (int module = 1; module >= 0; module--) { // Loop through the two modules (displays)
    for (int i = 0; i < 8; i++) { // Loop through each digit in the module
      if (number > 0 || digitCount == 0) {
        // Extract the current digit
        int digit = number % 10;
        number /= 10;
        digitCount++;

        // Enable the decimal point **before** every third digit (except the first group)
        bool showDot = ((digitCount - 1) % 3 == 0) && (digitCount > 1);

        // Display the digit with or without the decimal point
        lc.setDigit(module, i, digit, showDot);
      } else {
        // Blank out unused segments
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

      displayNumberWithDots(totalSecs);
    }
  }
}
