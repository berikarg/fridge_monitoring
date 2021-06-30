/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-cam-post-image-photo-server/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
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

const int timerInterval = 30000;    // time between each HTTP POST image
unsigned long previousMillis = 0;   // last time image was sent


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
  if (currentMillis - previousMillis >= timerInterval) {
    // put check temperature here
    float temperature = get_temperature();
    Serial.print("Temperature: ");
    Serial.println(temperature);
    send_temperature(temperature);
    previousMillis = currentMillis;
  }

  if (takeNewPhoto)
  {
      sendPhoto();
      takeNewPhoto = false;
  }

}
