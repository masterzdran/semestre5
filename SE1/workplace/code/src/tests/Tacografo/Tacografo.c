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

static percurso_init(pPercurso percurso){
	percurso->beginDate.year=2011;
	percurso->beginDate.month=02;
	percurso->beginDate.day=04;
	percurso->beginTime.hour=13;
	percurso->beginTime.minute=0;
	percurso->beginTime.second=0;
	percurso->spentTime=0;
	percurso->distance=0;
	percurso->averageSpeed=0;
	percurso->totalDistance=0;
	percurso->totalTime=0;
  
}
extern Option menu2Options[__MAX_FUNCTION_MENU_2__];
extern Option menu1Options[__MAX_FUNCTION_MENU_1__];

static int tickCount;
Percurso percurso;

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
  TIMER_init(pTIMER0,58982400/MILI);
  LCD_init(pTIMER1);
  keyboard_init(pTIMER1); 
  //WATCHDOG_init(0x0FFFFFFF);
  rtc_init();
  I2C_init();
  VIC_init();
  
  VIC_ConfigIRQ(__INTERRUPT_TIMER0__,1,timer0isr);
  TIMER_ext_match_init(pTIMER0,1,__MATCH_RESET__,5000,MATCH_TOGGLE);
  TIMER_capture_init(pTIMER0,1,__CAPTURE_INTERRUPT__|__CAPTURE_RISE__,10,COUNTER_MODE_FALL);  
  interrupt_enable(); 
 
  tickCount=0;

  //to use only when compiling to ram
  pMAM->MEMORY_MAPPING_CONTROL  = __MEMORY_MAP_CONTROL_USERRAM__; 

}

//typedef enum _status {MAIN=0,OK_PRESS,MENU_PRESS,RESET_PRESS,FULLRESET,READ,WRITE,WAIT} Status;

int main(){
  Status program_status=OK_PRESS;
  KB_Key key;
  char buff[16]="                ";
  percurso_init(&percurso);
  Tacografo_init();  


  LCD_clear();
  timer_sleep_seconds(pTIMER1,1);
  while (1){
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
	  
	  
	if (keyboard_hasKey()){
		switch(key = keyboard_getBitMap()){
		  case OK:
			Menu_Generic(&percurso,menu1Options,__MAX_FUNCTION_MENU_1__);
			program_status=MENU_PRESS;
			break;
		  case MENU:
			Menu_Generic(&percurso,menu2Options,__MAX_FUNCTION_MENU_2__);
			program_status=RESET_PRESS;
			break;
		  case RESET:
			resetTotal((&percurso));
			program_status = OK_PRESS;
			break;
		  case ACCEL:
			TIMER_ext_match_changeTime(pTIMER0,1,+5);
			break;
		  case BRAKE:
		    TIMER_ext_match_changeTime(pTIMER0,1,-5);
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
		//No key present
		
	}
	//WD_reset;
  }



  return 0;
}
