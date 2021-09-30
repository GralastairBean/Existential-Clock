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

double age = 276936; //31 years = 271560 hours, round to 270000
double lifeExp = 713064; //81.4 years = 713064 hours
double hoursLeft = lifeExp - age;
double pct = (age / lifeExp) * 100;
unsigned long intervalMillis = 1000; // number of millisecs between updating "age"
unsigned long currentMillis = 0;    // stores the value of millis() in each iteration of loop()
unsigned long previousMillis = 0;   // will store last time "age" was updated



void setup() {

  Serial.begin(9600);
  // Start Wire library for I2C
  Wire.begin();


  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);


}

void updateAge() {

  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(0.5);
  //Set the cursor coordinates
  display.setCursor(0, 0);
  display.print("EXISTENTIAL CLOCK v2");
  display.setCursor(0, 10);
  display.print("time: ");
  display.print(hoursLeft, 0);
  display.setCursor(0, 20);
  display.print("pct: ");
  display.print(pct, 5);
  display.print(" %");

  Serial.print("age:  ");
  Serial.print(age, 0);
  Serial.print("  lifeExp:  ");
  Serial.print(lifeExp, 0);
  Serial.print("  hoursLeft:  ");
  Serial.print(hoursLeft, 0);
  Serial.print("  pct:  ");
  Serial.print(pct, 7);
  Serial.println("%");
}
void loop() {

  currentMillis = millis();   //check the time
  if (currentMillis - previousMillis >= intervalMillis) {
    age = age + 1;
    hoursLeft = lifeExp - age;
    pct = (age / lifeExp) * 100;
    previousMillis += intervalMillis;
    updateAge();
    display.display();
  }
}
