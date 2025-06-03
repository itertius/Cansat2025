#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include <tuple>
#include <HardwareSerial.h>

extern TinyGPSPlus gps;

void initGPS();
bool readGPS(float &lat, float &lon, float &alt);

#endif