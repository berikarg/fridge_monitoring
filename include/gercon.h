#pragma once

#define GERCON_PIN GPIO_NUM_14
#define GERCON_DELAY 200            // delay before cheking gercon, sort of debounce

extern bool is_door_open;
extern bool check_gercon;

void gercon_init();
static void IRAM_ATTR gercon_isr(void * arg);
int send_door_status();