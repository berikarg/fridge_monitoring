#pragma once

#include "DHT.h"

#define TEMP_SEN_PIN GPIO_NUM_15

void temperature_sensor_init();
float get_temperature();
int send_temperature(float temperature);