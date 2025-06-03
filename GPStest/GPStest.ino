#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Define GPS
TinyGPSPlus gps;
HardwareSerial ss(2); // UART2

// GPS RX to GPIO 16, TX to GPIO 17
#define RXD2 16
#define TXD2 17

unsigned long pre = 0;
unsigned long interval = 1000;

void setup() {
  Serial.begin(115200);
  ss.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("GPS Module with ESP32 - GY-NEO6MV2");
}

void loop() {
  unsigned long curr = millis();
  while (ss.available() > 0) {
    gps.encode(ss.read());
  }

  if (gps.location.isUpdated()) {
    Serial.print("Latitude: ");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude: ");
    Serial.println(gps.location.lng(), 6);
    Serial.print("Altitude: ");
    Serial.println(gps.altitude.meters());
    Serial.print("Satellites: ");
    Serial.println(gps.satellites.value());
    Serial.print("Speed: ");
    Serial.println(gps.speed.kmph());
    Serial.println();
  }
  else {
    if (curr - pre >= interval) {
      pre = curr;
      Serial.println("No GPS Updated!!!");
    }
  }
}
