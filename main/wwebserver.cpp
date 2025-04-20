#include "webpage.h"
#include "wwebserver.h"

WebServer server(80);

void handRoot() {
  server.send(200, "text/html", webpage);
}

void initWebserver() {
  server.on("/", handRoot);
  server.begin();
}

void handClient() {
  server.handleClient();
}
