#pragma once

#define GERCON_PIN GPIO_NUM_14

extern bool is_door_open;

void gercon_init();
static void IRAM_ATTR gercon_isr(void * arg);
int send_door_status();