#include "llora.h"

void initLoRa(long Fq) {
  if (!LoRa.begin(Fq)) {
    Serial.println("LoRa Not Found!!!");
  }
  else {
    Serial.print("LoRa Found!!!");
  }
}

// [0, 0, [0, 0, 0, 0, 0, 0, 0]]
void send(long cmd, long time, long type, long data1, long data2, long data3, long data4, long data5, long data6) {
  String payload = "[" + String(cmd) + "," + String(time) + ",[" + String(type) + "," + String(data1) + "," + String(data2) + "," + String(data3) + "," + String(data4) + "," + String(data5) + "," + String(data6) + "]]";

  LoRa.beginPacket();
  LoRa.print(payload);
  LoRa.endPacket();
}
