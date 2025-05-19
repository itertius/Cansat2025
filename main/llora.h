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

void initLoRa(long Fq);
void send(long cmd, long time, long type, long data1, long data2, long data3, long data4, long data5, long data6);

#endif
