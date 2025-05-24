#include "bmp.h"

Adafruit_BMP280 bmp;

void initBMP(float sl) {
  if (!bmp.begin()) {
    Serial.println("BMP Not Found!!!");
  } else {
    Serial.println("BMP Found!!!");

    Serial.println("Test BMP280!!!");

    Serial.print("Temperature = ");
    Serial.println(bmp.readTemperature());

    Serial.print("Pressure = ");
    Serial.println(bmp.readPressure());

    Serial.print("BMP Altitude = ");
    Serial.println(bmp.readAltitude(sl));

    Serial.println("| -------- |");
  }
}

float readBMPTemp() {
  return bmp.readTemperature();
}

float readPress() {
  return bmp.readPressure();
}

float readBMPAlt(float alt) {
  return bmp.readAltitude(alt);
}