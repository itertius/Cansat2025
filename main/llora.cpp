#include "llora.h"

void initLoRa(long Fq = 921.925E6) {
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
  String incoming = "";
  int packetSize = LoRa.parsePacket();
  if (packetSize > 0) {
    while (LoRa.available()) {
      char c = (char)LoRa.read();
      incoming += c;
    }
  }
  Serial.print(incoming);
  return incoming;
}
