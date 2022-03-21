//fastled en neopixel


#include <Arduino.h>
#define PIN_RED    25 // GIOP23
#define PIN_GREEN  33 // GIOP22
#define PIN_BLUE   32 // GIOP21
boolean schakelGroen = false;

void setup() {
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);

  for (int i=0; i<3; i++){
    digitalWrite(PIN_RED, HIGH);
    digitalWrite(BUILTIN_LED, HIGH);
    delay(300);
    digitalWrite(PIN_RED, LOW);
    digitalWrite(BUILTIN_LED, LOW);
    delay(300);
  }
}

void loop() {
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_BLUE, LOW);
  if(schakelGroen){
    digitalWrite(PIN_GREEN, HIGH);
  }
  else{
    digitalWrite(PIN_GREEN, LOW);
  }
  schakelGroen = !schakelGroen;
  delay(5);
}