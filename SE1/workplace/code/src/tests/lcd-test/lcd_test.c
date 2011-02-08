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
#include "I2C.h"
#include "EEPROM.h"


#define  LCD_MASK   ((U32) 0x7F00)

int main(){
  char buffer[64];
  U32 addr = 0x10;
  U32 addr2 = 0x10;
  char text[16]="2011-02-06 14:39";
  char buff[16]="                ";
  gpio_init(0,0);
  timer_init(pTIMER1,58982400/MICRO);
  timer_init(pTIMER0,58982400/MICRO);
  LCD_init(pTIMER1);
  keyboard_init(pTIMER1);
  rtc_init();
  I2C_init();
  
  /*
  timer_set_match_register((500000),matchUsed);
	timer_set_match_control(match_reset, matchUsed, true);
	timer_set_xMatch_control(xmatch_toggle, matchUsed);
  */
/*  
  TIMER_ext_match_init(pTIMER0,MAT01,__RESET_MR1__,10000000);
  TIMER_capture_init(pTIMER0,CAP01,__CAP1_MSK__,1000000);
  addr= pTIMER0->TC;
  LCD_clear();
  timer_sleep_seconds(pTIMER1,1);
  while (1){
    LCD_posCursor(0,0);
    addr = timer_elapsed(pTIMER0,addr);
    
    sprintf(&buff,"%16d",addr);
    LCD_writeString(&buff);
    timer_sleep_seconds(pTIMER1,1);
  }*/
  
  EEPROM_init();
  LCD_posCursor(0,0);
	LCD_writeString(text);
  eeprom_write_block(addr,&text,16);
  timer_sleep_seconds(pTIMER1,2);
  eeprom_read_block(addr,buff,16);
   timer_sleep_seconds(pTIMER1,2);
  LCD_posCursor(1,0);
	LCD_writeString(buff);
  
  
  
  
  
  
  
  
  
//	kbTest();
	
//	DATE_TIME date_time;
//	PVOID dummy;
//	setClock(dummy);
/*	
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
*/ 
 return 0;  
}
