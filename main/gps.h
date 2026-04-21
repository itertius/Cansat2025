#ifndef GPS_H
#define GPS_H

#include <TinyGPS++.h>
#include <tuple>
#include <HardwareSerial.h>

extern TinyGPSPlus gps;

void initGPS();
void serviceGPS();
bool getLastFix(float* lat, float* lon, float* alt, unsigned long* ageMs);

#endif