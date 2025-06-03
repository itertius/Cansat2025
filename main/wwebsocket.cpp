#include "wwebsocket.h"

WebSocketsServer ws(81); 

void initWebSocket() {
  ws.begin();
}

void handSocket() {
  ws.loop();
}

void pushserver(String payload) {
  if (payload.length() > 0) {
    ws.broadcastTXT(payload);
  }
}