#include <Arduino.h>
#include <WiFi.h>
#include "wifi_client.h"

const char* ssid = "ENTERYOURSSIDHERE";
const char* password = "ENTERYOURPASSWORDHERE";
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
    Serial.print(WiFi.status());
    delay(500);
  }
  Serial.println();
  Serial.print("ESP32-CAM IP Address: ");
  Serial.println(WiFi.localIP());
}
