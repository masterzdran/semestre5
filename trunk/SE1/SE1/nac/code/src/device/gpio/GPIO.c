#include "GPIO.h"
/*
 * Table 58. Pin function select register bits (Page 66)
 *   
 * 00 Primary (default) function, typically GPIO port 
 * 01 First alternate function 
 * 10 Second alternate function 
 * 11 Third alternate function 
 * */

/*The PINSEL0 register controls the functions of the pins 0-15*/
void gpio_PINSEL0(){ 
 __PINSEL0__ = 0x0; 
}

/*The PINSEL1 register controls the functions of the pins 16-31*/
void gpio_PINSEL1(){   
  __PINSEL1__ = 0x0;
}
/*
 *Table 62. (Page 72)
 * GPIO port 0 Direction register (IO0DIR - address 0xE002 8008) bit description
 * 0 Controlled pin is input.
 * 1 Controlled pin is output.
 * */
void gpio_write(U32 mask, U32 value ){
  pGPIO->IODIR = mask;
  pGPIO->IOSET = ~(value & mask);  
}

void gpio_clear(U32 mask){
  pGPIO->IOCLR = mask; 
}

U32 gpio_read(U32 mask){
	pGPIO->IODIR = ~mask;
    return  ~(pGPIO->IOPIN& mask);
}
