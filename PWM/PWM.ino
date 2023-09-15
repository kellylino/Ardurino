const int potPin1 = A0; 
const int potPin2 = A1; 
const int ledPin1 = 9;
const int ledPin2 = 10; 
int joystickButtonPin = 19;
boolean ledsOn = false;

void setup() {
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(joystickButtonPin, INPUT_PULLUP);
  //using interrupts, turns the leds entirely on and off
  attachInterrupt(digitalPinToInterrupt(joystickButtonPin), buttonhPressedISR, FALLING);
}

void loop() {
  //uses the analog values read from two potentiometers to change the brightness of two leds 
  int potValue1 = analogRead(potPin1);
  int potValue2 = analogRead(potPin2);

  int brightness1 = map(potValue1, 0, 1023, 0, 255);
  int brightness2 = map(potValue2, 0, 1023, 0, 255);

  analogWrite(ledPin1, brightness1);
  analogWrite(ledPin2, brightness2);

  //Use a boolean variable that determines if the leds are on or off
  if (ledsOn) {
    analogWrite(ledPin1, 1023);
    analogWrite(ledPin2, 1023);
  } else {
    analogWrite(ledPin1, 0); // Turn off LED 1
    analogWrite(ledPin2, 0); // Turn off LED 2
  }
}

void buttonhPressedISR() {
  ledsOn = !ledsOn;
}