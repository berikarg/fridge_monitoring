#include <Arduino.h>
#include <WiFi.h>
#include "wifi_client.h"

//const char* ssid = "Galaxy S20798e";
//const char* password = "gfmu3112";

//const char* ssid = "HP2400";
//const char* password = "018384584qwer";

const char* ssid = "Lucent";
const char* password = "018384584";

//String serverName = "192.168.202.12";   // REPLACE WITH YOUR Raspberry Pi IP ADDRESS
//String serverName = "192.168.5.147";
String serverName = "192.168.1.64"; 
String serverPath = "/upload.php";     // The default serverPath should be upload.php

const int serverPort = 80;

WiFiClient client;

void wifi_init()
{
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("ESP32-CAM IP Address: ");
  Serial.println(WiFi.localIP());
}