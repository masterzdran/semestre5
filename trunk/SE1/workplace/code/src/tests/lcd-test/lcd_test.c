#include "LCD.h"
#include "GPIO.h"
#include "TIMER.h"
#include "TYPES.h"
#include "startosc.h"

#define  LCD_MASK   ((U32) 0x7F00)

int main(){
  gpio_init(0,0);
  
 // gpio_set_direction(0x1F00,GPIO_OUT);
  //gpio_clear(0x1F00,0x1F00);
  //gpio_set(0x1F00);
  timer_init(pTIMER0,58982400/MILI);
  
  
  while (1){
    gpio_set(0x2000);
    timer_sleep_miliseconds(pTIMER0,500);
    gpio_clear(0x2000);
    timer_sleep_miliseconds(pTIMER0,500);
  }
    
  //LCD_init(pTIMER0);
  
  //writeString("TESTE");
  
  
  
 return 0;  
}
