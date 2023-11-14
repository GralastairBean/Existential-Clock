/*existentialClock_1
  Al Green 2021
  Uses a 20x4 I2C LCD to show your hours lived, hours to live and % of life
*/
#include <LiquidCrystal.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x20, 20, 4); // set the LCD address to 0x20 for a 20 chars and 4 line displa
double age = 289278; //33 years = 289278 hours
double lifeExp = 672440; //AUSTRALIAN 1989 Life expectancy = 76.71 years  = 672440 hours (1yr=365.2425 days)
double hoursLeft = lifeExp - age;
double pct = (age / lifeExp) * 100;
unsigned long intervalMillis = 3600000; // 1 hour = 3600000 ms = number of millisecs between updating "age"
unsigned long currentMillis = 0;    // stores the value of millis() in each iteration of loop()
unsigned long previousMillis = 0;   // will store last time "age" was updated

const int ledPin =  LED_BUILTIN;// the number of the LED pin
int ledState = LOW;             // ledState used to set the LED
unsigned long previousMillis_LED = 0;        // will store last time LED was updated
const long interval_LED = 1000;           // interval at which to blink (milliseconds)

void setup() {
  pinMode(ledPin, OUTPUT);
  lcd.init();                      // initialize the lcd
  lcd.backlight();                  // turn on the lcd backlight
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("EXISTENTIAL CLOCK V1");

  lcd.setCursor(0, 1);
  lcd.print("Age");
  lcd.setCursor(8, 1);
  lcd.print(age, 0);
  lcd.setCursor(14, 1);
  lcd.print(" hrs");

  lcd.setCursor(0, 2);
  lcd.print("Remain");
  lcd.setCursor(8, 2);
  lcd.print(hoursLeft, 0);
  lcd.setCursor(14, 2);
  lcd.print(" hrs");

  lcd.setCursor(0, 3);
  lcd.print("Life %");
  lcd.setCursor(8, 3);
  lcd.print(pct, 5);
  lcd.setCursor(17, 3);
  lcd.print("%");

  Serial.begin(9600);
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
  updateAge();  //call update age function

  if (age >= lifeExp) {
    Serial.println("***************");
    Serial.println("YOU ARE DEAD");
    Serial.println("***************");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("EXISTENTIAL CLOCK V1");
    lcd.setCursor(0, 1);
    lcd.print("********************");
    lcd.setCursor(0, 2);
    lcd.print("YOU ARE DEAD.....");
    lcd.setCursor(0, 3);
    lcd.print("********************");

    delay(10000000);

  }
}

void updateAge() {
  if (currentMillis - previousMillis >= intervalMillis) {
    age = age + 1;
    hoursLeft = lifeExp - age;
    pct = (age / lifeExp) * 100;
    previousMillis += intervalMillis;

    Serial.print("age:  ");
    Serial.print(age, 0);
    Serial.print("  lifeExp:  ");
    Serial.print(lifeExp, 0);
    Serial.print("  hoursLeft:  ");
    Serial.print(hoursLeft, 0);
    Serial.print("  pct:  ");
    Serial.print(pct, 7);
    Serial.println("%");

    lcd.clear();
    lcd.print("EXISTENTIAL CLOCK V1");
    lcd.setCursor(0, 1);
    lcd.print("Age");
    lcd.setCursor(8, 1);
    lcd.print(age, 0);
    lcd.setCursor(14, 1);
    lcd.print(" hrs");

    lcd.setCursor(0, 2);
    lcd.print("Remain");
    lcd.setCursor(8, 2);
    lcd.print(hoursLeft, 0);
    lcd.setCursor(14, 2);
    lcd.print(" hrs");

    lcd.setCursor(0, 3);
    lcd.print("Life %");
    lcd.setCursor(8, 3);
    lcd.print(pct, 5);
    lcd.setCursor(17, 3);
    lcd.print("%");
  }
  unsigned long currentMillis_LED = millis();
  if (currentMillis_LED - previousMillis_LED >= interval_LED) {
    // save the last time you blinked the LED
    previousMillis_LED = currentMillis_LED;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }

}
