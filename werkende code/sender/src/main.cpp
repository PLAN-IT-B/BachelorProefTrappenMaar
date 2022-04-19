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
String messageTemp = "newNumber";
bool messageReceived = true;

char cstr[16];

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
    Serial.println("message send to esp1");
    client.publish("TrappenMaar/esp1", cstr);
    cstr="";  
    }
    

  else if (randomEsp ==2){
    Serial.println("message send to esp2");
    client.publish("TrappenMaar/esp2", cstr);
    cstr="";
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
    //OORSPRONKELIJK TUSSEN 1 EN 5
    int randomGetal = random(0,3);
    itoa(randomGetal,cstr,10);
    //OORSPRONKELIJK TUSSEN 1 EN 5
    int randomEsp = random(1,2); //getal 1,2, 3 of 4
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
    Serial.println("CORRECT GEFIETST, buffer stijgt");
  }
  else{
    client.publish("TrappenMaar/fiets", "false");
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
   messageTemp = "";
   Serial.println(messageReceived);
}
  

}
