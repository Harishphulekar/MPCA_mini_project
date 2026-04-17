#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

Servo feederServo;

// Pins
#define IR_PIN 2
#define TRIG_PIN 3
#define ECHO_PIN 4
#define SERVO_PIN 9
#define LDR_PIN 7
#define LED_PIN 8

// Feeding time
int feedHour = 17;
int feedMinute = 39;

bool fed = false;

// -------- Ultrasonic --------
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2;
}

// -------- Feeding --------
void feedPet() {
  lcd.clear();
  lcd.print("Feeding...");

  feederServo.write(90);
  delay(3000);

  feederServo.write(0);

  lcd.clear();
  lcd.print("Done!");
  delay(2000);
}

void setup() {
  Serial.begin(9600);

  pinMode(IR_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  feederServo.attach(SERVO_PIN);
  feederServo.write(0);

  lcd.init();
  lcd.backlight();

  if (!rtc.begin()) {
    lcd.print("RTC Error");
    while (1);
  }

  lcd.print("System Ready");
  delay(2000);
  lcd.clear();
}

void loop() {

  DateTime now = rtc.now();

  // -------- LDR (Light Control) --------
  int lightState = digitalRead(LDR_PIN);
  digitalWrite(LED_PIN, lightState == HIGH ? HIGH : LOW);

  // -------- IR (ACTIVE LOW FIXED) --------
  int petPresent = !digitalRead(IR_PIN);

  // -------- Ultrasonic --------
  long distance = getDistance();
  int foodPercent = ((12.5 - distance) * 100) / (12.5 - 2);

  if (foodPercent > 100) foodPercent = 100;
  if (foodPercent < 0) foodPercent = 0;

  // -------- LCD Display --------
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(now.hour());
  lcd.print(":");
  lcd.print(now.minute());

  lcd.print(" F:");
  lcd.print(foodPercent);
  lcd.print("% ");

  lcd.setCursor(0, 1);
  lcd.print("P:");
  lcd.print(petPresent ? "Y" : "N");

  // -------- FEEDING LOGIC --------
  if (now.hour() == feedHour && now.minute() == feedMinute && !fed) {

    lcd.clear();
    lcd.print("Feeding Time");
    delay(1000);

    // -------- IF PET PRESENT --------
    if (petPresent) {

      lcd.clear();
      lcd.print("Pet Detected");
      delay(1000);

      feedPet();   // instant feeding

    } 
    // -------- IF PET NOT PRESENT --------
    else {

      lcd.clear();
      lcd.print("Waiting Pet...");
      delay(1000);

      unsigned long startTime = millis();
      bool petDetected = false;

      while (millis() - startTime < 10000) {

        if (!digitalRead(IR_PIN)) {   // active LOW
          petDetected = true;
          break;
        }

        delay(200);
      }

      lcd.clear();

      if (petDetected) {
        lcd.print("Pet Arrived");
      } else {
        lcd.print("No Pet-Feed");
      }

      delay(1500);

      feedPet();   // feed anyway
    }

    fed = true;
  }

  // -------- Reset next day --------
  if (now.hour() == 0 && now.minute() == 0) {
    fed = false;
  }

  delay(500);
}
