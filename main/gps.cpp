#include <tuple>
#include "gps.h"

TinyGPSPlus gps;

#define GPS_RX 16
#define GPS_TX 17

HardwareSerial gpsSerial(1);

void initGPS() {
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  Serial.println("Init GPS!");
}

bool readGPS(float &lat, float &lon, float &alt) {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }
  if (gps.location.isValid() && gps.location.isUpdated()) {
    lat = gps.location.lat();
    lon = gps.location.lng();
    alt = gps.altitude.meters();
    return true;
  }
  return false;
}
