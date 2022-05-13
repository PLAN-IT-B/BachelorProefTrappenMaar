#include <Adafruit_PN532.h>
#include <LiquidCrystal_I2C.h>
#include "WiFi.h"
#include "PubSubClient.h"

#define SSID "NETGEAR68"
#define PWD "excitedtuba713"

#define MQTT_SERVER "192.168.1.2"
#define MQTT_PORT 1883

char cstr[16];


#define LED1 12
#define LED2 13
#define LED3 14
#define Rled 19
#define Gled 17
#define Bled 16

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;
int level;
bool messageReceived = false;

String messageSend;

void callback(char *topic, byte *message, unsigned int length);
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

LiquidCrystal_I2C lcd (0x27, 20,4);  //
byte block[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};

byte line[] = {
  B00000,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001
};

byte one[] = {
  B00000,
  B00000,
  B00100,
  B00010,
  B11111,
  B00000,
  B00000,
  B00000
};

byte two[] = {
  B00000,
  B00000,
  B11101,
  B10101,
  B10111,
  B00000,
  B00000,
  B00000
};

byte three[] = {
  B00000,
  B00000,
  B10101,
  B10101,
  B11111,
  B00000,
  B00000,
  B00000
};

byte four[] = {
  B00000,
  B00000,
  B00111,
  B00100,
  B11111,
  B00000,
  B00000,
  B00000
};

byte emptyBlock[] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);



  lcd.init();
  lcd.backlight();
  Serial.begin(115200);                // Start serial monitor after a few seconds. Mainly for testing code to get it to work.
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(callback);
  Wire.begin();
  lcd.begin(20,4);
  
  lcd.createChar(0, block);
  lcd.createChar(1, line);
  lcd.createChar(2, one);
  lcd.createChar(3, two);
  lcd.createChar(4, three);
  lcd.createChar(5, four);
  lcd.createChar(6, emptyBlock);

  lcd.setCursor(4,3); lcd.write(1);
  lcd.setCursor(9,3); lcd.write(1);
  lcd.setCursor(14,3); lcd.write(1);

  lcd.setCursor(2,3); lcd.write(2);
  lcd.setCursor(7,3); lcd.write(3);
  lcd.setCursor(12,3); lcd.write(4);
  lcd.setCursor(17,3); lcd.write(5);
 
  pinMode (LED1, OUTPUT);
  pinMode (LED2, OUTPUT);
  pinMode (LED3, OUTPUT);
  pinMode (19, OUTPUT);
  pinMode (Gled, OUTPUT);
  pinMode (Bled, OUTPUT);

}
void callback(char *topic, byte *message, unsigned int length)
{
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");

  for (int i = 0; i < length; i++)
  {
    Serial.print((char)message[i]);
    messageSend += (char)message[i];
  }
  Serial.print("Message toegekomen: ");
  Serial.print(messageSend);
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
    if (client.connect("fiets"))
    {
      Serial.println("connected");
      //hij luistert op trappen maar, fiets
      //hij schrijft naar trappen maar, buffer
      client.subscribe("TrappenMaar/fiets");
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


void display(int r) {
  lcd.setCursor(15, 2);
  if (int(r) < 10) {
    lcd.print(" ");  // if less then 10 add " " space - to remove prev carcters
  }
  lcd.print(r);
    if( (r)==0) {
      //eerst dan even kijken of het nul blijft
      //of fouten eruit te filteren
      delay(250);
      if((r)==0) {
      lcd.setCursor(0,0); lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);
      lcd.setCursor(0,1); lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);
      lcd.setCursor(0,2); lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);lcd.write(6);
        }
        else{
          display(r);
        }
      level = 0;    
    }
    else if((0<(r)) && ((r) <=50)) {
      lcd.setCursor(0,0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,1); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,2); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(5,0); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);
      lcd.setCursor(5,1); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);
      lcd.setCursor(5,2); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);

      level =1;
    }
    else if((50 < (r)) && ((r) <=100)){
      lcd.setCursor(0,0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,1); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,2); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(10,0); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); 
      lcd.setCursor(10,1); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); 
      lcd.setCursor(10,2); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); 

      level =2;
 }
    else if((100 < (r)) && ((r) <=140)){
      lcd.setCursor(0,0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,1); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,2); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(15,0); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);
      lcd.setCursor(15,1); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);
      lcd.setCursor(15,2); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6); lcd.write(6);

      level = 3;
}

    else if((r)> 140) {
      lcd.setCursor(0,0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,1); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);
      lcd.setCursor(0,2); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);lcd.write(0);lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0); lcd.write(0);

      level = 4;   
}
  
}
// the loop routine runs over and over again forever:
void loop() {

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


  // read the input on analog pin 34:
  int sensorValue = analogRead(34);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage = sensorValue * (3.3 / 4095.0);
  Serial.print(sensorValue);
  Serial.print(" ");
  // print out the value you read:
  Serial.print(voltage);
  Serial.print(" ");
  Serial.println(100*voltage);
  display(100*voltage);
  
  char cstr[16];

  
if(messageReceived == true){
   messageReceived = false;
   control(messageSend);
   Serial.println(messageSend);
   messageSend = "";
    
}


}

void control(String mess){
  //checken of 'newNumber': w gezonden dr segment wnn 7segment klaar is
 Serial.println("CONTROL IS OKE");

if(messageSend == "send"){
    Serial.println("message send is toegekomen");
    itoa(level, cstr,10);
    client.publish("TrappenMaar/buffer", cstr);
    Serial.print("level wordt verstuurd: ");
    Serial.println(cstr);
  

  }

    else if(messageSend == "led1"){
        digitalWrite (LED1, HIGH);	// turn on the LED
    }

    else if(messageSend == "led2"){
        digitalWrite (LED2, HIGH);	// turn on the LED
    }

    else if(messageSend == "led3"){
        digitalWrite (LED3, HIGH);	// turn on the LED
    }

    else if(messageSend == "correct"){
      digitalWrite (Gled, HIGH);
      delay(1000);
      digitalWrite (LED1, LOW);	
      digitalWrite (LED2, LOW);	
      digitalWrite (LED3, LOW);	
      digitalWrite (Rled, LOW);
      digitalWrite (Gled, LOW);
      client.publish("TrappenMaar/buffer", "newNumber");
      Serial.println("newNumber werd gestuurd naar buffer");
	// turn on the GREEN LED
    }

    
    else if(messageSend == "false"){
      digitalWrite (19, HIGH);	// turn on the RED LED
      delay(1000);
      digitalWrite (LED1, LOW);	
      digitalWrite (LED2, LOW);	
      digitalWrite (LED3, LOW);	
      digitalWrite (Rled, LOW);
      digitalWrite (Gled, LOW);
      client.publish("TrappenMaar/buffer", "newNumber");
      Serial.println("newNumber werd gestuurd naar buffer");
    }

    else if(messageSend == "resetFiets"){
      Serial.println("Restarting in 10 seconds");
      delay(10000);
      ESP.restart();
      Serial.println("Fiets is ook ready");
      client.publish("TrappenMaar/buffer", "Fiets ready");
    
    }
  
    else{
      Serial.print("FOUT BERICHT:");
      Serial.println(messageSend);
    }

}

