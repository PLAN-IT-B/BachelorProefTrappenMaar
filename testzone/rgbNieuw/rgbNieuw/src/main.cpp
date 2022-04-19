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

void setup() {
  // put your setup code here, to run once:
  pinMode(rood1, OUTPUT);pinMode(rood2, OUTPUT); pinMode(rood3, OUTPUT); pinMode(rood4, OUTPUT); pinMode(rood5, OUTPUT);
  pinMode(yellow1, OUTPUT); pinMode(yellow2, OUTPUT);pinMode(yellow3, OUTPUT);pinMode(yellow4, OUTPUT);pinMode(yellow5, OUTPUT);pinMode(yellow6, OUTPUT);
  pinMode(groen1, OUTPUT);pinMode(groen2, OUTPUT);pinMode(groen3, OUTPUT);pinMode(groen4, OUTPUT);pinMode(groen5, OUTPUT); 

  ledcSetup(PWM_CHANNEL, PWM_frequency, PWM_RESOLUTION);
  ledcAttachPin(dutyPin, PWM_CHANNEL);
  digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW);
  ledcWrite(PWM_CHANNEL, 0);

  digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(rood1, LOW);digitalWrite(rood2, LOW);digitalWrite(rood3, LOW); digitalWrite(rood4, LOW);digitalWrite(rood5, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
}

void loop() {
  
  if(score==0){
  //niets
  digitalWrite(rood1, LOW);digitalWrite(rood2, LOW);digitalWrite(rood3, LOW); digitalWrite(rood4, LOW);digitalWrite(rood5, LOW);
  digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  } 
  else if((0*interval<(score)) && ((score) <=1*interval)) {
  //rood1
  digitalWrite(rood1, HIGH);digitalWrite(rood2, LOW);digitalWrite(rood3, LOW); digitalWrite(rood4, LOW);digitalWrite(rood5, LOW);
  digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((1*interval<(score)) && ((score) <=2*interval)) {
  //rood2
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, LOW); digitalWrite(rood4, LOW);digitalWrite(rood5, LOW);
  digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((2*interval<(score)) && ((score) <=3*interval)) {
  //rood3
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, LOW);digitalWrite(rood5, LOW);
  digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((3*interval<(score)) && ((score) <=4*interval)) {
 //rood4
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, LOW);
  digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((4*interval<(score)) && ((score) <=5*interval)) {
  //rood5
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((5*interval<(score)) && ((score) <=6*interval)) {
  //oranje1
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((6*interval<(score)) && ((score) <=7*interval)) {
  //oranje2
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((7*interval<(score)) && ((score) <=8*interval)) {
  //oranje3
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((8*interval<(score)) && ((score) <=9*interval)) {
  //oranje4
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((9*interval<(score)) && ((score) <=10*interval)) {
  //oranje5
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, LOW);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((10*interval<(score)) && ((score) <=11*interval)) {
  //oranje6
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
  digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((11*interval<(score)) && ((score) <=12*interval)) {
  //groen1
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
  digitalWrite(groen1, HIGH);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((12*interval<(score)) && ((score) <=13*interval)) {
  //groen2
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
  digitalWrite(groen1, HIGH);digitalWrite(groen2, HIGH);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((13*interval<(score)) && ((score) <=14*interval)) {
  //groen3
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
  digitalWrite(groen1, HIGH);digitalWrite(groen2, HIGH);digitalWrite(groen3, HIGH); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((14*interval<(score)) && ((score) <=15*interval)) {
  //groen4
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
  digitalWrite(groen1, HIGH);digitalWrite(groen2, HIGH);digitalWrite(groen3, HIGH); digitalWrite(groen4, HIGH);digitalWrite(groen5, LOW);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else if((15*interval<(score)) && ((score) <=16*interval)) {
  //groen5
  digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
  digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
  digitalWrite(groen1, HIGH);digitalWrite(groen2, HIGH);digitalWrite(groen3, HIGH); digitalWrite(groen4, HIGH);digitalWrite(groen5, HIGH);
  ledcWrite(PWM_CHANNEL, dutyCycle);
  }
}