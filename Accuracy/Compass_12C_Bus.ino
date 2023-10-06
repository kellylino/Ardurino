#include <Wire.h>
#define CMPS14_Address 0x60
#include <LiquidCrystal.h>
#include <TimerOne.h>
LiquidCrystal lcd(37, 36, 35, 34, 33, 32);
#define PPR 176
#define WHEEL_RADIUS_CM 2.1

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

int pulseCount = 0;

byte raw;

bool turn = false;

int turnCount = 0;

void setup() {
  Wire.begin();  // Initialize the I2C communication
  Serial.begin(9600);
  lcd.begin(20, 4);

  attachInterrupt(digitalPinToInterrupt(ENC_LEFT_B), encoderInterrupt, FALLING);

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

  // Request a single byte (8 bits) of data from the compass sensor
  Wire.beginTransmission(CMPS14_Address);
  Wire.write(1);
  Wire.endTransmission();

  // Read the data from the compass sensor
  Wire.requestFrom(CMPS14_Address, 1, true);
  if (Wire.available() >= 1) {
    raw = Wire.read();  // Read the 8-bit bearing value
    Serial.print("Raw Bearing Value: ");
    Serial.println(raw);
  }

  int pwm_R = 0;
  int pwm_L = 0;

  if (turnCount < 2) {
    if (!turn) {
      if (turnCount == 0 && pulseCount <= 500) {
        // Serial.println(pulseCount);
        // Serial.println(pulsesFor50cm);
        pwm_R = 255;
        pwm_L = 255;
        digitalWrite(Motor_R_dir_pin, Motor_return);
        digitalWrite(Motor_L_dir_pin, Motor_return);
      } else if (turnCount == 1 && pulseCount <= 660) {
        pwm_R = 255;
        pwm_L = 255;
        digitalWrite(Motor_R_dir_pin, Motor_return);
        digitalWrite(Motor_L_dir_pin, Motor_return);
      } else {
        // if (turnCount == 1) {
        //   pwm_R = 0;
        //   pwm_L = 0;
        // }
        turn = true;
      }
    } else {
      if (raw < 65 || raw > 240) {
        pwm_L = 255;
        digitalWrite(Motor_L_dir_pin, Motor_forward);
      } else if (raw = 65) {
        pwm_L = 0;
        pulseCount = 0;
        turn = false;
        turnCount++;
      }
    }
  }

  analogWrite(Motor_L_pwm_pin, pwm_L);
  analogWrite(Motor_R_pwm_pin, pwm_R);



}

void encoderInterrupt() {
  pulseCount++;
}
