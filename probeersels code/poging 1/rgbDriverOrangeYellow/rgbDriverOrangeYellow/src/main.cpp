#include <Arduino.h>
#define PIN_RED1    32 // GIOP23
#define PIN_RED2    33
#define PIN_RED3 25
#define PIN_GREEN1  26 // GIOP22
#define PIN_GREEN2  14
#define PIN_GREEN3  12
//#define PIN_YELLOW2 26
boolean oplopen = true;
boolean groen = false;
int score = 0;
int PWM_frequency1 = 1000;
int PWM_CHANNEL1 = 0;
int PWM_RESOLUTION1 = 8;
int GPIOPIN1 = 27;
int dutyCycle1 = 125;

void setupLEDS();

void setup() {
  setupLEDS();
}

void loop() {
  if(score==0){
    digitalWrite(PIN_RED1, LOW); digitalWrite(PIN_RED2, LOW); digitalWrite(PIN_RED3, LOW);
    digitalWrite(PIN_GREEN1, LOW); digitalWrite(PIN_GREEN2, LOW); digitalWrite(PIN_GREEN3, LOW);
  } //rood1
  else if(score==1){
    digitalWrite(PIN_RED1, HIGH); digitalWrite(PIN_RED2, LOW); digitalWrite(PIN_RED3, LOW);
    digitalWrite(PIN_GREEN1, HIGH); digitalWrite(PIN_GREEN2, LOW); digitalWrite(PIN_GREEN3, LOW);
  } //rood
  else if(score==2){
    digitalWrite(PIN_RED1, HIGH); digitalWrite(PIN_RED2, HIGH); digitalWrite(PIN_RED3, LOW);
    digitalWrite(PIN_GREEN1, HIGH); digitalWrite(PIN_GREEN2, HIGH); digitalWrite(PIN_GREEN3, LOW);
  } //rood en geel1
  else if(score==3){
    digitalWrite(PIN_RED1, HIGH); digitalWrite(PIN_RED2, HIGH); digitalWrite(PIN_RED3, HIGH);
    digitalWrite(PIN_GREEN1, HIGH); digitalWrite(PIN_GREEN2, HIGH); digitalWrite(PIN_GREEN3, HIGH);
  } //rood en geel
  
  if(oplopen && (score<3)){
    score++;
  }
  else if(oplopen && score==3){
    oplopen = false;
  }
  else if(!oplopen && score > 0){
    score--;
  }
  else oplopen = true;
  delay(500);
  //aflopen
}

void setupLEDS(){
  pinMode(PIN_RED1,OUTPUT);pinMode(PIN_RED2,OUTPUT);pinMode(PIN_RED3,OUTPUT);
  pinMode(PIN_GREEN1,OUTPUT);pinMode(PIN_GREEN2,OUTPUT);pinMode(PIN_GREEN3,OUTPUT);
  ledcSetup(PWM_CHANNEL1, PWM_frequency1, PWM_RESOLUTION1);
  ledcAttachPin(GPIOPIN1, PWM_CHANNEL1);
  digitalWrite(PIN_RED1, LOW);digitalWrite(PIN_RED2, LOW);digitalWrite(PIN_RED3, LOW);
  ledcWrite(PWM_CHANNEL1, dutyCycle1);digitalWrite(PIN_GREEN1,0);digitalWrite(PIN_GREEN2, LOW); digitalWrite(PIN_GREEN3, HIGH);
}