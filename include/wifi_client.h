#pragma once
#include <Arduino.h>
#include <WiFi.h>

extern const char* ssid;
extern const char* password;

extern String server_name;
extern String serverPath;

extern const int serverPort;

extern WiFiClient client;

void wifi_init();