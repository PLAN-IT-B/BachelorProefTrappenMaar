#include <Arduino.h>
#include <LiquidCrystal.h>

uint8_t reedSwitch = 2;
uint8_t radius = 0.2;
uint8_t circumference;
uint8_t totaltime;
uint8_t speed;
uint8_t timer;

const uint8_t rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 6;   // Declaring pins for LCD Display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void isr(){
  timer++;
  delayMicroseconds(9600);
}

void setup() {
  Serial.begin(115200);

  lcd.begin(16,2);
  lcd.setCursor(6,0);
  lcd.print("speed");  

  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);

  pinMode(reedSwitch, INPUT_PULLUP);
  timer = 0;
  speed = 0;
  totaltime = 0;
  circumference = 6.28*radius;
}

void loop() {
  if(millis()-totaltime >= 1000){
    detachInterrupt(digitalPinToInterrupt(2));
    speed = (circumference/(millis()-totaltime)*timer);

    timer = 0;
    totaltime = millis();
    attachInterrupt(digitalPinToInterrupt(2), isr, RISING);
    
    lcd.setCursor(8,1);
    lcd.print(speed);
  }
}