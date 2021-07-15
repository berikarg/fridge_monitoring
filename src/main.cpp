/*
Fridge monitoring system
Features:
1) Periodically collects temperature, sends it to a Raspberry Pi, which in turn sends it to Qaratal server
2) Senses when fridge's door opens and closes, takes a picture each time, 
   sends it to a Raspberry Pi, which in turn sends it to Qaratal server
*/

#include <Arduino.h>
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "esp_camera.h"
#include "camera.h"
#include "wifi_client.h"
#include "gercon.h"
#include "temp_sen.h"
#include "main.h"

// Globals
const int timerInterval = 30000;    // time between each HTTP POST temperature
unsigned long previousMillis = 0;   // last time temperature was sent
const String fridge_id = "Fridge_1";// used to identify location, will be sent with photos

void setup() {
  //WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); 
  Serial.begin(115200);
  
  wifi_init();

  camera_setup();

  gercon_init();

  sendPhoto(); 
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= timerInterval) 
  {
    float temperature = get_temperature();
    Serial.print("Temperature: ");
    Serial.println(temperature);
    send_temperature(temperature);
    previousMillis = currentMillis;
  }

  if (takeNewPhoto)
  {
      send_door_status();
      sendPhoto();
      takeNewPhoto = false;
  }

}
