#include "llora.h"

void initLoRa(long Fq = 935E6) {
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(Fq)) {
    Serial.println("LoRa Not Found!!!");
  } else {
    Serial.println("LoRa Found!!!");
  }
}

String receive() {
  String incoming = "";
  while (LoRa.available()) incoming += (char)LoRa.read();

  return incoming;
}