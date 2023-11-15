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

// Heartbeat LED Setup
const int ledPin = 9;              // This must be a PWM pin.
// Assuming that a led update of 25 Hz is fast enough, then the interval is 40 ms.
unsigned long previousMillis_LED;
const unsigned long interval_LED = 40; // update interval
float x = -0.5;                    // from -0.5 to 0.5

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

  if( currentMillis_LED - previousMillis_LED >= interval_LED)
  {
    previousMillis_LED = currentMillis_LED;

    // The standard deviation is:
    //    y = e ^ ( -0.5 * x * x )
    // This sketch uses:
    //    y = expf ( -s * squaref ( x ) )
    //
    // The brightness to the human eye is close to a logarithmic scale with base 10.
    // Since an exponential curve is used, it is already a nice pulse.

    const float s1 = 150.0;        // steepness first pulse (recommend 150.0)
    const float s2 = 400.0;        // steepness second pulse (recommend 400.0)
    const float d = 0.13;          // distance between the pulses (recommend 0.13)
    const float f = 0.7;           // frequency of heartbeat in Hz (recomend 0.6)
    const float a = 200.0;         // amplitude of brightness (recommend 200.0)

    // Set lowest value to 1, so the led does not go completely off
    float y = 0.0;

    // First pulse.
    y += a * expf( -s1 * squaref( x + d));

    // Second pulse at lower brightness.
    y += a * expf( -s2 * squaref( x - d)) * 0.30;

    // The total value of y should not be above 255.
    analogWrite( ledPin, int( y));

    x += f * float( interval_LED) / 1000.0;  // divide interval by 1000 because it is in milliseconds
    if( x >= 0.5)
      x -= 1.0;
  }

}
