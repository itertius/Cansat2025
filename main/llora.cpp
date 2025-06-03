  #include "llora.h"

  bool initLoRa(long Fq = 921.925E6) {
    SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);

    LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

    if (!LoRa.begin(Fq)) {
      Serial.println("LoRa Not Found!!!");
      return false;
    } else {
      LoRa.setSignalBandwidth(125E3);
      LoRa.setSpreadingFactor(9);
      Serial.println("LoRa Found!!!");
      return true;
    }
  }

  // [0, 0, [0, 0, 0, 0, 0, 0, 0]]
void send(float cmd, float time, float type, float data1, float data2, float data3, float data4, float data5, float data6) {
  String payload = "{";
  payload += "\"cmd\":" + String(cmd, 2);
  payload += ",\"time\":" + String(time / 1000.0, 2);
  payload += ",\"type\":" + String(type, 2);
  payload += ",\"data\":[" + 
             String(data1, 2) + "," + 
             String(data2, 2) + "," + 
             String(data3, 2) + "," + 
             String(data4, 2) + "," + 
             String(data5, 2) + "," + 
             String(data6, 2) + "]";
  payload += "}\n";

  LoRa.beginPacket();
  LoRa.print(payload);
  if (LoRa.endPacket()) {
    Serial.println("Send!!!");
    Serial.println(payload);
  }
}
