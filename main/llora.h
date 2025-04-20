#ifndef LLORA_H
#define LLORA_H

#include <Arduino.h>
#include <LoRa.h>

void initLoRa(long Fq);
String receive();

#endif