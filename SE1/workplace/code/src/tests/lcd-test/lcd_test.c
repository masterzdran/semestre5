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
#include "VIC.h"
#include "WATCHDOG.h"


#define  LCD_MASK   ((U32) 0x7F00)

U32 x;
 
void func0(void){
    x++;
    enableIRQ( __INTERRUPT_TIMER0__ );
    pVIC_VECTDEFADDR->DefVectAddr =0; //dummy write
}


int main(){
  char buffer[64];
  U32 addr = 0x10;
  U32 addr2 = 0x10;
  char text[16]="2011-02-06 14:39";
  char buff[16]="                ";
  gpio_init(0,0);
  timer_init(pTIMER1,58982400/MICRO);
  timer_init(pTIMER0,58982400/MILI);
  LCD_init(pTIMER1);
  keyboard_init(pTIMER1);
  WATCHDOG_init(0xFFFFFFFF);
  U32 watch = WD_ISRUNNING();


  rtc_init();
  I2C_init();
  VIC_init();
  
  
  //TIMER_ext_match_init(pLPC_TIMER timer,U8 channel, U32 MatchMask, U32 countNbr,tEmrFunction emrFunction)
  TIMER_ext_match_init(pTIMER0,1,__MATCH_RESET__,1000,MATCH_TOGGLE);
  
  //TIMER_capture_init(pLPC_TIMER timer,U8 channel, U32 captureMask, U32 countNbr,tCtcrFunction ctcrFunction)
  TIMER_capture_init(pTIMER0,1,__CAPTURE_INTERRUPT__|__CAPTURE_FALL__,10,COUNTER_MODE_FALL);



  x=0;
  VIC_ConfigIRQ(__INTERRUPT_TIMER0__,0,func0);
    
  addr= pTIMER0->TC;
  LCD_clear();
  timer_sleep_seconds(pTIMER1,1);
  while (1){
    LCD_posCursor(0,0);
    //addr = timer_elapsed(pTIMER0,addr);
    addr = pTIMER0->TC;
    
    sprintf((char*)(&buff),"%16d",addr);
    LCD_writeString((char*)&buff);
    timer_sleep_seconds(pTIMER1,1);
  }
/*  
  EEPROM_init();
  LCD_posCursor(0,0);
	LCD_writeString(text);
  eeprom_write_block(addr,&text,16);
  timer_sleep_seconds(pTIMER1,2);
  eeprom_read_block(addr,buff,16);
   timer_sleep_seconds(pTIMER1,2);
  LCD_posCursor(1,0);
	LCD_writeString(buff);
  */
  
  
  
  
  
  
  
  
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
