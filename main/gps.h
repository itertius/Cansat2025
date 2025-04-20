#ifndef GPS_H
#define GPS_H

#include <TinyGPSPlus.h>
#include <tuple>

extern TinyGPSPlus gps;

void initGPS();
float readLat();
float readLon();
float readGPSAlt();
std::tuple<float, float, float> readGPS();

#endif