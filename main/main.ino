// Arduino lib
 #include <Wire.h>
 #include <SPI.h>

// BMP280
#include "bmp.h"
unsigned long b_update = 0;
const unsigned long b_interval = 1000;

// GY-521
#include "mpu.h"
unsigned long m_update = 0;
const unsigned long m_interval = 500;

// LoRa
#include "llora.h"

// GPS
#include "gps.h"
unsigned long g_update = 0;
const unsigned long g_interval = 5000;

// Constant
const float sl = 1013.5;

void setup() {
  Serial.begin(115200);
  initBMP();
  initMPU(2, 250, 94);
  // initGPS();
}

void loop() {
  unsigned long curr = millis();

  // BMP280 Call
  if (curr-b_update>=b_interval) {
    b_update = curr;
    send(0, curr, 0, readBMPTemp(), readPress(), readBMPAlt(sl), 0, 0, 0);
  }
  
  // GY-521 Call
  if (curr-m_update>=m_interval) {
    m_update = curr;
    send(0, curr, 1, readAcc('x'), readAcc('y'), readAcc('z'), readGyro('x'), readGyro('y'), readGyro('z'));
  }

  // GPS Call
  if (curr-g_update>=g_interval) {
    g_update = curr;
    auto [lat, lon, alt] = readGPS();
    send(0, curr, 2, lat, lon, alt, 0, 0, 0);
  }
}