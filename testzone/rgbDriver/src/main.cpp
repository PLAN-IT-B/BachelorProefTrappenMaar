//fastled en neopixel


#include <Arduino.h>
#define PIN_RED1    32 // GIOP23
#define PIN_RED2    33
#define PIN_GREEN1  27 // GIOP22
#define PIN_GREEN2  14
#define PIN_YELLOW1 25
#define PIN_YELLOW2 26
boolean oplopen = true;
boolean groen = false;
int score = 0;
int PWM_frequency = 1000;
int PWM_CHANNEL = 0;
int PWM_RESOLUTION = 8;
int GPIOPIN = 12;
int dutyCycle = 127;

//void schakelGroen(int tijd);
//void schakelRood(int tijd);
//void schakelGeel(int tijd);

void setup() {
  pinMode(PIN_RED1,OUTPUT);
  pinMode(PIN_RED2,OUTPUT);
  pinMode(PIN_GREEN1,OUTPUT);
  pinMode(PIN_GREEN2,OUTPUT);
  pinMode(PIN_YELLOW1,OUTPUT);
  pinMode(PIN_YELLOW2,OUTPUT);
  ledcSetup(PWM_CHANNEL, PWM_frequency, PWM_RESOLUTION);
  ledcAttachPin(GPIOPIN, PWM_CHANNEL);
  digitalWrite(PIN_RED1, LOW);digitalWrite(PIN_RED2, LOW);digitalWrite(PIN_GREEN1, LOW);
  digitalWrite(PIN_GREEN2, LOW);digitalWrite(PIN_YELLOW1, LOW);digitalWrite(PIN_YELLOW2, LOW);
}

void loop() {
  
int time = 500;
  if(score==0){
    digitalWrite(PIN_RED1, LOW);digitalWrite(PIN_RED2, LOW);digitalWrite(PIN_GREEN1, LOW);
    digitalWrite(PIN_GREEN2, LOW);digitalWrite(PIN_YELLOW1, LOW);digitalWrite(PIN_YELLOW2, LOW);
    ledcWrite(PWM_CHANNEL, 0);
  } //rood1
  else if(score==1){
    digitalWrite(PIN_RED1, HIGH);digitalWrite(PIN_RED2, LOW);digitalWrite(PIN_GREEN1, LOW);
    digitalWrite(PIN_GREEN2, LOW);digitalWrite(PIN_YELLOW1, LOW);digitalWrite(PIN_YELLOW2, LOW);
    ledcWrite(PWM_CHANNEL, 0);
  } //rood
  else if(score==2){
    digitalWrite(PIN_RED1, HIGH);digitalWrite(PIN_RED2, HIGH);digitalWrite(PIN_GREEN1, LOW);
    digitalWrite(PIN_GREEN2, LOW);digitalWrite(PIN_YELLOW1, LOW);digitalWrite(PIN_YELLOW2, LOW);
    ledcWrite(PWM_CHANNEL, 0);
  } //rood en geel1
  else if(score==3){
    digitalWrite(PIN_RED1, HIGH);digitalWrite(PIN_RED2, HIGH);digitalWrite(PIN_GREEN1, LOW);
    digitalWrite(PIN_GREEN2, LOW);//digitalWrite(PIN_YELLOW1, HIGH);digitalWrite(PIN_YELLOW2, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);/*
    int i = time;
    while(i>0){
    if(groen){
      digitalWrite(PIN_YELLOW1, HIGH);
    }
    else{
      digitalWrite(PIN_YELLOW1, LOW);
    }
    groen = !groen;
    delay(5);
    i-=5;
  }  */
  } //rood en geel
  else if(score==4){
    digitalWrite(PIN_RED1, HIGH);digitalWrite(PIN_RED2, HIGH);digitalWrite(PIN_GREEN1, LOW);
    digitalWrite(PIN_GREEN2, LOW);digitalWrite(PIN_YELLOW1, HIGH);digitalWrite(PIN_YELLOW2, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
  } //rood, geel en groen1
  else if(score==5){
    digitalWrite(PIN_RED1, HIGH);digitalWrite(PIN_RED2, HIGH);digitalWrite(PIN_GREEN1, HIGH);
    digitalWrite(PIN_GREEN2, LOW);digitalWrite(PIN_YELLOW1, HIGH);digitalWrite(PIN_YELLOW2, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  else{ //rood, geel en groen
    digitalWrite(PIN_RED1, HIGH);digitalWrite(PIN_RED2, HIGH);digitalWrite(PIN_GREEN1, HIGH);
    digitalWrite(PIN_GREEN2, HIGH);digitalWrite(PIN_YELLOW1, HIGH);digitalWrite(PIN_YELLOW2, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
  }
  if(oplopen && (score<6)){
    score++;
  }
  else if(oplopen && score==6){
    oplopen = false;
  }
  else if(!oplopen && score > 0){
    score--;
  }
  else oplopen = true;
  
  delay(500);
  //aflopen
}


/*
void schakelGroen(int tijd){
  digitalWrite(PIN_RED, LOW);
  digitalWrite(PIN_GREEN, HIGH);
  delay(tijd);
}

void schakelRood(int tijd){
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_GREEN, LOW);
  delay(tijd);
}

void schakelGeel(int tijd){
  int i = tijd;
  while(i>0){
    digitalWrite(PIN_RED, HIGH);
    if(groen){
      digitalWrite(PIN_GREEN, HIGH);
    }
    else{
      digitalWrite(PIN_GREEN, LOW);
    }
    groen = !groen;
    delay(5);
    i-=5;
  }  
}*/