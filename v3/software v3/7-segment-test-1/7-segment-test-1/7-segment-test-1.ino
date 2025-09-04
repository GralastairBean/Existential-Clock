#include <LedControl.h>

// Pins for the MAX7219
#define DIN_PIN 11
#define CS_PIN 10
#define CLK_PIN 13

// Create an instance of LedControl
LedControl lc = LedControl(DIN_PIN, CLK_PIN, CS_PIN, 1); // 1 = Number of MAX7219 modules

// Starting number
long currentNumber = 10000000;

void setup() {
  // Initialize the MAX7219
  lc.shutdown(0, false);   // Wake up the display
  lc.setIntensity(0, 1);   // Set brightness level to 2 (dim but visible)
  lc.clearDisplay(0);      // Clear the display
}

void loop() {
  // Display the current number
  displayNumber(currentNumber);
  
  // Decrement the number by 1
  currentNumber--;
  
  // If the number reaches 0, stop at 0
  if (currentNumber < 0) {
    currentNumber = 0;
  }
  
  // Wait for 1 second
  delay(1000);
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
