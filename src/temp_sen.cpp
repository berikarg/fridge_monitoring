#include <OneWire.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "wifi_client.h"
#include "temp_sen.h"

OneWire ds(TEMP_SEN_PIN); // Создаем объект OneWire для шины 1-Wire, с помощью которого будет осуществляться работа с датчиком

const String temperature_url = "http://192.168.1.64/post-esp-data.php";
const String api_key_value = "tPmAT5Ab3j7F9";
const String sensor_name = "DS18b20";
const String sensor_location = "Fridge 1";

float get_temperature()
{
  // Определяем температуру от датчика DS18b20
  byte data[2]; // Место для значения температуры
  
  ds.reset(); // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
  ds.write(0xCC); // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство 
  ds.write(0x44); // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память
  
  delay(1000); // Микросхема измеряет температуру, а мы ждем.  
  
  ds.reset(); // Теперь готовимся получить значение измеренной температуры
  ds.write(0xCC); 
  ds.write(0xBE); // Просим передать нам значение регистров со значением температуры
 
  // Получаем и считываем ответ
  data[0] = ds.read(); // Читаем младший байт значения температуры
  data[1] = ds.read(); // А теперь старший
 
  // Формируем итоговое значение: 
  //    - сперва "склеиваем" значение, 
  //    - затем умножаем его на коэффициент, соответсвующий разрешающей способности (для 12 бит по умолчанию - это 0,0625)
  float temperature =  ((data[1] << 8) | data[0]) * 0.0625;
  return temperature;
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
    String http_request_data = "api_key=" + api_key_value + "&sensor=" + sensor_name
                          + "&location=" + sensor_location + "&value1=" + String(temperature) + "";
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