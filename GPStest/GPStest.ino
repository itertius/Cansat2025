#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <LoRa.h>

// ===== GPS =====
TinyGPSPlus gps;
HardwareSerial ss(2); // UART2
#define RXD2 16
#define TXD2 17

// ===== LoRa =====
#define LORA_SS   5
#define LORA_RST 14
#define LORA_DIO0 2
long LORA_FREQ = 921.925E6;   // 921.925 MHz

unsigned long lastSend = 0;
const unsigned long sendInterval = 1000;

void setup() {
  Serial.begin(115200);
  ss.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("GPS + LoRa Test");

  // --- init LoRa ---
  LoRa.setPins(LORA_SS, LORA_RST, LORA_DIO0);
  if (!LoRa.begin(LORA_FREQ)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  Serial.println("LoRa OK");
}

void loop() {
  while (ss.available()) gps.encode(ss.read());

  unsigned long now = millis();
  if (now - lastSend >= sendInterval) {
    lastSend = now;

    if (gps.location.isValid() && gps.location.age() < 2000) {
      double lat = gps.location.lat();
      double lon = gps.location.lng();
      double alt = gps.altitude.meters();

      // Send over LoRa
      LoRa.beginPacket();
      LoRa.print("{\"cmd\":0,\"time\":");
      LoRa.print(now / 1000.0, 2);
      LoRa.print(",\"type\":2,\"data\":[");
      LoRa.print((int32_t)lround(lat * 1e6));
      LoRa.print(",");
      LoRa.print((int32_t)lround(lon * 1e6));
      LoRa.print(",");
      LoRa.print((int32_t)lround(alt));
      LoRa.println("]}");
      LoRa.endPacket();

      Serial.printf("Sent GPS: %.6f, %.6f, %.1f m\n", lat, lon, alt);
    } else {
      Serial.println("No GPS fix yet…");
    }
  }
}