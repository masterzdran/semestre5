#include "LCD.h"
#include "GPIO.h"
#include "TIMER.h"
#include "RTC.h"
#include "Clock.h"
#include "Keyboard.h"
#include "TYPES.h"
#include "startosc.h"
#include "stdio.h"
#include "Menu.h"
#include "MenuFunctions.h"


#define  LCD_MASK   ((U32) 0x7F00)

int main(){
  char buffer[64];
  gpio_init(0,0);
  timer_init(pTIMER0,58982400/MICRO);
  LCD_init(pTIMER0);
  keyboard_init(pTIMER0);
  rtc_init();
  
//	kbTest();
/*	
	DATE_TIME date_time;
	PVOID dummy;
	setClock(dummy);
	
	LCD_clear();
	rtc_getDateTime(&date_time);
	sprintf(buffer,"%2.2d/%2.2d/%4.4d",date_time.date.day,date_time.date.month,date_time.date.year);
	LCD_posCursor(0,0);
	LCD_writeString(buffer);
	timer_sleep_seconds(pTIMER0,1);
	rtc_getDateTime(&date_time);
	sprintf(buffer,"%2.2d/%2.2d/%4.4d",date_time.date.day,date_time.date.month,date_time.date.year);
	LCD_posCursor(0,0);
	LCD_writeString(buffer);
		timer_sleep_seconds(pTIMER0,1);
while(1){
	rtc_getDateTime(&date_time);
	sprintf(buffer,"%2.2d:%2.2d:%2.2d",date_time.time.hour,date_time.time.minute,date_time.time.second);
	LCD_posCursor(1,0);
	LCD_writeString(buffer);
	timer_sleep_miliseconds(pTIMER0,800);
}
*/
	
	Percurso p;
	p.beginDate.year=2011;
	p.beginDate.month=02;
	p.beginDate.day=04;
	p.beginTime.hour=13;
	p.beginTime.minute=0;
	p.beginTime.second=0;
	p.spentTime=3;
	p.distance=5;
	p.averageSpeed=7;
	p.totalDistance=9;
	p.totalTime=11;
 
 static Option menu2Options[__MAX_FUNCTION_MENU_2__] =
{
  {"1- Setting Clock",setClock}, 
  {"2- Reset Total",resetTotal}  
};


static Option menu1Options[__MAX_FUNCTION_MENU_1__] = 
{
  {"1- Route Start",printDateTime},
  {"2- Distance Made",printDistance},
  {"3- Time Spent",printTime},
  {"4- Max Speed",printMaxSpeed},
  {"5- Average Speed",printAvgSpeed},
  {"6- Total Km",printTotalDistance},
  {"7- Total Time",printTotalTime}  
};
	while(1){
		Menu_Generic(&p,&menu1Options,7);
	}
 
 return 0;  
}
