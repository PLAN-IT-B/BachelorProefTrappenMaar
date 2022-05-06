#include "WiFi.h"
#include "PubSubClient.h" //pio lib install "knolleary/PubSubClient"
#include <Arduino.h>

#define SSID "NETGEAR68"
#define PWD "excitedtuba713"

#define MQTT_SERVER "192.168.1.2"
#define MQTT_PORT 1883

#define ONBOARD_LED  2

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
int Maxscore = 16*interval;
boolean oplopen = true;

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

int fiveSeconds =0;
int bufferValue=0;
String messageTemp = "newNumber";
bool messageReceived = true;

char cstr[16];

void callback(char *topic, byte *message, unsigned int length);
void sendTo7Segment (int eps, char* cstr);
void checkMessage(String mess);
void control(String message);
void setBuffer();
int aantalReady = 0;


void setup_wifi()
{
  delay(10);
  Serial.println("Connecting to WiFi..");

  WiFi.begin(SSID, PWD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  pinMode(ONBOARD_LED,OUTPUT);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  //setup ledstrip buffer
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

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  for (int i = 0; i < length; i++)
  {
    //Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  //Serial.println();
  messageReceived = true;
}


void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // creat unique client ID
    // in Mosquitto broker enable anom. access
    if (client.connect("buffer"))
    {
      Serial.println("connected");
      // Subscribe
      // client.subscribe("input/#");
      client.subscribe("TrappenMaar/buffer");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void sendTo7Segment(int randomEsp, char* cstr){
  Serial.print("probeer");
  Serial.println(cstr);
  if(randomEsp == 1) {
    Serial.println("message send to segment1");
    client.publish("TrappenMaar/segment1", cstr);
    cstr="";  
    }
    

  else if (randomEsp ==2){
    Serial.println("message send to segment2");
    client.publish("TrappenMaar/segment2", cstr);
    cstr="";
  }

  else if (randomEsp ==3){
    client.publish("TrappenMaar/segment3", cstr);
  }
  
  else if (randomEsp ==4){
    client.publish("TrappenMaar/segment4", cstr);
  }

}


void control(String mess){
  //checken of 'newNumber': w gezonden dr segment wnn 7segment klaar is
 Serial.println("CONTROL IS OKE");
 
 if(mess == "newNumber"){
    Serial.println("MESSAGE: newNumber ARRIVED");
    //OORSPRONKELIJK TUSSEN 1 EN 5
    int randomGetal = random(1,5);
    itoa(randomGetal,cstr,10);
    //OORSPRONKELIJK TUSSEN 1 EN 5
    int randomEsp = random(1,5); //getal 1,2, 3 of 4
    Serial.println("randomESP");
    Serial.print("esp: ");
    Serial.print(randomEsp);
    Serial.print("nummer: ");
    Serial.print(randomGetal);
    sendTo7Segment(randomEsp, cstr);
  }

  //checken of level doorgestuurd werd door fiets
  else if((mess == "0")||(mess == "1")||(mess == "2")||(mess == "3")||(mess == "4")){
        Serial.println("MESSAGE: level ARRIVED");
        Serial.print("level: ");
        Serial.println(mess);
        Serial.print("score: ");
        checkMessage(mess);
        Serial.println(bufferValue);
    }
/*
  else if(mess == "grote fout"){
    if(bufferValue!=0){
    bufferValue -=2;}
    else{
      Serial.println("BUFFER IS LEEG");
    }
  }
  
  else if(mess == "kleine fout"){
    if(bufferValue!=0){
    bufferValue -=1;}
    else{
      Serial.println("BUFFER IS LEEG");
    }
  }
*/

  else if(mess == "reset"){
      client.publish("TrappenMaar/segment1","resetSegment1");
      client.publish("TrappenMaar/segment2","resetSegment2");
      client.publish("TrappenMaar/segment3","resetSegment3");
      client.publish("TrappenMaar/segment4","resetSegment4");

      client.publish("TrappenMaar/fiets","resetFiets");

  }

   else if((mess == "Fiets ready")||(mess == "Segment1 ready")||(mess == "Segment2 ready")||(mess == "Segment3 ready")||(mess == "Segment4 ready")){
    aantalReady ++;
    if(aantalReady == 5){
      aantalReady = 0;
      Serial.println("Restarting in 10 seconds");
      delay(10000);
      ESP.restart();
      Serial.println("Buffer is ook ready");
      client.publish("controlpanel/reset", "TrappenMaar is ready");
    }
   }

  else{
    Serial.println("MESSAGE: not for me");
    Serial.println(messageTemp);
  }
  
}

void checkMessage(String mess) {
  //Serial.println("bericht ontvangen");
  if(mess == cstr){
    bufferValue ++;
    client.publish("TrappenMaar/fiets", "correct");
  }
  else{
    client.publish("TrappenMaar/fiets", "false");
    Serial.println("FOUT GEFIETST, buffer stijgt niet");

  }
}

void setBuffer(){
  if(bufferValue==0){
    //niets
    Serial.println("geen kleuren");
    digitalWrite(rood1, LOW);digitalWrite(rood2, LOW);digitalWrite(rood3, LOW); digitalWrite(rood4, LOW);digitalWrite(rood5, LOW);
    digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    } 
    else if((0*interval<(bufferValue)) && ((bufferValue) <=1*interval)) {
    //rood1
    digitalWrite(rood1, HIGH);digitalWrite(rood2, LOW);digitalWrite(rood3, LOW); digitalWrite(rood4, LOW);digitalWrite(rood5, LOW);
    digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((1*interval<(bufferValue)) && ((bufferValue) <=2*interval)) {
    //rood2
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, LOW); digitalWrite(rood4, LOW);digitalWrite(rood5, LOW);
    digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((2*interval<(bufferValue)) && ((bufferValue) <=3*interval)) {
    //rood3
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, LOW);digitalWrite(rood5, LOW);
    digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((3*interval<(bufferValue)) && ((bufferValue) <=4*interval)) {
  //rood4
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, LOW);
    digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((4*interval<(bufferValue)) && ((bufferValue) <=5*interval)) {
    //rood5
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, LOW);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((5*interval<(bufferValue)) && ((bufferValue) <=6*interval)) {
    //oranje1
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, LOW);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((6*interval<(bufferValue)) && ((bufferValue) <=7*interval)) {
    //oranje2
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, LOW); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((7*interval<(bufferValue)) && ((bufferValue) <=8*interval)) {
    //oranje3
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, LOW);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((8*interval<(bufferValue)) && ((bufferValue) <=9*interval)) {
    //oranje4
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, LOW);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((9*interval<(bufferValue)) && ((bufferValue) <=10*interval)) {
    //oranje5
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, LOW);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((10*interval<(bufferValue)) && ((bufferValue) <=11*interval)) {
    //oranje6
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
    digitalWrite(groen1, LOW);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((11*interval<(bufferValue)) && ((bufferValue) <=12*interval)) {
    //groen1
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
    digitalWrite(groen1, HIGH);digitalWrite(groen2, LOW);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((12*interval<(bufferValue)) && ((bufferValue) <=13*interval)) {
    //groen2
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
    digitalWrite(groen1, HIGH);digitalWrite(groen2, HIGH);digitalWrite(groen3, LOW); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((13*interval<(bufferValue)) && ((bufferValue) <=14*interval)) {
    //groen3
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
    digitalWrite(groen1, HIGH);digitalWrite(groen2, HIGH);digitalWrite(groen3, HIGH); digitalWrite(groen4, LOW);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((14*interval<(bufferValue)) && ((bufferValue) <=15*interval)) {
    //groen4
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
    digitalWrite(groen1, HIGH);digitalWrite(groen2, HIGH);digitalWrite(groen3, HIGH); digitalWrite(groen4, HIGH);digitalWrite(groen5, LOW);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
    else if((15*interval<(bufferValue)) && ((bufferValue) <=16*interval)) {
    //groen5
    digitalWrite(rood1, HIGH);digitalWrite(rood2, HIGH);digitalWrite(rood3, HIGH); digitalWrite(rood4, HIGH);digitalWrite(rood5, HIGH);
    digitalWrite(yellow1, HIGH);digitalWrite(yellow2, HIGH);digitalWrite(yellow3, HIGH); digitalWrite(yellow4, HIGH);digitalWrite(yellow5, HIGH);digitalWrite(yellow6, HIGH);
    digitalWrite(groen1, HIGH);digitalWrite(groen2, HIGH);digitalWrite(groen3, HIGH); digitalWrite(groen4, HIGH);digitalWrite(groen5, HIGH);
    ledcWrite(PWM_CHANNEL, dutyCycle);
    }
}
void loop()
{
    if (!client.connected()){
    Serial.println("not connected");
    reconnect();
    }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000){
    lastMsg = now;
  }


if(messageReceived == true){
   messageReceived = false;
   control(messageTemp);
   Serial.println(messageTemp);
   messageTemp = "";
   setBuffer();
}
}

