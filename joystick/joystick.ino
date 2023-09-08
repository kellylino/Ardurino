#include <LiquidCrystal.h>
const int Xpin = A0, Ypin = A1;
int joystickButtonPin = 19;
volatile boolean buttonPressed = false;
LiquidCrystal lcd(37, 36, 35, 34, 33, 32);

void setup() {
  lcd.begin(20, 4);
  pinMode(Xpin, INPUT);
  pinMode(joystickButtonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(joystickButtonPin), buttonhPressedISR, FALLING);
}

void loop() {
  int Xval = analogRead(Xpin);
  int Xpercentage = round(((float)Xval - 512) / 511.0 * 100.0);
  int lcdPos = map(Xpercentage, -100, 100, 0, 19);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("X-position");
  lcd.setCursor(0, 1);
  lcd.print("-100%");
  lcd.setCursor(8, 1);
  lcd.print(Xpercentage);
  lcd.print("%");
  lcd.setCursor(14, 1);
  lcd.print("+100%");


  lcd.setCursor(lcdPos, 2);
  lcd.print("I");

  if (buttonPressed) {
    lcd.setCursor(0, 3);
    lcd.print("Pressed!");
    buttonPressed = false; 
  }

  delay(300);
}

void buttonhPressedISR() {
  buttonPressed = true;
}