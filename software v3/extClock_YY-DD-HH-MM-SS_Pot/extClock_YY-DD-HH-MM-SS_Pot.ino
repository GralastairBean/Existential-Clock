#include <LedControl.h>
#include <Wire.h>
#include <RTClib.h>

#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13
#define POT_PIN A0 // potentiometer input

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 2); 
RTC_DS3231 rtc;

// Example "death date"
DateTime deathTime(2070, 12, 31, 0, 0, 0);

// --- Brightness smoothing variables ---
const int SMOOTH_SAMPLES = 3;      // fewer samples = snappier response
int potBuffer[SMOOTH_SAMPLES];     // readings buffer
int bufferIndex = 0;               // circular buffer index
long bufferTotal = 0;              // sum of stored readings

void setup() {
  Serial.begin(9600); // serial monitor for debugging

  if (!rtc.begin()) {
    while (true); // Stop if RTC not found
  }

  // Initialize brightness buffer with initial pot value
  int initialPot = analogRead(POT_PIN);
  for (int i = 0; i < SMOOTH_SAMPLES; i++) {
    potBuffer[i] = initialPot;
    bufferTotal += initialPot;
  }

  for (int module = 0; module < 2; module++) {
    lc.shutdown(module, false);
    lc.setIntensity(module, 2); // initial brightness
    lc.clearDisplay(module);
  }
}

void printToDisplay(const char *buf) {
  int len = strlen(buf);
  int pos = 0;
  for (int i = len - 1; i >= 0; i--) {
    char c = buf[i];
    int module = 1 - pos / 8;
    int digit = pos % 8;

    if (c == '-') {
      lc.setChar(module, digit, '-', false);
    } else if (c >= '0' && c <= '9') {
      lc.setDigit(module, digit, c - '0', false);
    } else {
      lc.setChar(module, digit, ' ', false);
    }
    pos++;
  }
  for (; pos < 16; pos++) {
    int module = 1 - pos / 8;
    int digit = pos % 8;
    lc.setChar(module, digit, ' ', false);
  }
}

void displayCountdown(TimeSpan remaining) {
  long totalDays = remaining.days();
  int years = totalDays / 365;
  int days = totalDays % 365;
  int hours = remaining.hours();
  int mins = remaining.minutes();
  int secs = remaining.seconds();

  char buf[20];
  snprintf(buf, sizeof(buf), "%02d-%03d-%02d-%02d-%02d",
           years, days, hours, mins, secs);

  printToDisplay(buf);
}

void loop() {
  // --- Smooth brightness control ---
  int newReading = analogRead(POT_PIN);

  bufferTotal -= potBuffer[bufferIndex];
  potBuffer[bufferIndex] = newReading;
  bufferTotal += newReading;

  bufferIndex = (bufferIndex + 1) % SMOOTH_SAMPLES;

  int averageReading = bufferTotal / SMOOTH_SAMPLES;

  int brightness = (averageReading * 15L) / 1010;

  for (int module = 0; module < 2; module++) {
    lc.setIntensity(module, brightness);
  }

  // Debug output of current brightness
  Serial.print("Pot raw: ");
  Serial.print(newReading);
  Serial.print(" | Smoothed: ");
  Serial.print(averageReading);
  Serial.print(" | Brightness: ");
  Serial.println(brightness);

  // --- Countdown display ---
  DateTime now = rtc.now();

  if (now >= deathTime) {
    printToDisplay("00-000-00-00-00");
  } else {
    TimeSpan remaining = deathTime - now;
    displayCountdown(remaining);
  }

  delay(10); // faster refresh for brightness control
}
