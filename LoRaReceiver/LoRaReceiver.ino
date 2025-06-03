#include <SPI.h>
#include <LoRa.h>

#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  2

String receive() {
  String incoming = "";
  int packetSize = LoRa.parsePacket();
  if (packetSize > 0) {
    while (LoRa.available()) {
      char c = (char)LoRa.read();
      incoming += c;
      Serial.print(c);
    }
  }
  return incoming;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_SS);

  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);

  if (!LoRa.begin(921.925E6)) {
    Serial.println("LoRa Not Found!!!");
  } else {
    LoRa.setSignalBandwidth(125E3);
    LoRa.setSpreadingFactor(9);
    Serial.println("LoRa Found!!!");
  }
}

String incoming = "";
void loop() {
  incoming = receive();
  incoming = "";
}
