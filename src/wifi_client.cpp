#include <Arduino.h>
#include <WiFi.h>
#include "wifi_client.h"

//const char* ssid = "Galaxy S20798e";
//const char* password = "gfmu3112";

//const char* ssid = "HP2400";
//const char* password = "018384584qwer";

//const char* ssid = "Lucent";
//const char* password = "018384584";

const char* ssid = "test1";
const char* password = "018384584";
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
    //Serial.print(".");
    Serial.println(WiFi.status());
    delay(500);
  }
  Serial.println();
  Serial.print("ESP32-CAM IP Address: ");
  Serial.println(WiFi.localIP());
}