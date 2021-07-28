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
const int timer_interval = 30000;    // time between each HTTP POST temperature
unsigned long previous_millis = 0;   // last time temperature was sent
const String fridge_id = "Fridge_1"; // used to identify location, will be sent with photos

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable broen-out detector
  Serial.begin(115200);

  temperature_sensor_init();
  
  wifi_init();

  camera_setup();

  gercon_init();

  send_photo(); 
}

void loop() {
  unsigned long current_millis = millis();
  if (current_millis - previous_millis >= timer_interval) 
  {
    float temperature = get_temperature();
    Serial.print("Temperature: ");
    Serial.println(temperature);
    send_temperature(temperature);
    previous_millis = current_millis;
  }

  if (check_gercon)
  {
    delay(GERCON_DELAY);
    if (digitalRead(GERCON_PIN)) // door has been opened
        is_door_open = true;
    else if (!digitalRead(GERCON_PIN)) // door has been closed 
        is_door_open = false;
    send_door_status();
    send_photo();
    check_gercon = false;
  }
}
