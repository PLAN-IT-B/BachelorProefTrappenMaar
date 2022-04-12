#include <Arduino.h>

#define yellow 33
int dutyPin = 32; //Dit is de pin die de dutycycle zal genereren
int PWM_frequency = 1000;
int PWM_CHANNEL = 0;
int PWM_RESOLUTION = 8;
int dutyCycle = 127;

void setup() {
  // put your setup code here, to run once:
  pinMode(yellow, OUTPUT);
  ledcSetup(PWM_CHANNEL, PWM_frequency, PWM_RESOLUTION);
  ledcAttachPin(dutyPin, PWM_CHANNEL);
  digitalWrite(yellow, LOW);
  ledcWrite(PWM_CHANNEL, 0);
}

void loop() {

  ledcWrite(PWM_CHANNEL, dutyCycle); digitalWrite(yellow, HIGH);
  delay(1000);
  ledcWrite(PWM_CHANNEL, 0); digitalWrite(yellow, LOW);
  delay(500);
}