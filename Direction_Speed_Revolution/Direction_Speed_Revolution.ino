#include <LiquidCrystal.h>
#include <TimerOne.h>
LiquidCrystal lcd(37, 36, 35, 34, 33, 32);
#define PPR 176
#define WHEEL_RADIUS_CM 2.0

#define JOY_X_PIN A0
#define JOY_Y_PIN A1
#define Motor_forward 0
#define Motor_return 1
#define Motor_L_dir_pin 8
#define Motor_R_dir_pin 7
#define Motor_L_pwm_pin 10
#define Motor_R_pwm_pin 9
#define ENC_RIGHT_A 23
#define ENC_RIGHT_B 2
#define ENC_LEFT_A 24
#define ENC_LEFT_B 3

int iL = 0, iR = 0, frequencyHzL, frequencyHzR;


void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);

  // Timer1.initialize(1000000);
  // Timer1.attachInterrupt(frequencyCal);


  attachInterrupt(digitalPinToInterrupt(ENC_LEFT_B), countENCBL, FALLING);
  attachInterrupt(digitalPinToInterrupt(ENC_RIGHT_B), countENCBR, FALLING);

  pinMode(Motor_L_dir_pin, OUTPUT);
  pinMode(Motor_R_dir_pin, OUTPUT);
  pinMode(Motor_L_pwm_pin, OUTPUT);
  pinMode(Motor_R_pwm_pin, OUTPUT);
  pinMode(ENC_RIGHT_A, INPUT);
  pinMode(ENC_RIGHT_B, INPUT);
  pinMode(ENC_LEFT_A, INPUT);
  pinMode(ENC_LEFT_B, INPUT);
  pinMode(JOY_X_PIN, INPUT);
  pinMode(JOY_Y_PIN, INPUT);
}

void loop() {
  float pulsesPerRevolution = PPR;
  float wheelDistanceRevolution = 2.0 * PI * WHEEL_RADIUS_CM;
  float pulsesFor50cm = (50.0 / wheelDistanceRevolution) * pulsesPerRevolution;
  float pulsesFor1cm = (1.0 / wheelDistanceRevolution) * pulsesPerRevolution;
  lcd.setCursor(0, 0);
  lcd.print("Pulses Left: ");
  lcd.setCursor(15, 0);
  lcd.print(iL);

  lcd.setCursor(0, 1);
  lcd.print("one round(cm): ");
  lcd.setCursor(15, 1);
  lcd.print(wheelDistanceRevolution);

  lcd.setCursor(0, 2);
  lcd.print("pulsesFor50cm: ");
  lcd.setCursor(15, 2);
  lcd.print(pulsesFor50cm);

   lcd.setCursor(0, 3);
  lcd.print("pulsesFor1cm: ");
  lcd.setCursor(15, 3);
  lcd.print(pulsesFor1cm);




  

  // delay(100);

  int joyX = analogRead(JOY_X_PIN);
  int joyY = analogRead(JOY_Y_PIN);
  int pwm_R = 0;
  int pwm_L = 0;

  if (joyY > 600) {
    pwm_R = map(joyY, 600, 1023, 0, 255);
    pwm_L = map(joyY, 600, 1023, 0, 255);
    digitalWrite(Motor_R_dir_pin, Motor_return);
    digitalWrite(Motor_L_dir_pin, Motor_return);
  } else if (joyY < 400) {
    pwm_R = map(joyY, 400, 0, 0, 255);
    pwm_L = map(joyY, 400, 0, 0, 255);
    digitalWrite(Motor_R_dir_pin, Motor_forward);
    digitalWrite(Motor_L_dir_pin, Motor_forward);
  }

  if (joyX > 600) {
    pwm_L = map(joyX, 600, 1023, 0, 255);
    digitalWrite(Motor_L_dir_pin, Motor_forward);
  } else if (joyX < 400) {
    pwm_R = map(joyX, 400, 0, 0, 255);
    digitalWrite(Motor_R_dir_pin, Motor_forward);
  }

  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);
}



// void frequencyCal() {
//   frequencyHzL = iL;
//   frequencyHzR = iR;
//   Serial.println("Pulse per second:");
//   Serial.println("ENCB left:");
//   Serial.println(frequencyHzL);
//   Serial.println("ENCB right:");
//   Serial.println(frequencyHzR);
//   iL = 0;
//   iR = 0;
// }


//PWM counting function
void countENCBL() {
  iL++;
}
void countENCBR() {
  iR++;
}

// void encoderInterrupt() {
//   pulseCount++;
// }