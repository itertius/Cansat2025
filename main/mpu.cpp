#include "mpu.h"

Adafruit_MPU6050 mpu;

sensors_event_t a, g, temp;

void initMPU(int A_range, int G_range, int BW_range) {
  if (!mpu.begin()) {
    Serial.println("MPU Not Found!!!");
  }
  else {
    Serial.println("MPU Found!!!");

    switch (A_range) {
      case 2:
        mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
        break;
      case 4:
        mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
        break;
      case 8:
        mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
        break;
      case 16:
        mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
        break;
      default:
        Serial.println("Invalid A_range. Using default (2G).");
        mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
        break;
    }

    switch (G_range) {
      case 250:
        mpu.setGyroRange(MPU6050_RANGE_250_DEG);
        break;
      case 500:
        mpu.setGyroRange(MPU6050_RANGE_500_DEG);
        break;
      case 1000:
        mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
        break;
      case 2000:
        mpu.setGyroRange(MPU6050_RANGE_2000_DEG);
        break;
      default:
        Serial.println("Invalid G_range. Using default (250DPS).");
        mpu.setGyroRange(MPU6050_RANGE_250_DEG);
        break;
    }

    switch (BW_range) {
      case 5:
        mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
        break;
      case 10:
        mpu.setFilterBandwidth(MPU6050_BAND_10_HZ);
        break;
      case 21:
        mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
        break;
      case 44:
        mpu.setFilterBandwidth(MPU6050_BAND_44_HZ);
        break;
      case 94:
        mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);
        break;
      case 184:
        mpu.setFilterBandwidth(MPU6050_BAND_184_HZ);
        break;
      case 260:
        mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
        break;
      default:
        Serial.println("Invalid BW_range. Using default (94Hz).");
        mpu.setFilterBandwidth(MPU6050_BAND_94_HZ);
        break;
    }

    mpu.getEvent(&a, &g, &temp);
    Serial.println("Testing MPU6050!!!");
    Serial.println("Acc (x, y, z), Gy (x, y, z), Temp");

    Serial.print(a.acceleration.x);
    Serial.print(" ");
    Serial.print(a.acceleration.y);
    Serial.print(" ");
    Serial.println(a.acceleration.z);

    Serial.print(g.gyro.x);
    Serial.print(" ");
    Serial.print(g.gyro.y);
    Serial.print(" ");
    Serial.println(g.gyro.z);

    Serial.println(temp.temperature);

    Serial.println("Finished init MPU!!!");
    Serial.println("| -------- |"); 
  }
}

float readAcc(char c) {
  mpu.getEvent(&a, &g, &temp);
  switch (c) {
    case 'x':
      return a.acceleration.x;
    case 'y':
      return a.acceleration.y;
    case 'z':
      return a.acceleration.z;
    default :
      return 0.0f;
  }
}

float readGyro(char c) {
  mpu.getEvent(&a, &g, &temp);
  switch (c) {
    case 'x':
      return g.gyro.x;
    case 'y':
      return g.gyro.y;
    case 'z':
      return g.gyro.z;
    default :
      return 0.0f;
  }
}