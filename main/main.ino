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
const char* ssid = "CAT yamalah wifi";
const char* password = "pppb1346";
long Fq = 935E6;
unsigned long previous = 0;
unsigned long interval = 500;

void setup() {
  Serial.begin(115200);
  initLoRa(Fq);
  initWifi(ssid, password);
  initWebserver();
  initWebSocket();
}

void loop() {
  unsigned long curr = millis();
  handClient();
  handSocket();

  if (curr - previous >= interval) {
    if (int(LoRa.parsePacket())) {
      payload = receive();
      pushserver(payload);
    }
  }

  payload = "";
}