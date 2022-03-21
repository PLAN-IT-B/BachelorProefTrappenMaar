#include "WiFi.h"
#include "PubSubClient.h" //pio lib install "knolleary/PubSubClient"

#define SSID "NETGEAR68"
#define PWD "excitedtuba713"

#define MQTT_SERVER "192.168.1.2"
#define MQTT_PORT 1883

#define LED_PIN 2

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char *topic, byte *message, unsigned int length);
void sendTo7Segment (int eps, char cstrs);

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

  pinMode(LED_PIN, OUTPUT);
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
      //subscribe("TrappenMaar/status");
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

void sendTo7Segment(int randomEsp, char cstr){
  if(randomEsp == 1) {
    client.publish("TrappenMaar/esp1", cstr);
    delay(5000); //zelfde delay als andere esp's bij laten branden 7segment
  }

  else if (randomEsp ==2){
    client.publish("TrappenMaar/esp2", cstr);
    delay(5000); //zelfde delay als andere esp's bij laten branden 7segment
  }

  else if (randomEsp ==3){
    client.publish("TrappenMaar/esp3", cstr);
    delay(5000); //zelfde delay als andere esp's bij laten branden 7segment
  }
  
  else if (randomEsp ==4){
    client.publish("TrappenMaar/esp4", cstr);
    delay(5000); //zelfde delay als andere esp's bij laten branden 7segment
  }

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

  //-------RANDOM ISP KIEZEN-------//
  //idee: 4 esp laten luisteren elk op iets anders: de eerste op TrappenMaar/esp1 de tweede op ..
  //en dan eerst een random int laten kiezen tussen 1 en 4 en afh van welk int, via een if lus, een andere lus uitvoeren en dus ook naar een andere esp schrijven
  // hypothetische code: 
  //OPGELET: vergeet in de verschillende codes van de ESP's hun 'naam' niet uniek te maken!
  //------------------------------//

  int randomGetal = random(1,5);
  char cstr[16];
  itoa(randomGetal, cstr,10);
  int randomEsp = random(1,3); //getal 1,2, 3 of 4
  Serial.println("randomESP");
  sendTo7Segment(randomEsp, cstr);


  //random getal: 1,2,3 of 4
  /*int randomGetal = random(1,5);
  char cstr[16];
  itoa(randomGetal, cstr,10);
  client.publish("TrappenMaar", cstr);
  delay(3000);*/
  

}
