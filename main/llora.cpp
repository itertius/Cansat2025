#include "llora.h"

void initLoRa(long Fq = 935E6) {
  if (!LoRa.begin(Fq)) {
    Serial.println("LoRa Not Found!!!");
  }
  else {
    Serial.println("LoRa Found!!!");
  }
}

String receive() {
  String incoming = "";
  while (LoRa.available()) incoming += (char)LoRa.read();

  return incoming;
}