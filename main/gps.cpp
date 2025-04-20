#include <tuple>
#include "gps.h"

TinyGPSPlus gps;

#define GPS_RX 16
#define GPS_TX 17

HardwareSerial gpsSerial(1);

void initGPS() {
gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  Serial.println("Init GPS!!!");
  while (!gps.location.isValid()) {
    Serial.println("Waiting for GPS...");
    delay(1000);
  }
  Serial.println("GPS Found!!!");
}

float lastLat = 0.0f;
float lastLon = 0.0f;
float lastAlt = 0.0f;

std::tuple<float, float, float> readGPS() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }
  if (gps.location.isUpdated()) {
    lastLat = gps.location.lat();
    lastLon = gps.location.lng();
    lastAlt = gps.altitude.meters();
  }
  return std::make_tuple(0.0f, 0.0f, 0.0f);
}