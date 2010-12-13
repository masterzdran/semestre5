#include "LCD.h"
#include "GPIO.h"
#include "TIMER.h"
#include "TYPES.h"
#include "startosc.h"

#define  LCD_MASK   ((U32) 0x7F00)

int main(){
  gpio_init(0,0);
//  gpio_set_direction(0x3FF00,GPIO_OUT);
 // gpio_set(0x3FF00);
  timer_init(pTIMER0,CCLK/MICRO);
  LCD_init(pTIMER0);
  
  writeString("TESTE");
  
  
  
 return 0;  
}
