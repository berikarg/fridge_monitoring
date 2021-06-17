#pragma once

#define GERCON_PIN GPIO_NUM_14

void gercon_init();
static void IRAM_ATTR gercon_isr(void * arg);