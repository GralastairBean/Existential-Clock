/*
Connections for the MAX7219 Modules:
-------------------------------------
Arduino   -> MAX7219 (First Module)
-------------------------------------
GND       -> GND
5V        -> VCC
D11       -> DIN
D10       -> CS
D13       -> CLK

MAX7219 (First Module) -> MAX7219 (Second Module)
-------------------------------------
DOUT (First Module) -> DIN (Second Module)
GND (First Module)  -> GND (Second Module)
VCC (First Module)  -> VCC (Second Module)
CLK (First Module)  -> CLK (Second Module)
CS (First Module)   -> CS (Second Module)
*/

#include <LedControl.h>

#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 2); // 2 Modules

long long currentNumber = 1607827200 ; // 51 years in seconds

void setup() {
  for (int module = 0; module < 2; module++) {
    lc.shutdown(module, false);   // Wake up the display
    lc.setIntensity(module, 2);   // Set brightness to 2
    lc.clearDisplay(module);      // Clear the display
  }
}

void loop() {
  displayNumber(currentNumber);
  currentNumber--;
  if (currentNumber < 0) {
    currentNumber = 0; // Stop at 0
  }
  delay(1000); // 1-second delay
}

void displayNumber(long long number) {
  for (int module = 1; module >= 0; module--) { // Reverse module order
    for (int i = 0; i < 8; i++) {
      if (number > 0) {
        int digit = number % 10;
        lc.setDigit(module, i, digit, false); // Display digit
        number /= 10;
      } else {
        lc.setChar(module, i, ' ', false); // Clear leading digits
      }
    }
  }
}
