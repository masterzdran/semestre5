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


extern Option menu2Options[__MAX_FUNCTION_MENU_2__];
extern Option menu1Options[__MAX_FUNCTION_MENU_1__];

static U32 tickCount;	//nº de ticks detectados
static U32 tickTime;	//tempo acumulado entre ticks consecutivos


const char timeFormat[30]="%4.4d-%2.2d-%2.2d %2.2d:%2.2d";
#define __PRINT_PERCURSO_DATE_TIME__ dateTime.date.year,dateTime.date.month,dateTime.date.day,dateTime.time.hour,dateTime.time.minute
#define __ONE_KM_PER_HOUR__   3597122
#define __START_DISTANCE__    0
#define __START_TIME__        0

void timer0isr(void){
	timer_reset(pTIMER0);
	tickTime+=pTIMER0->CR1;
  tickCount++;
	pVIC_VECTDEFADDR->VectAddr =0;		       //clear isr function address
	pTIMER0->IR |= __INTERRUPT_TIMER0_MASK__;//clear timer0 CR1 interrupt request
	enableIRQ( __INTERRUPT_TIMER0__ );
}



void Tacografo_init(){
  tickCount=0;
  tickTime=0;
 
  TIMER_init(pTIMER1,58982400/MICRO);
  TIMER_init(pTIMER0,58982400/MICRO);
  LCD_init(pTIMER1);
  keyboard_init(pTIMER1); 
  rtc_init();
  VIC_init();
  VIC_ConfigIRQ(__INTERRUPT_TIMER0__,1,timer0isr);

  //3597122 - time needed to run at a 1 km/h speed
  TIMER_capture_init(pTIMER0,1,__CAPTURE_INTERRUPT__|__CAPTURE_FALL__,1,COUNTER_MODE_FALL);  
  TIMER_ext_match_init(pTIMER0,1,__MATCH_RESET__,__ONE_KM_PER_HOUR__,MATCH_TOGGLE);
  WATCHDOG_init(0x0FFFFFFF);  
  interrupt_enable(); 
 
  //to use only when compiling to ram
  //pMAM->MEMORY_MAPPING_CONTROL  = __MEMORY_MAP_CONTROL_USERRAM__; 

}


void saveData(){
  //not yet implemented
}

int main(){
  Percurso percurso;
  U32 lastSaveTime =0;
  U8 loop=5;
  DATE_TIME dateTime;
  KB_Key key;
  char buff[16]="                ";
  U8 status=0;
  U8 refresh=0;
  
  Tacografo_init();  
  percurso_init(&percurso,__START_DISTANCE__,__START_TIME__);

  LCD_clear();
  while (true){

        if (loop >= 5){
          rtc_getDateTime(&dateTime);
          sprintf((char*)(&buff),timeFormat,__PRINT_PERCURSO_DATE_TIME__);
          LCD_writeLine(0,buff);
          loop=0;
        }
          LCD_setCenter(true);
          sprintf((char*)(&buff),"[%s]%5d km/h",((status)?"ON":"OFF"),percurso.currentSpeed);
          LCD_writeLine(1,buff);
          LCD_setCenter(false);
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
            TIMER_ext_match_changeTime(pTIMER0,1,1,5);
            break;
          case ACCEL1:
            TIMER_ext_match_changeTime(pTIMER0,1,1,1);
            break;
          case BRAKE5:
            TIMER_ext_match_changeTime(pTIMER0,1,0,5);
            break;
          case BRAKE1:
            TIMER_ext_match_changeTime(pTIMER0,1,0,1);
            break;
          case START:
            TIMER_ext_match_start(pTIMER0, 1, MATCH_TOGGLE);
            TIMER_enable(pTIMER0);
            status=1;
            break;
          case STOP:
            TIMER_ext_match_stop(pTIMER0, 1, MATCH_TOGGLE);
            status=0;
            break;
          default:
            //do nothing
            break;
        }
        
      }
      ++lastSaveTime;
      if (lastSaveTime > 250){
            saveData(&percurso);
            lastSaveTime=0;
      }  
      	if (tickTime > __MAX_SPEED_UPDATE_TIMEOUT__ || (pTIMER0->TC) > __TICK_STOPPED_TIMEOUT__){
          percurso.vptr->updateSpeed(&percurso,&tickTime,&tickCount);
        }      
      timer_sleep_miliseconds(pTIMER1,200);
      ++loop;  
      WD_reset();    
  }

  return 0;
}

