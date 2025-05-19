#include "llora.h"

void initLoRa(long Fq = 915E6) {
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(Fq)) {
    Serial.println("LoRa Not Found!!!");
  } else {
    Serial.println("LoRa Found!!!");
  }
}

// [0, 0, [0, 0, 0, 0, 0, 0, 0]]
void send(long cmd, long time, long type, long data1, long data2, long data3, long data4, long data5, long data6) {
  char payload[150];
  snprintf(payload, sizeof(payload), "[%ld,%ld,[%ld,%ld,%ld,%ld,%ld,%ld,%ld]]", 
           cmd, time, type, data1, data2, data3, data4, data5, data6);
  
  LoRa.beginPacket();
  LoRa.print(payload);
  if (LoRa.endPacket()) {
    Serial.println("Send!!!");
  }
}
