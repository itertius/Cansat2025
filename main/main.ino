// Arduino lib
#include <SPI.h>

// LoRa
#include "llora.h"

// webserver
#include "wwebserver.h"

// websocket
#include "wwebsocket.h"

// Wifi
#include "wwifi.h"

// variable
String payload = "";
const char* ssid = "tetae";
const char* password = "12345678";
long Fq = 921.925E6;
unsigned long previous = 0;
unsigned long interval = 80;

void setup() {
  Serial.begin(115200);
  initLoRa(Fq);
  // initWifi(ssid, password);
  // initWebserver();
  // initWebSocket();
}

void loop() {
  unsigned long curr = millis();
  // handClient();
  // handSocket();
  if (curr - previous >= interval) {
    payload = receive();
    // Serial.print(payload);
    // pushserver(payload);
  }
  payload="";
}