#include <Wire.h>
#include <RTClib.h>

RTC_DS3231 rtc;

void setup() {
  Serial.begin(9600);
  while (!Serial) { delay(10); } // Wait for Serial to be ready (only needed on some Arduinos)

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC!");
    while (1);
  }

  Serial.println("RTC Setter Ready");
  Serial.println("Enter date & time in format: YYYY/MM/DD HH:MM:SS");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    int year, month, day, hour, minute, second;

    // Try to parse the format YYYY/MM/DD HH:MM:SS
    int parsed = sscanf(input.c_str(), "%d/%d/%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);

    if (parsed == 6) {
      rtc.adjust(DateTime(year, month, day, hour, minute, second));
      Serial.print("RTC updated to: ");
      Serial.println(input);
    } else {
      Serial.println("Invalid format! Use: YYYY/MM/DD HH:MM:SS");
    }
  }
}
