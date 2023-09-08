#include <LiquidCrystal.h>
int GREEN_1 = 13, YELLOW_1 = 12, RED_1 = 11;
int GREEN_2 = 10, YELLOW_2 = 9, RED_2 = 8;
int DELAY_GREEN = 5000, DELAY_YELLOW = 2000, DELAY_RED = 5000;
int potentiometerPin = A3;
int MegaVoltagePin = A15;
float voltagePotentiometer;
LiquidCrystal lcd(37, 36, 35, 34, 33, 32);
 
void setup() {
  pinMode(GREEN_1, OUTPUT);
  pinMode(YELLOW_1, OUTPUT);
  pinMode(RED_1, OUTPUT);
  pinMode(GREEN_2, OUTPUT);
  pinMode(YELLOW_2, OUTPUT);
  pinMode(RED_2, OUTPUT);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("Hello light!!!");
}
 
void green_light_1() {
  digitalWrite(GREEN_1, HIGH);
  digitalWrite(YELLOW_1, LOW);
  digitalWrite(RED_1, LOW);
}
 
void yellow_light_1() {
  digitalWrite(GREEN_1, LOW);
  digitalWrite(YELLOW_1, HIGH);
  digitalWrite(RED_1, LOW);
}
 
void red_light_1() {
  digitalWrite(GREEN_1, LOW);
  digitalWrite(YELLOW_1, LOW);
  digitalWrite(RED_1, HIGH);
}
 
void green_light_2() {
  digitalWrite(GREEN_2, HIGH);
  digitalWrite(YELLOW_2, LOW);
  digitalWrite(RED_2, LOW);
}
 
void yellow_light_2() {
  digitalWrite(GREEN_2, LOW);
  digitalWrite(YELLOW_2, HIGH);
  digitalWrite(RED_2, LOW);
}
 
void red_light_2() {
  digitalWrite(GREEN_2, LOW);
  digitalWrite(YELLOW_2, LOW);
  digitalWrite(RED_2, HIGH);
}
 
void loop() {
  int sensorValue = analogRead(potentiometerPin);
  voltagePotentiometer = (sensorValue / 1023.0) * 5.0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pot.meter: ");
  lcd.print(voltagePotentiometer, 2);
 
  float voltage3_3 = analogRead(MegaVoltagePin) * (5.0 / 1023.0);
  lcd.setCursor(0, 2);
  lcd.print("3.3_level: ");
  lcd.print(voltage3_3, 1);
 
  green_light_1();
  red_light_2();
  delay(DELAY_GREEN);
 
  yellow_light_1();
  yellow_light_2();
  delay(DELAY_YELLOW);
 
  green_light_2();
  red_light_1();
  delay(DELAY_RED);
}
 