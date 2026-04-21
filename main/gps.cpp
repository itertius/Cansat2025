#include <tuple>
#include "gps.h"

TinyGPSPlus gps;

#define GPS_RX 16
#define GPS_TX 17
HardwareSerial gpsSerial(1);

static float lastLat = 0, lastLon = 0, lastAlt = 0;
static bool  hasFix   = false;
static unsigned long lastFixMs = 0;

void initGPS() {
  gpsSerial.begin(9600, SERIAL_8N1, GPS_RX, GPS_TX);
  Serial.println("Init GPS!");
}

void serviceGPS() {
  while (gpsSerial.available()) {
    gps.encode(gpsSerial.read());
  }

  if (gps.location.isValid()) {
    lastLat = gps.location.lat();
    lastLon = gps.location.lng();
    if (gps.altitude.isValid()) lastAlt = gps.altitude.meters();
    hasFix = true;
    if (gps.location.isUpdated() || gps.altitude.isUpdated()) {
      lastFixMs = millis();
    }
  }
}

bool getLastFix(float* lat, float* lon, float* alt, unsigned long* ageMs) {
  if (!hasFix) return false;
  if (lat)   *lat   = lastLat;
  if (lon)   *lon   = lastLon;
  if (alt)   *alt   = lastAlt;
  if (ageMs) *ageMs = millis() - lastFixMs;
  return true;
}