#ifndef LPC2106_H
#define LPC2106_H

#define FOSC 14745600
#define PLL_M 4
#define PLL_P 2
#define CCLK (FOSC * PLL_M)
#define PCLK (CCLK / 4)

//GPIO
#define	PINSEL0     0xE002C000
#define	PINSEL1  	0xE002C004
#define	IOPIN	 	0xE0028000
#define	IOSET	 	0xE0028004
#define	IODIR	 	0xE0028008
#define	IOCLR	 	0xE002800C



U32 timer_read();
void timer_init();

#endif
