#include "LCD.h"
#include "GPIO.h"
#include "TIMER.h"
#include "RTC.h"
#include "Keyboard.h"
#include "TYPES.h"
#include "startosc.h"
#include "stdio.h"

#define  LCD_MASK   ((U32) 0x7F00)

int main(){
  char buffer[64];
  gpio_init(0,0);
  
  //gpio_set_direction(0x1F00,GPIO_OUT);
  //gpio_clear(0x1F00,0x1F00);
  //gpio_set(0x1F00);
  timer_init(pTIMER0,58982400/MICRO);
  LCD_init(pTIMER0);
  keyboard_init(pTIMER0);
  rtc_init();
  
  //U32 system_clock_pr= pTIMER0->PR;
  /*
  while (1){
    gpio_set(0x2000);
    timer_sleep_seconds(pTIMER0,2);
    gpio_clear(0x2000);
    timer_sleep_seconds(pTIMER0,4);
	
    gpio_set(0x2000);
    timer_sleep_miliseconds(pTIMER0,2000);
    gpio_clear(0x2000);
    timer_sleep_miliseconds(pTIMER0,500);
  }
   */
/*
  while(1){
	U8 key=NO_KEY;
	while((key=getKey())==NO_KEY){
		readKey();
		timer_sleep_miliseconds(pTIMER0, 50);
	}
	sprintf(buffer,"%d",key);
	writeString(buffer);
  }
*/
	
	DATE date0,date1;
	rtc_getDate(&date0);
	TIME time0,time1;
	rtc_getTime(&time0);
	
	rtc_setDate(2011,01,29);
	rtc_setTime(15,30,0);
	
	rtc_getDate(&date1);
	rtc_getTime(&time1);
	
	rtc_setHour(17);
	
	rtc_getTime(&time1);
	
 return 0;  
}
