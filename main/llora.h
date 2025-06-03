#ifndef LLORA_H
#define LLORA_H

#include <LoRa.h>
#include <SPI.h>

#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  26

bool initLoRa(long Fq);
void send(float cmd, float time, float type, float data1, float data2, float data3, float data4, float data5, float data6);

#endif
