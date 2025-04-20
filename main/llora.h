#ifndef LLORA_H
#define LLORA_H

#include <LoRa.h>

void initLoRa(long Fq);
void send(long cmd, long time, long type, long data1, long data2, long data3, long data4, long data5, long data6);

#endif
