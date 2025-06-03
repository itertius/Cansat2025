// Arduino lib
 #include <Wire.h>
 #include <SPI.h>

// BMP280
#include "bmp.h"
unsigned long b_update = 0;
const unsigned long b_interval = 300;

// GY-521
#include "mpu.h"
unsigned long m_update = 0;
const unsigned long m_interval = 500;

// LoRa
#include "llora.h"

// GPS
#include "gps.h"
unsigned long g_update = 0;
unsigned long g_interval = 250;

// Constant
const float sl = 1013.5;
long Fq = 921.925E6;

// state
bool is_LoRa = false;
bool is_BMP = false;
bool is_MPU = false;
bool is_GPS = false;

void setup() {
  Serial.begin(115200);
  if (initLoRa(Fq)) is_LoRa = true;
  if (initBMP(sl)) is_BMP = true;
  if (initMPU(2, 250, 94)) is_MPU = true;
  initGPS();
}

void loop() {
  unsigned long curr = millis();

  if (is_LoRa) {
    // BMP280 Call
    handleBMP(curr);
    // testBMP(curr);
    
    // GY-521 Call
    handleMPU(curr);

    // GPS Call
    handleGPS(curr);
  }
  else {
    testBMP(curr);
    testMPU(curr);
    testGPS(curr);
  }
}

void handleBMP(unsigned long curr) {
  if (curr - b_update >= b_interval) {
    b_update = curr;
    // send(0, curr, 0, readBMPTemp(), readPress(), readBMPAlt(sl), 0, 0, 0);
    updateMPU();
    send(0, curr, 0, readTemp(), 0, 0, 0, 0, 0);
  }
}

void handleMPU(unsigned long curr) {
  if (curr - m_update >= m_interval && is_MPU) {
    m_update = curr;
    updateMPU();
    send(0, curr, 1, 
         readAcc('x'), readAcc('y'), readAcc('z'), 
         readGyro('x'), readGyro('y'), readGyro('z'));
  }
}

void handleGPS(unsigned long curr) {
  if (curr - g_update >= g_interval) {
    g_update = curr;
    float lat = 0, lon = 0, alt = 0;
    if (readGPS(lat, lon, alt)) {
      send(0, curr, 2, 
           (long)(lat * 1e6), (long)(lon * 1e6), (long)(alt), 
           0, 0, 0);
    }
  }
}

void testBMP(unsigned long curr) {
  if (curr - b_update >= b_interval && is_BMP) {
    b_update = curr;
    Serial.println(readBMPTemp());
    Serial.println(readPress());
    Serial.println(readBMPAlt(sl));
  }
}

void testMPU(unsigned long curr) {
  if (curr - m_update >= m_interval && is_MPU) {
    m_update = curr;
    updateMPU();
    Serial.println(readAcc('x'));
    Serial.println(readAcc('y'));
    Serial.println(readAcc('z'));
    Serial.println(readGyro('x'));
    Serial.println(readGyro('y'));
    Serial.println(readGyro('z'));
  }
}

void testGPS(unsigned long curr) {
  if (curr - g_update >= g_interval) {
    g_update = curr;
    float lat = 0, lon = 0, alt = 0;
    if (readGPS(lat, lon, alt)) {
      Serial.println((long)(lat * 1e6));
      Serial.println((long)(lon * 1e6));
      Serial.println((long)(alt));
    }
  }
}