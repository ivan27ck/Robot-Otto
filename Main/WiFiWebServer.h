#ifndef WIFI_WEB_SERVER_H
#define WIFI_WEB_SERVER_H

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

extern WebServer server;
extern const char* ssid;
extern const char* password;

void setupWiFi();
void handleRoot();
void handleCommand();

#endif

