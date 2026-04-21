#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include <stdint.h>

// --------------------------------------
// MPU6050 (GY-521) IMU
// --------------------------------------
#include "mpu.h"
unsigned long m_update = 0;
const unsigned long m_interval = 500; // ms between TEMP packets
bool is_MPU  = false;

// --------------------------------------
// GPS module
// --------------------------------------
#include "gps.h"
unsigned long g_update = 0;
const unsigned long g_interval = 500; // ms between GPS packets
bool is_GPS  = false;

// --------------------------------------
// LoRa radio
// --------------------------------------
#include "llora.h"
long Fq = 921.925E6;  // LoRa frequency in Hz
bool is_LoRa = false;

// --------------------------------------
// Helper: get packed GPS in dashboard format
// --------------------------------------
//
// Dashboard expects "type":2 packets like:
//   {"cmd":0,"time":1234,"type":2,"data":[ilat,ilon,ialt]}
// where:
//   ilat = latitude_deg * 1e6 (int32)
//   ilon = longitude_deg * 1e6 (int32)
//   ialt = altitude_meters (int32)
//
// We will convert floats -> scaled ints here.
//
bool getPackedGPS(int32_t &ilat, int32_t &ilon, int32_t &ialt) {
  float lat, lon, alt;
  unsigned long age;

  // You already had this pattern:
  // if (!getLastFix(&lat, &lon, &alt, &age)) return false;
  // if (age > 2000) return false;
  //
  // We'll reuse that logic:
  if (!getLastFix(&lat, &lon, &alt, &age)) {
    return false;
  }
  if (age > 2000) { // older than 2 seconds = stale
    return false;
  }

  ilat = (int32_t)lroundf(lat * 1e6f);
  ilon = (int32_t)lroundf(lon * 1e6f);
  ialt = (int32_t)lroundf(alt);
  return true;
}

// --------------------------------------
// setup()
// --------------------------------------
void setup() {
  Serial.begin(115200);

  // I2C for MPU6050
  // ESP32 default you chose: SDA=21, SCL=22
  Wire.begin(21, 22);
  Wire.setClock(100000); // 100kHz = safe and stable

  // LoRa radio init
  if (initLoRa(Fq)) {
    is_LoRa = true;
    Serial.println("LoRa OK");
  } else {
    Serial.println("LoRa FAIL");
  }

  // MPU6050 init
  // Args: accel range (2g/4g/8g/16g),
  //       gyro range (250/500/1000/2000 dps),
  //       bandwidth Hz (5/10/21/44/94/184/260)
  if (initMPU(2, 250, 94)) {
    is_MPU = true;
    Serial.println("| -------- |");
    Serial.println("MPU OK");
  } else {
    Serial.println("MPU FAIL");
  }

  // GPS init
  initGPS();
  is_GPS = true;
  Serial.println("GPS init!");
}

// --------------------------------------
// loop()
// --------------------------------------
void loop() {
  unsigned long curr = millis();

  // Keep GPS parser alive every loop so we have fresh fixes
  // (usually this reads from Serial1 / UART and feeds TinyGPS++)
  serviceGPS();

  // 1) TEMP PACKET (type 3)
  //
  // Ground browser expects:
  //   {"cmd":0,"time":<ms>,"type":3,"data":[tempC,0,0,0,0,0]}
  //
  // Our send() signature is:
  //   send(node, time_ms, type, a,b,c,d,e,f)
  //
  if (curr - m_update >= m_interval) {
    m_update = curr;

    if (is_MPU && is_LoRa) {
      // Ask MPU6050 for latest reading
      updateMPU();
      float t_mpu = readTemp(); // degC (IMU die temp)

      // Debug to USB serial
      Serial.print("TEMP PACKET: t_mpu = ");
      Serial.println(t_mpu, 3);

      // Transmit over LoRa
      // We'll pack temp into 'a', and leave b..f = 0 for now
      // (The ground station will turn this into type:3 JSON)
      send(
        0,          // node id (your satellite ID)
        curr,       // ms timestamp
        3,          // packet type 3 = TEMP ONLY
        t_mpu,      // a = degC
        0,          // b
        0,          // c
        0,          // d
        0,          // e
        0           // f
      );

      Serial.println("Sent TEMP packet!");
    }
  }

  // 2) GPS PACKET (type 2)
  //
  // Ground browser expects:
  //   {"cmd":0,"time":<ms>,"type":2,"data":[ilat,ilon,ialt]}
  //
  // where ilat = lat_deg * 1e6, etc.
  //
  if (curr - g_update >= g_interval) {
    g_update = curr;

    if (is_GPS && is_LoRa) {
      int32_t ilat = 0;
      int32_t ilon = 0;
      int32_t ialt = 0;
      bool fresh = getPackedGPS(ilat, ilon, ialt);

      if (fresh) {
        // Debug info to USB serial
        Serial.print("GPS PACKET: lat=");
        Serial.print(ilat / 1e6f, 6);
        Serial.print(" lon=");
        Serial.print(ilon / 1e6f, 6);
        Serial.print(" alt=");
        Serial.println(ialt);

        // Send GPS packet over LoRa.
        //
        // NOTE:
        // send() takes float slots a..f.
        // We'll cast the scaled ints into floats.
        // On the ground receiver (before printing JSON to browser)
        // you should cast them BACK to int32 and output them as integers.
        //
        send(
          0,            // node id
          curr,         // ms timestamp
          2,            // packet type 2 = GPS FIX
          (float)ilat,  // a
          (float)ilon,  // b
          (float)ialt,  // c
          0,            // d
          0,            // e
          0             // f
        );

        Serial.println("Sent GPS packet!");
      } else {
        // No fresh fix (<2s old), skip sending
        // Optional: Serial.println("GPS not fresh yet...");
      }
    }
  }
}