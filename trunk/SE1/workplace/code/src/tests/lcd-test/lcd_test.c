#include "LCD.h"
#include "GPIO.h"
#include "TIMER.h"
#include "RTC.h"
#include "Clock.h"
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
	kbTest();
	
	DATE_TIME date_time;
	PVOID dummy;
	setClock(dummy);
	
	
	rtc_getDateTime(&date_time);
	sprintf(buffer,"%2.2d/%2.2d:%4.4d",date_time.date.day,date_time.date.month,date_time.date.year);
	LCD_posCursor(0,0);
	LCD_writeString(buffer);
while(1){
	rtc_getDateTime(&date_time);
	sprintf(buffer,"%2.2d:%2.2d:%2.2d",date_time.time.hour,date_time.time.minute,date_time.time.second);
	LCD_posCursor(1,0);
	LCD_writeString(buffer);
	timer_sleep_miliseconds(pTIMER0,900);
}

 return 0;  
}
