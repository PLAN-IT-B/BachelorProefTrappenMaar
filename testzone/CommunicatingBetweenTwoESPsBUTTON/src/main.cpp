#include <esp_now.h>
#include <WiFi.h>

#include <Wire.h>

// Boolean to see if signal switch high
bool LED = false;

//Structure example to send data
//Must match the receiver structure
typedef struct struct_message {
    bool LED;
} struct_message;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

esp_now_peer_info_t peerInfo;

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  LED = incomingReadings.LED;
}

static void updateDisplay();
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  updateDisplay();
}

void updateDisplay(){// Display Readings in Serial Monitor
  digitalWrite(LED_BUILTIN, LED);
}