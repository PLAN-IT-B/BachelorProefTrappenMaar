#include <Arduino.h>

#define yellow1 33
#define yellow2 25
#define yellow3 27
int dutyPin = 32; //Dit is de pin die de dutycycle zal genereren
#define green 5 // niet belangrijk
#define red 23  // niet belangrijk
int PWM_frequency = 1000;
int PWM_CHANNEL = 0;
int PWM_RESOLUTION = 8;
int dutyCycle = 127;
int score = 1;
boolean oplopen = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(yellow1, OUTPUT); pinMode(yellow2, OUTPUT);
  pinMode(yellow3, OUTPUT); pinMode(green, OUTPUT); pinMode(red, OUTPUT);
  ledcSetup(PWM_CHANNEL, PWM_frequency, PWM_RESOLUTION);
  ledcAttachPin(dutyPin, PWM_CHANNEL);
  digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW);
  digitalWrite(green, LOW);digitalWrite(red, LOW);
  ledcWrite(PWM_CHANNEL, 0);
}

void loop() {
  
  if(score==0){
    digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW);
    digitalWrite(green, LOW);digitalWrite(red, LOW);
    ledcWrite(PWM_CHANNEL, 0);
  } //rood1
  else if(score==1){
    digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW);
    digitalWrite(green, LOW);digitalWrite(red, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
  } //rood
  else if(score==2){
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW);
    digitalWrite(green, LOW);digitalWrite(red, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
  } //rood en geel1
  else if(score==3){
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, LOW);
    digitalWrite(green, LOW);digitalWrite(red, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
  } //rood en geel
  else if(score==4){
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH);
    digitalWrite(green, HIGH);digitalWrite(red, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
  } //rood, geel en groen1
  else if(score==5){
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH);
    digitalWrite(green, HIGH);digitalWrite(red, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else{ //rood, geel en groen
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH);
    digitalWrite(green, HIGH);digitalWrite(red, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  if(oplopen && (score<3)){
    score++;
  }
  else if(oplopen && score==4){
    oplopen = false;
  }
  else if(!oplopen && score > 1){
    score--;
  }
  else oplopen = true;
  
  delay(500);
  //aflopen
}