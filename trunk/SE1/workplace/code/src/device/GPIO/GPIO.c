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
static void gpio_PINSEL0(U32 mask){ 
 __PINSEL0__ &= ~mask; 
}

/*The PINSEL1 register controls the functions of the pins 16-31*/
static void gpio_PINSEL1(U32 mask){   
  __PINSEL1__ &= ~mask;
}

void gpio_init(U32 pinsel0_mask,U32 pinsel1_mask){
  gpio_PINSEL0(pinsel0_mask);
  gpio_PINSEL1(pinsel1_mask);
} 

void gpio_write(U32 mask, U32 value){
  pGPIO->IOCLR |= mask & value;
  pGPIO->IOSET |= mask & value;    
}
/*
 *Table 62. (Page 72)
 * GPIO port 0 Direction register (IO0DIR - address 0xE002 8008) bit description
 * 0 Controlled pin is input.
 * 1 Controlled pin is output.
 * */
void gpio_set_direction(U32 mask, U8 direction){
  if (direction)
    pGPIO->IODIR |= mask;
  else
    pGPIO->IODIR &= ~mask;
}

void gpio_clear(U32 mask, U32 value){
  pGPIO->IOCLR |= mask & value;
}

U32 gpio_read(U32 mask){
    return  pGPIO->IOPIN & mask;
}
