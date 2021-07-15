#include <WiFi.h>
#include <HTTPClient.h>
#include "Arduino.h"
#include "camera.h"
#include "gercon.h"

bool is_door_open = false;

const String door_url = "http://192.168.1.64/post-door-status.php";
const String door_location = "Fridge 1";

void gercon_init()
{
    pinMode(GERCON_PIN, INPUT_PULLUP);
    esp_err_t err = gpio_isr_handler_add(GERCON_PIN, gercon_isr, (void *) 3);
    if (err != ESP_OK) {
        Serial.printf("handler add failed with error 0x%x \r\n", err);
    }
    err = gpio_set_intr_type(GERCON_PIN, GPIO_INTR_ANYEDGE);
    if (err != ESP_OK) {
        Serial.printf("set intr type failed with error 0x%x \r\n", err);
    }
}

static void IRAM_ATTR gercon_isr(void * arg)
{
    if (digitalRead(GERCON_PIN)) // door has been opened
    {
        is_door_open = true;
        takeNewPhoto = true;
    }
    else if (!digitalRead(GERCON_PIN)) // door has been closed 
    {
        is_door_open = false;
        takeNewPhoto = true;
    }
}

int send_door_status()
{
  String door_status;
  if(is_door_open)
    door_status = "Open";
  else
    door_status = "Closed";
    //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(door_url);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String http_request_data = "&door_location=" + door_location
                             + "&door_status=" + door_status + "";
    Serial.print("httpRequestData: ");
    Serial.println(http_request_data);
    
    // Send HTTP POST request
    int http_response_code = http.POST(http_request_data);
           
    if (http_response_code>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(http_response_code);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(http_response_code);
    }
    // Free resources
    http.end();
    return http_response_code;
  }
  Serial.println("WiFi Disconnected");
  return 0;
}