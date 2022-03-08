#include "WiFi.h"
#include "PubSubClient.h" //pio lib install "knolleary/PubSubClient"

#define SSID          "NETGEAR68"
#define PWD           "excitedtuba713"

#define MQTT_SERVER   "192.168.1.20"
#define MQTT_PORT     1883

#define LED_PIN       2

byte pin[] = {22,23,4,5,18,19,21};
const byte count[4] = {
  B00000110,
  B01011011,
  B01001111,
  B01100110,
};

static void waitForInput();
static void handleInput();
static void printNumber(int number);
#define PN532_IRQ   4
#define PN532_RESET 5 
boolean readerDisabled = false;
int irqCurr;
int irqPrev;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void callback(char *topic, byte *message, unsigned int length);

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

  uint8_t functie = 1; //transmitter
  //uint8_t functie = 2 //receiver

  pinMode(pin[0], OUTPUT);
  pinMode(pin[1], OUTPUT);
  pinMode(pin[2], OUTPUT);
  pinMode(pin[3], OUTPUT);
  pinMode(pin[4], OUTPUT);
  pinMode(pin[5], OUTPUT);
  pinMode(pin[6], OUTPUT);

  for(int i=0; i<4; i++){
    digitalWrite(pin[i], bitRead(3, i));
  }

  waitForInput();
}

void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  int messageTemp;

  for (int i = 0; i < length; i++)
  {
    Serial.print((int)message[i]);
    messageTemp += (int)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "esp32/output")
  {
    printNumber(messageTemp);
  }
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
    if (client.connect("ESP8266ClientTransmitter"))
    {
      Serial.println("connected");
      // Subscribe
      client.subscribe("tag/number");
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

  if(readerDisabled){
    readerDisabled = false;
    waitForInput();
  }
  else{
    irqCurr = digitalRead(PN532_IRQ);
    if(irqCurr == LOW && irqPrev == HIGH){
      handleInput();
    }
    irqPrev = irqCurr;
  }

}
//code for receiver

void printNumber(int number){
  for(int i=0; i<4; i++){
    digitalWrite(pin[i], bitRead(number-1, i));
  }
}

void waitForInput(){
  irqPrev = irqCurr = HIGH;
  handleInput();
}
void handleInput(){

}


// code for transmitter
/*void waitForInput(){
  irqPrev = irqCurr = HIGH;
  Serial.println("druk op enter");
  getchar();
  handleInput();
}

void handleInput(){
  const char* cijfers [4]= {"1", "2", "3", "4"};
  int n = rand()%4;
  const char* cijfer = cijfers[n];
  client.publish("tag/cijfer", cijfer);
}*/