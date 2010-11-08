
/*
 * gpio.c
 *
 *  Created on: 14 Oct 2010
 *      Author: psampaio
 */
#define IOPIN          (*((volatile unsigned long *) 0xE0028000))
#define IOSET          (*((volatile unsigned long *) 0xE0028004))
#define IODIR          (*((volatile unsigned long *) 0xE0028008))
#define IOCLR          (*((volatile unsigned long *) 0xE002800C))

void delay()
{
	int i;

	for(i = 1000; i-- ;);
}

int main(void)
{
	IODIR = (0x3 << 16);
	for(;;) {
		IOSET = (0x3 << 16);
		delay();
		IOCLR = (0x3 << 16);
		delay();
	}
	return 0;
}
