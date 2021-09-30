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
double age = 276936; //31 years = 271560 hours, round to 270000
double lifeExp = 713064; //81.4 years = 713064 hours
double hoursLeft = lifeExp - age;
double pct = (age / lifeExp) * 100;
//Time monitors

unsigned long intervalMillis1 = 10000; // number of millisecs between updating "age"
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
  delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Please" );
  display.setCursor(0, 20);
  display.print("wait." );
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Please" );
  display.setCursor(0, 20);
  display.print("wait.." );
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Please" );
  display.setCursor(0, 20);
  display.print("wait..." );
  display.display();
  delay(500);
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("EXIST" );
  display.setCursor(0, 20);
  display.print("-ENTIAL" );
  display.setCursor(0, 40);
  display.print("CLOCK v2");
  display.display();
  delay(1500);
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
    display.setCursor(0, 0);
    display.print("EXIST" );
    display.setCursor(0, 20);
    display.print("-ENTIAL" );
    display.setCursor(0, 40);
    display.print("CLOCK v2");
  }
  else if (flag == 1) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("Pct Lived");
    display.setCursor(10, 32);
    display.print(pct, 5);
    display.print("%");

  }
  else if (flag == 2) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("HoursLived");
    display.setCursor(10, 32);
    display.print(age, 0);

  }
  else {
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0, 0);
    display.print("HoursLeft");
    display.setCursor(10, 32);
    display.print(hoursLeft, 0);

  }

  //Serial debug output
  Serial.print("flag:  ");
  Serial.print(flag);
  Serial.print("  age:  ");
  Serial.print(age, 0);
  Serial.print("  lifeExp:  ");
  Serial.print(lifeExp, 0);
  Serial.print("  hoursLeft:  ");
  Serial.print(hoursLeft, 0);
  Serial.print("  pct:  ");
  Serial.print(pct, 6);
  Serial.println("%");
}

void updateAge() {
  // Clear the display
  //display.clearDisplay();
  //Set the color - always use white despite actual display color
  //display.setTextColor(WHITE);
  //Set the font size
  //display.setTextSize(2);

  //Set the cursor coordinates
  //display.setCursor(0, 0);
  //display.print("EXISTENTIAL CLOCK v2");
  //display.setCursor(10, 0);
  //display.print("time: ");
  //display.setCursor(0, 16);
  //display.print(hoursLeft, 0);
  //display.setCursor(0, 32);
  //display.print("Pct Lived");
  //display.setCursor(10, 32);
  //display.print(pct, 5);
  //display.print("%");

  //Serial debug output
  Serial.print("flag:  ");
  Serial.print(flag);
  Serial.print("age:  ");
  Serial.print(age, 0);
  Serial.print("  lifeExp:  ");
  Serial.print(lifeExp, 0);
  Serial.print("  hoursLeft:  ");
  Serial.print(hoursLeft, 0);
  Serial.print("  pct:  ");
  Serial.print(pct, 6);
  Serial.println("%");
}
void loop() {

  currentMillis1 = millis();   //check the time
  currentMillis2 = millis();


  if (currentMillis2 - previousMillis2 >= intervalMillis2) {
    previousMillis2 += intervalMillis2;
    flag = flag + 1;
    if (flag == 4) {
      flag = 0;
    }
    updateAge();
    updateDisplay();
    display.display();

  }

  if (currentMillis1 - previousMillis1 >= intervalMillis1) {
    age = age + 1;
    hoursLeft = lifeExp - age;
    pct = (age / lifeExp) * 100;
    previousMillis1 += intervalMillis1;
    updateAge();
    display.display();

  }
}
