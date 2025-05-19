#ifndef MPU_H
#define MPU_H

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

extern Adafruit_MPU6050 mpu;

void initMPU(int A_range, int G_range, int BW_range);
float readAcc(char axis);
float readGyro(char axis);
float testGyro();

#endif