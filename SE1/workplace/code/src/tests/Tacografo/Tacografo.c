#include "Tacografo.h"
#include "LCD.h"
#include "GPIO.h"
#include "TIMER.h"
#include "RTC.h"
#include "Clock.h"
#include "Keyboard.h"
#include "VIC.h"
#include "WATCHDOG.h"
#include "I2C.h"
#include "TYPES.h"
#include "startosc.h"
#include "stdio.h"
#include "Menu.h"
#include "MenuFunctions.h"
#include "EEPROM.h"
#include "Percurso.h"


extern Option menu2Options[__MAX_FUNCTION_MENU_2__];
extern Option menu1Options[__MAX_FUNCTION_MENU_1__];

static U32 tickCount;	//nº de ticks detectados
static U32 tickTime;	//tempo acumulado entre ticks consecutivos

void timer0isr(void){
	//U32 irq_status = pVIC->IRQStatus;
	//if (irq_status & __INTERRUPT_TIMER0_MASK__){
	timer_reset(pTIMER0);
	tickCount++;
	tickTime+=pTIMER0->CR1;
	pVIC_VECTDEFADDR->VectAddr =0;		     //clear isr function address
	pTIMER0->IR |= __INTERRUPT_TIMER0_MASK__;//clear timer0 CR1 interrupt request
	enableIRQ( __INTERRUPT_TIMER0__ );
	//}
}

void Tacografo_init(){
  gpio_init(0,0);
  TIMER_init(pTIMER1,58982400/MICRO);
  TIMER_init(pTIMER0,58982400/MICRO);
  LCD_init(pTIMER1);
  keyboard_init(pTIMER1); 
  //WATCHDOG_init(0x0FFFFFFF);
  rtc_init();
  I2C_init();
  VIC_init();
  
  VIC_ConfigIRQ(__INTERRUPT_TIMER0__,1,timer0isr);
  //3597122 - time needed to run at a 1 km/h speed
  TIMER_capture_init(pTIMER0,1,__CAPTURE_INTERRUPT__|__CAPTURE_FALL__,1,COUNTER_MODE_FALL);  
  TIMER_ext_match_init(pTIMER0,1,__MATCH_RESET__,3597122,MATCH_TOGGLE);
  interrupt_enable(); 
 
  tickCount=0;
  tickTime=0;
  //to use only when compiling to ram
  pMAM->MEMORY_MAPPING_CONTROL  = __MEMORY_MAP_CONTROL_USERRAM__; 

}

void updateSpeed(Percurso* percurso){
  if (tickTime){
	//is running
	percurso_addSpentTime(percurso, tickTime/1000);
	percurso_updateDistance(percurso, tickCount*__METERS_PER_TICK__);
	//speed in km/h
	percurso_setCurrentSpeed(percurso, ((tickCount * __METERS_PER_TICK__)*3600000)/tickTime);
	tickCount=0;
	tickTime=0;
	percurso_updateAverageSpeed(percurso);
  }else{
	//is stopped
	percurso_addStopTime(percurso, (pTIMER0->TC)/1000);
	timer_reset(pTIMER0);
	percurso_setCurrentSpeed(percurso,0);
  }
}

void saveData(){
	
}
//typedef enum _status {MAIN=0,OK_PRESS,MENU_PRESS,RESET_PRESS,FULLRESET,READ,WRITE,WAIT} Status;

int main(){
  Percurso percurso;
  U32 lastSaveTime;
  
  KB_Key key;
  char buff[16]="                ";

  U16 lastSaveDistance;
  percurso_init(&percurso,0,0);
  Tacografo_init();  
  
  lastSaveTime = rtc_getCurrentTime();
  lastSaveDistance = percurso.distance;

  LCD_clear();
  timer_sleep_seconds(pTIMER1,1);
  TIMER_ext_match_start(pTIMER0);
  
 /* 
  while (1){
	//Menu_Generic(&percurso,&menu1Options,7);
    sprintf((char*)(&buff),"%12d-%3d",tickTime,tickCount);
    LCD_writeLine(0,(char*)&buff);
	TIMER_ext_match_stop(pTIMER0);
	timer_sleep_miliseconds(pTIMER1,4000);
    sprintf((char*)(&buff),"%12d-%3d",tickTime,tickCount);
	LCD_writeLine(0,(char*)&buff);
	TIMER_ext_match_start(pTIMER0);
	sprintf((char*)(&buff),"%12d-%3d",tickTime,tickCount);
    LCD_writeLine(0,(char*)&buff);
	TIMER_ext_match_changeTime(pTIMER0,1,+20);
	while(1){
	sprintf((char*)(&buff),"%12d-%3d",tickTime,tickCount);
    LCD_writeLine(0,(char*)&buff);
	//WD_FEED();
	timer_sleep_miliseconds(pTIMER1,2000);
	}
  }
*/

  while (true){
	if (tickTime > __MAX_SPEED_UPDATE_TIMEOUT__ || (pTIMER0->TC) > __TICK_STOPPED_TIMEOUT__){
	  updateSpeed(&percurso);
	}
	if (keyboard_hasKey()){
		switch(key = keyboard_getBitMap()){
		  case OK:
			Menu_Generic(&percurso,menu1Options,__MAX_FUNCTION_MENU_1__);
			break;
		  case MENU:
			Menu_Generic(&percurso,menu2Options,__MAX_FUNCTION_MENU_2__);
			break;
		  case RESET:
			resetTotal((&percurso));
			break;
		  case ACCEL5:
			TIMER_ext_match_changeTime(pTIMER0,1,1,+5);
			break;
		  case ACCEL1:
			TIMER_ext_match_changeTime(pTIMER0,1,1,+1);
			break;
		  case BRAKE5:
		    TIMER_ext_match_changeTime(pTIMER0,1,0,5);
		    break;
		  case BRAKE1:
		    TIMER_ext_match_changeTime(pTIMER0,1,0,1);
		    break;
		  case START:
		    TIMER_ext_match_start(pTIMER0);
		    break;
		  case STOP:
		    TIMER_ext_match_stop(pTIMER0);
		    break;
		  default:
		    //do nothing
		  	break;
		}
	}else{
	  if ((percurso.distance-lastSaveDistance > __MAX_SAVE_DISTANCE__) || (rtc_secondsElapsed(lastSaveTime) > __MAX_SAVE_TIMEOUT__)){
	    saveData(&percurso);
		lastSaveTime=rtc_getCurrentTime();
	  }
	  sprintf((char*)(&buff),"%11d km/h",percurso.currentSpeed);
	  LCD_writeLine(1,buff);
    }
	//WD_reset;
	timer_sleep_miliseconds(pTIMER1,300);
  }

  return 0;
}

