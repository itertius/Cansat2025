#include "bmp.h"

Adafruit_BMP280 bmp;

bool initBMP(float sl) {
  if (!bmp.begin()) {
    Serial.println("BMP Not Found!!!");
    return false;
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
    return true;
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