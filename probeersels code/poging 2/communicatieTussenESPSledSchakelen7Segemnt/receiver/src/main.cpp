#include "WiFi.h"
#include "PubSubClient.h" //pio lib install "knolleary/PubSubClient"
#include <iostream>
#include <string.h>

#define SSID          "NETGEAR68"
#define PWD           "excitedtuba713"

#define MQTT_SERVER   "192.168.1.2"
#define MQTT_PORT     1883

#define LED_2         14

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char *topic, byte *message, unsigned int length);
void schakelLED(String message);

//for the 7segment display
int a = 14;  //For displaying segment "a"
int b = 27;  //For displaying segment "b"
int c = 33;  //For displaying segment "c"
int d = 25;  //For displaying segment "d"
int e = 26;  //For displaying segment "e"
int f = 12;  //For displaying segment "f"
int g = 13;  //For displaying segment "g"
int point = 32; //For displaying the point

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

  Serial.begin(115200);

  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);

  pinMode(LED_2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //for 7segment display
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
}

//for 7segment display
void displayDigit(int digit){
  //Conditions for displaying segment a
  if(digit!=1 && digit != 4)
  digitalWrite(a,HIGH);
  
  //Conditions for displaying segment b
  if(digit != 5 && digit != 6)
  digitalWrite(b,HIGH);
  
  //Conditions for displaying segment c
  if(digit !=2)
  digitalWrite(c,HIGH);
  
  //Conditions for displaying segment d
  if(digit != 1 && digit !=4 && digit !=7)
  digitalWrite(d,HIGH);
  
  //Conditions for displaying segment e 
  if(digit == 2 || digit ==6 || digit == 8 || digit==0)
  digitalWrite(e,HIGH);
  
  //Conditions for displaying segment f
  if(digit != 1 && digit !=2 && digit!=3 && digit !=7)
  digitalWrite(f,HIGH);
  if (digit!=0 && digit!=1 && digit !=7)
  digitalWrite(g,HIGH);
  
  }
  void turnOff()
  {
    digitalWrite(a,LOW);
    digitalWrite(b,LOW);
    digitalWrite(c,LOW);
    digitalWrite(d,LOW);
    digitalWrite(e,LOW);
    digitalWrite(f,LOW);
    digitalWrite(g,LOW);
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
  schakelLED(messageTemp);

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
    if (client.connect("ESP8266Sander"))
    {
      Serial.println("connected");
      // Subscribe
      //client.subscribe("input/#");
      client.subscribe("TrappenMaar");
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
void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 5000)
  {
    lastMsg = now;
  }


  //client.publish("TrappenMaar","R");
  //delay(3000);
  

}

void schakelLED(String message){
  if (message == "1"){
    displayDigit(1);
  }
  else if(message == "2"){
    displayDigit(2);    
  }
  else if(message == "3"){
    displayDigit(3);
  }
  else if(message == "4"){
    displayDigit(4); 
  }

  delay(3000);
  turnOff();
}