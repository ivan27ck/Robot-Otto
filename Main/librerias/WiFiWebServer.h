#ifndef WIFI_WEB_SERVER_H
#define WIFI_WEB_SERVER_H

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>

// Declaración de funciones
void setupWiFi(const char* ssid, const char* password, IPAddress local_IP, IPAddress gateway, IPAddress subnet);
void setupWebServer();
void handleRoot();
void handleCommand();

// Declaración del servidor web
extern WebServer server;

// Variables globales
extern bool baile;
extern bool caminar;
extern bool isInitialized;

#endif

