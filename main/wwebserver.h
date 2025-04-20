#ifndef WWEBSERVER_H
#define WWEBSERVER_H

#include <Arduino.h>
#include <HTTP_Method.h>
#include <Middlewares.h>
#include <Uri.h>
#include <WebServer.h>

extern WebServer server;

void initWebserver();
void handRoot();
void handClient();

#endif