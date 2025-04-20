#include "wwebsocket.h"

WebSocketsServer ws(81); 

void initWebSocket() {
  ws.begin();
}

void handSocket() {
  ws.loop();
}

void pushserver(String payload) {
  ws.broadcastTXT(payload);
}