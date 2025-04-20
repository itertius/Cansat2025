#ifndef WWEBSOCKET_H
#define WWEBSOCKET_H

#include <Arduino.h>
#include <WebSocketsServer.h>

extern WebSocketsServer ws;

void initWebSocket();
void pushserver(String payload);
void handSocket();

#endif