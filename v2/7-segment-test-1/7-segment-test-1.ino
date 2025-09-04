#include <LedControl.h>

// Pins for the MAX7219
#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

// Create an instance of LedControl
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1); // 1 = Number of MAX7219 modules

void setup() {
  // Initialize the MAX7219
  lc.shutdown(0, false);   // Wake up the display
  lc.setIntensity(0, 8);   // Set brightness level (0-15)
  lc.clearDisplay(0);      // Clear the display
}

void loop() {
  // Display a number (e.g., 12345678)
  displayNumber(12345678);
  delay(2000); // Wait 2 seconds
  
  // Display another number (e.g., 98765432)
  displayNumber(98765432);
  delay(2000);
}

// Function to display a number on the 8-digit display
void displayNumber(long number) {
  for (int i = 0; i < 8; i++) {
    // Extract each digit (right to left)
    int digit = number % 10;
    lc.setDigit(0, i, digit, false); // 'false' = no decimal point
    number /= 10;
  }
}
