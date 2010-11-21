#ifndef LED_H
#define LED_H

#include "../LPC2106/LPC2106.h"

//LED PIN
#define LED_PIN	13

void led_init();
void led_write(int i);

#endif
