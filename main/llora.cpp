#include "llora.h"

void initLoRa(long Fq = 921475E6) {
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(Fq)) {
    Serial.println("LoRa Not Found!!!");
  } else {
    LoRa.setSignalBandwidth(125E3);
    LoRa.setSpreadingFactor(9);
    Serial.println("LoRa Found!!!");
  }
}

String receive() {
  if (!LoRa.available()) return "";
  String incoming = "";
  while (LoRa.available()) incoming += (char)LoRa.read();

  return incoming;
}