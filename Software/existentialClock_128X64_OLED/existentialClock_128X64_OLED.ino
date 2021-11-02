/*
  OLED existentialClock

  Shows user how long they have left to live
  Displays results on 128 x 64 OLED display
  Uses Adafruit SSD1306 OLED Library
  Uses Adafruit GFX Graphics Library

  Al Green 2021
*/

// Include Wire Library for I2C
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Setup OLED using Adafruit GFX Graphics Library
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3c ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Existential life expectancy calculations
double ageYears = 31; //31 years = 276936 hours
double ageDays = ageYears * 365;
double ageHours = ageDays * 24;
double lifeExpYears = 81.4; //81.4 years = 713064 hours
double lifeExpDays = lifeExpYears * 365;
double lifeExpHours = lifeExpDays * 24;
double yearsLeft = lifeExpYears - ageYears;
double daysLeft = lifeExpDays - ageDays;
double hoursLeft = lifeExpHours - ageHours;
double pctLeft = 100 - ( (ageHours / lifeExpHours) * 100);
//Time monitors

unsigned long intervalMillis1 = 3600000; // number of millisecs between updating "age" 1 hr = 3600000
unsigned long currentMillis1 = 0;    // stores the value of millis() in each iteration of loop()
unsigned long previousMillis1 = 0;   // will store last time "age" was updated

unsigned long intervalMillis2 = 5000; // number of millisecs between changing data shown on screen
unsigned long currentMillis2 = 0;    // stores the value of millis() in each iteration of loop()
unsigned long previousMillis2 = 0;   // will store last time screen data was changed

//flag to change data screen
int flag = 0;

void setup() {

  // Start debug Serial
  Serial.begin(9600);
  // Start Wire library for I2C
  Wire.begin();
  // initialize OLED with I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Please" );
  display.setCursor(0, 20);
  display.print("wait" );
  display.display();
  //delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Please" );
  display.setCursor(0, 20);
  display.print("wait." );
  display.display();
  //delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Please" );
  display.setCursor(0, 20);
  display.print("wait.." );
  display.display();
  //delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Please" );
  display.setCursor(0, 20);
  display.print("wait..." );
  display.display();
  //delay(500);
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("EXISTENTIAL" );
  display.setCursor(0, 40);
  display.print("CLOCK v2");
  display.display();
  //delay(1500);


  //SERIAL DEBUG
  Serial.print("flag:  ");
  Serial.print(flag);

  Serial.print("  lifeExpHours:  ");
  Serial.print(lifeExpHours, 0);
  Serial.print("  lifeExpDays:  ");
  Serial.print(lifeExpDays, 2);
  Serial.print("  lifeExpYears:  ");
  Serial.print(lifeExpYears, 5);

  Serial.print("  ageHours:  ");
  Serial.print(ageHours, 0);
  Serial.print("  ageDays:  ");
  Serial.print(ageDays, 2);
  Serial.print("  ageYears:  ");
  Serial.print(ageYears, 5);

  Serial.print("  hoursLeft:  ");
  Serial.print(hoursLeft, 0);
  Serial.print("  daysLeft:  ");
  Serial.print(daysLeft, 2);
  Serial.print("  yearsLeft:  ");
  Serial.print(yearsLeft, 5);

  Serial.print("  pctLeft:  ");
  Serial.print(pctLeft, 3);
  Serial.println("%");
}


void updateDisplay() {
  // Clear the display
  display.clearDisplay();
  //Set the color - always use white despite actual display color
  display.setTextColor(WHITE);
  //Set the font size
  display.setTextSize(2);
  //Check flag settging to decide which data value to display
  if (flag == 0) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(20, 0);
    display.print("pctLeft");
    display.setCursor(15, 32);
    display.print(pctLeft, 3);
    display.setCursor(100, 32);
    display.print("%");
  }
  else if (flag == 1) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 0);
    display.print("yearsLeft");
    display.setCursor(15, 32);
    display.print(yearsLeft, 5);

  }
  else if (flag == 2) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(15, 0);
    display.print("daysLeft");
    display.setCursor(17, 32);
    display.print(daysLeft, 2);

  }
  else {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(10, 0);
    display.print("hoursLeft");
    display.setCursor(26, 32);
    display.print(hoursLeft, 0);

  }

}

void updateAge() {
  //increment age and recalculate all ages
  ageHours = ageHours + 1;
  ageDays = ageHours / 24;
  ageYears = ageDays / 365;
  //recalculate time left
  hoursLeft = lifeExpHours - ageHours;
  daysLeft = lifeExpDays - ageDays;
  yearsLeft = lifeExpYears - ageYears;
  pctLeft = 100 - ( (ageHours / lifeExpHours) * 100);

  //SERIAL DEBUG
  Serial.print("flag:  ");
  Serial.print(flag);

  Serial.print("  ageHours:  ");
  Serial.print(ageHours, 0);
  Serial.print("  ageDays:  ");
  Serial.print(ageDays, 2);
  Serial.print("  ageYears:  ");
  Serial.print(ageYears, 5);

  Serial.print("  hoursLeft:  ");
  Serial.print(hoursLeft, 0);
  Serial.print("  daysLeft:  ");
  Serial.print(daysLeft, 2);
  Serial.print("  yearsLeft:  ");
  Serial.print(yearsLeft, 5);

  Serial.print("  pctLeft:  ");
  Serial.print(pctLeft, 4);
  Serial.println("%");
}
void loop() {
  //check the time
  currentMillis1 = millis();
  currentMillis2 = millis();

  //if time to update display then call updateDisplay() function and increment the flag
  if (currentMillis2 - previousMillis2 >= intervalMillis2) {
    previousMillis2 += intervalMillis2;
    flag = flag + 1;
    if (flag == 4) {
      flag = 0;
    }
    updateDisplay();
    display.display();
  }

  //if time to update age play then call updateAge() function
  if (currentMillis1 - previousMillis1 >= intervalMillis1) {
    previousMillis1 += intervalMillis1;
    updateAge();
    display.display();
  }
}
