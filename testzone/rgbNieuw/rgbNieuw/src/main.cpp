#include <Arduino.h>

#define yellow1 33
#define yellow2 25
#define yellow3 26
#define yellow4 27
#define yellow5 14
#define yellow6 12

#define rood1 23
#define rood2 22
#define rood3 21
#define rood4 19
#define rood5 18

#define groen1 5
#define groen2 17
#define groen3 16
#define groen4 4
#define groen5 13


int dutyPin = 32; //Dit is de pin die de dutycycle zal genereren

int PWM_frequency = 1000;
int PWM_CHANNEL = 0;
int PWM_RESOLUTION = 8;
int dutyCycle = 127;
int interval =1;
int score = 16*interval;
boolean oplopen = true;

void setOff();

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
void setOff(){
  digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(rood1, LOW);digitalWrite(rood2, LOW);digitalWrite(rood3, LOW); digitalWrite(rood4, LOW);digitalWrite(rood5, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);


}
void loop() {
  
  if(score==0){
    //niets
    digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW);
    digitalWrite(green, LOW);digitalWrite(red, LOW);
    ledcWrite(PWM_CHANNEL, 0);
  } 
    else if((0*interval<(score)) && ((score) <=1*interval)) {
    //rood1
    digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW);
    digitalWrite(green, LOW);digitalWrite(red, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
  }
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
  /*if(oplopen && (score<3)){
    score++;
  }
  else if(oplopen && score==4){
    oplopen = false;
  }
  else if(!oplopen && score > 1){
    score--;
  }
  else oplopen = true;*/
  
  delay(1000);
  //aflopen
}