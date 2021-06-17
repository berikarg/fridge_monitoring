#include "Arduino.h"
#include "camera.h"
#include "gercon.h"

void gercon_init()
{
    pinMode(GERCON_PIN, INPUT_PULLUP);
    esp_err_t err = gpio_isr_handler_add(GERCON_PIN, gercon_isr, (void *) 3);
    if (err != ESP_OK) {
        Serial.printf("handler add failed with error 0x%x \r\n", err);
    }
    err = gpio_set_intr_type(GERCON_PIN, GPIO_INTR_NEGEDGE);
    if (err != ESP_OK) {
        Serial.printf("set intr type failed with error 0x%x \r\n", err);
    }
}

static void IRAM_ATTR gercon_isr(void * arg)
{
    takeNewPhoto = true;
}