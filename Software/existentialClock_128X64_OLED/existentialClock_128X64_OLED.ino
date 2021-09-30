/*
  OLED Temperature and Humidity Meter
  oled-temp-humid-meter.ino
  Displays results on 128 x 64 OLED display
  Uses AM2320 I2C Temperature and Humidity sensor
  Uses Adafruit SSD1306 OLED Library
  Uses Adafruit AM2320 Library
  Uses Adafruit GFX Graphics Library
  
  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Include Wire Library for I2C
#include <Wire.h>

// Include Adafruit Graphics & OLED libraries
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



// Reset pin not used but needed for library
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

double hours = 0;
double total = 1000;
double pct;


void setup() {
  // Start Wire library for I2C
  Wire.begin();

  
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  

}

void displayUpdate(){
  // Delay to allow initialise
  delay(500);
  hours ++;
  pct = hours/total;



  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(1);
  //Set the cursor coordinates
  display.setCursor(0,0);
  display.print("Existential Clock");
  display.setCursor(0,10); 
  display.print("Pct:    "); 
  display.print(pct); 
  display.print(" %");
  display.setCursor(0,20);
  display.print("Hours: "); 
  display.print(hours); 
}
void loop() {
  displayUpdate();
  display.display();
}
