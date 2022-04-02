#include <Arduino.h>
byte pin[] = {22,23,4,5,18,19,21};
const byte count[4] = {
  B00000110,
  B01011011,
  B01001111,
  B01100110,
};

static void SevenSeg(byte Bit);

void setup() {
  // put your setup code here, to run once:
  pinMode(pin[0], OUTPUT);
  pinMode(pin[1], OUTPUT);
  pinMode(pin[2], OUTPUT);
  pinMode(pin[3], OUTPUT);
  pinMode(pin[4], OUTPUT);
  pinMode(pin[5], OUTPUT);
  pinMode(pin[6], OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<4; i++){
    SevenSeg(count[i]);
    delay(5000);
  }
}

void SevenSeg(byte Bit){
  for(int i=0; i<7; i++){
    digitalWrite(pin[i], bitRead(Bit, i));
  }
}