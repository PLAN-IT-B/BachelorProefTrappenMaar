#include "WiFi.h"
#include "PubSubClient.h" //pio lib install "knolleary/PubSubClient"
#include <Arduino.h>

#define SSID "NETGEAR68"
#define PWD "excitedtuba713"

#define MQTT_SERVER "192.168.1.2"
#define MQTT_PORT 1883

#define ONBOARD_LED  2


WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

int fiveSeconds =0;
int bufferValue;
String messageTemp;

char cstr[16]="";

void callback(char *topic, byte *message, unsigned int length);
void sendTo7Segment (int eps, char* cstr);
void checkMessage(String mess);
void control(String message);

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


  /*int randomGetal = random(1,5);
  char cstr[16];
  itoa(randomGetal,cstr,10);
  int randomEsp = random(1,2); //getal 1,2, 3 of 4
  Serial.println("randomESP");
  sendTo7Segment(randomEsp, cstr);
  Serial.println("setup done");*/

  
while(messageTemp!="newNumber"){
  Serial.println("nog niets ontvangen");
  control("newNumber");
  delay(5000);
 }
}

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
  Serial.println(messageTemp);
  control(messageTemp); 

  // Feel free to add more if statements to control more GPIOs with MQTT
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
    if (client.connect("Lyssa"))
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
    client.publish("TrappenMaar",cstr);
    digitalWrite(ONBOARD_LED,HIGH);
    Serial.println("ok");
    delay(500);
    digitalWrite(ONBOARD_LED,LOW);

  }

  else if (randomEsp ==2){
    client.publish("TrappenMaar/esp2", cstr);
  }

  else if (randomEsp ==3){
    client.publish("TrappenMaar/esp3", cstr);
  }
  
  else if (randomEsp ==4){
    client.publish("TrappenMaar/esp4", cstr);
  }

}


void control(String mess){
  //checken of 'newNumber': w gezonden dr segment wnn 7segment klaar is
 Serial.println("CONTROL IS OKE");
 
 if(mess == "newNumber"){
    Serial.println("MESSAGE: newNumber ARRIVED");
    int randomGetal = random(1,5);
    itoa(randomGetal,cstr,10);
    int randomEsp = random(1,2); //getal 1,2, 3 of 4
    Serial.println("randomESP");
    Serial.print("esp: ");
    Serial.print(randomEsp);
    Serial.print("nummer: ");
    Serial.print(randomGetal);
    sendTo7Segment(randomEsp, cstr);
  }

  //checken of level doorgestuurd werd door fiets
  else if((mess == "1")||(mess == "2")||(mess == "3")||(mess == "4")){
        Serial.println("MESSAGE: level ARRIVED");
        checkMessage(mess);
    }

  else{
    Serial.println("MESSAGE: not for me");

  }
  
}

void checkMessage(String mess) {
  /*Serial.println("bericht ontvangen");
  if(mess == cstr){
    bufferValue ++;
    Serial.println("CORRECT GEFIETST, buffer stijgt");
    Serial.println(bufferValue);
  }*/

}


void loop()
{
    if (!client.connected()){
    reconnect();
    }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000){
    lastMsg = now;
  }

  //-------RANDOM ESP KIEZEN-------//
  //idee: 4 esp laten luisteren elk op iets anders: de eerste op TrappenMaar/esp1 de tweede op ..
  //en dan eerst een random int laten kiezen tussen 1 en 4 en afh van welk int, via een if lus, een andere lus uitvoeren en dus ook naar een andere esp schrijven
  // hypothetische code: 
  //OPGELET: vergeet in de verschillende codes van de ESP's hun 'naam' niet uniek te maken!
  //------------------------------//
/*
  int randomGetal = random(1,5);
  //char cstr[16];
  itoa(randomGetal,cstr,10);
  int randomEsp = random(1,2); //getal 1,2, 3 of 4
  Serial.println("randomESP");
  Serial.print("esp: ");
  Serial.print(randomEsp);
  Serial.print("nummer: ");
  Serial.println(cstr);
  sendTo7Segment(randomEsp, cstr);
  delay(5000);
*/

  //random getal: 1,2,3 of 4
  /*int randomGetal = random(1,5);
  char cstr[16];
  itoa(randomGetal, cstr,10);
  client.publish("TrappenMaar", cstr);
  delay(3000);*/
  

}
