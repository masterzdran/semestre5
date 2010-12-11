#include "LCD.h"
#include "GPIO.h"
#include "TIMER.h"
#include "TYPES.h"
#include "startosc.h"

#define  LCD_MASK   ((U32) 0x7F0)

int main(){
  gpio_init(0,0);
  timer_init(pTIMER0,CCLK);
  LCD_init(pTIMER0);
  
  writeString("TESTE");
  
  
  
 return 0;  
}
