#include "led.h"

/* init GPIO for led on LED_PIN and make sure it is off*/
void led_init(){
	io_write_u32(PINSEL0, 0);
	io_write_u32(IODIR, 1 << LED_PIN);
	io_write_u32(IOCLR, 1 << LED_PIN);
}

void led_write(int i){
	if(i)
		io_write_u32(IOSET, 1 << LED_PIN);
	else
		io_write_u32(IOCLR, 1 << LED_PIN);
}
