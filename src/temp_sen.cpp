#include <OneWire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <DallasTemperature.h>
#include "wifi_client.h"
#include "temp_sen.h"

OneWire ds(TEMP_SEN_PIN); // Создаем объект OneWire для шины 1-Wire, с помощью которого будет осуществляться работа с датчиком
DallasTemperature temperature_sensor(&ds);


const String temperature_url = "http://192.168.1.64/post-temperature.php";
const String sensor_name = "DS18b20";
const String sensor_location = "Fridge 1";


void temperature_sensor_init()
{
    temperature_sensor.begin();
    temperature_sensor.setResolution(9);
}

float get_temperature()
{
    temperature_sensor.requestTemperatures();
    return temperature_sensor.getTempCByIndex(0);
}

int send_temperature(float temperature)
{
    //Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(temperature_url);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    
    // Prepare your HTTP POST request data
    String http_request_data = "&sensor=" + sensor_name + "&location=" + sensor_location
                             + "&temperature=" + String(temperature) + "";
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