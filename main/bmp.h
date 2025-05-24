#ifndef BMP_H
#define BMP_H

#include <Adafruit_BMP280.h>
#include <Wire.h>

extern Adafruit_BMP280 bmp;

void initBMP(float sl);
float readBMPTemp();
float readPress();
float readBMPAlt(float alt);

#endif
