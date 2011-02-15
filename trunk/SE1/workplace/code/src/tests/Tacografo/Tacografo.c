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

static int tickCount;
Percurso percurso;
U8  currentSpeed;
U32 lastDistanceTimeUpdate;
U32 lastSaveTime;


void timer0isr(void){
	U32 irq_status = pVIC->IRQStatus;
	if (irq_status & __INTERRUPT_TIMER0_MASK__){
		tickCount++;
		pVIC_VECTDEFADDR->VectAddr =0;		//clear isr function address
		pTIMER0->IR |= 1<<5;				//clear timer0 CR1 interrupt request
		enableIRQ( __INTERRUPT_TIMER0__ );
	}
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
  //35297122 - time needed to run at a 1 km/h speed
  TIMER_ext_match_init(pTIMER0,1,__MATCH_RESET__,3597122,MATCH_TOGGLE);
  TIMER_capture_init(pTIMER0,1,__CAPTURE_INTERRUPT__|__CAPTURE_RISE__,10,COUNTER_MODE_FALL);  
  interrupt_enable(); 
 
  tickCount=0;

  //to use only when compiling to ram
  pMAM->MEMORY_MAPPING_CONTROL  = __MEMORY_MAP_CONTROL_USERRAM__; 

}

void updateSpeed(){
  if (currentSpeed==0){
	//estava parado
	lastDistanceTimeUpdate=percurso_addStopTime(&percurso, lastDistanceTimeUpdate);
  }else{
	//estava a andar
	lastDistanceTimeUpdate=percurso_addSpentTime(&percurso, lastDistanceTimeUpdate);
	percurso_updateDistance(&percurso, tickCount);
	tickCount=0;
	percurso_updateAverageSpeed(&percurso);
  }
  currentSpeed=3600000/timer_capture1_time(pTIMER0);
  timer_capture1_time(pTIMER0)=0;
  percurso_testAndSetMaxSpeed(&percurso, currentSpeed);
  
}

void saveData(){
	
}
//typedef enum _status {MAIN=0,OK_PRESS,MENU_PRESS,RESET_PRESS,FULLRESET,READ,WRITE,WAIT} Status;

int main(){
  Status program_status=OK_PRESS;
  KB_Key key;
  char buff[16]="                ";

  U16 lastSaveDistance = percurso.distance;
  U32 lastSpeedCheckTS=timer_now(pTIMER1);
  currentSpeed=0;
  lastDistanceTimeUpdate = Clock_getCurrentTimeSeconds();
  lastSaveTime = lastDistanceTimeUpdate;
 
  percurso_init(&percurso,0,0);
  Tacografo_init();  


  LCD_clear();
  timer_sleep_seconds(pTIMER1,1);
  while (1){
	Menu_Generic(&percurso,&menu1Options,7);
    LCD_posCursor(0,0);
    sprintf((char*)(&buff),"%12d-%3d",tickCount,pTIMER0->TC);
    LCD_writeString((char*)&buff);
    LCD_posCursor(1,0);
	sprintf((char*)(&buff),"%16d",pTIMER0->CR1);
    LCD_writeString((char*)&buff);
	//WD_FEED();
	timer_sleep_miliseconds(pTIMER1,1);
  }
  
  while (true){
	if (timer_elapsed(pTIMER1,lastSpeedCheckTS)>2000000){
	  updateSpeed();
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
			TIMER_ext_match_changeTime(pTIMER0,1,+5);
			break;
		  case ACCEL1:
			TIMER_ext_match_changeTime(pTIMER0,1,+1);
			break;
		  case BRAKE5:
		    TIMER_ext_match_changeTime(pTIMER0,1,-5);
		    break;
		  case BRAKE1:
		    TIMER_ext_match_changeTime(pTIMER0,1,-1);
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
	  if ((percurso.distance-lastSaveDistance)>1000 || timer_elapsed(pTIMER1,lastSpeedCheckTS)>1000000*60){
	    saveData();
		lastSaveDistance=percurso.distance;
	  }
    }
	//WD_reset;
	timer_sleep_miliseconds(pTIMER1,100);
  }



  return 0;
}
