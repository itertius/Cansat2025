#ifndef LLORA_H
#define LLORA_H

#include <Arduino.h>
#include <LoRa.h>
#include <SPI.h>

#define LORA_SCK   18
#define LORA_MISO  19
#define LORA_MOSI  23
#define LORA_SS    5
#define LORA_RST   14
#define LORA_DIO0  26

void initLoRa(long Fq);
String receive();

#endif