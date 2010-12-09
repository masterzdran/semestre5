#ifndef GPIO_H
#define GPIO_H
#include "LPC2106.h"

#define pGPIO 	((pLPC_GPIO)	0xE0028000)

typedef struct _GPIO{
	U32 IOPIN;	/* GPIO Port Pin value register.             0xE002 8000*/
	U32 IOSET;	/* GPIO Port Output Set register.            0xE002 8004*/
	U32 IODIR;	/* GPIO Port Direction control register.     0xE002 8008*/
	U32 IOCLR;	/* GPIO Port Output Clear register.          0xE002 800C*/
}LPC_GPIO,*pLPC_GPIO;

U32 gpio_read(U32 mask);
void gpio_clear(U32 mask);
void gpio_write(U32 mask, U32 value );
void gpio_PINSEL1();
void gpio_PINSEL0();

#endif //GPIO_H
