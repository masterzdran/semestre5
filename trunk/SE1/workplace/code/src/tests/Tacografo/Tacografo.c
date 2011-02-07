#include "Tacografo.h"
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
Percurso percurso;
void Tacografo_init(){
    //initiate all need modules
}


int main(){
  Status program_status=OK_PRESS;
  percurso_init(&percurso);
  gpio_init(0,0);
  timer_init(pTIMER1,58982400/MICRO);
  timer_init(pTIMER0,58982400/MICRO);
  LCD_init(pTIMER1);
  keyboard_init(pTIMER1);
  rtc_init();
  
  while (true){    
    switch(program_status){
      case OK_PRESS:
        Menu_Generic(&percurso,menu1Options,__MAX_FUNCTION_MENU_1__);
        program_status=MENU_PRESS;
        break;
      case MENU_PRESS:
        Menu_Generic(&percurso,menu2Options,__MAX_FUNCTION_MENU_2__);
        program_status=RESET_PRESS;
        break;
      case RESET_PRESS:
        resetTotal((&percurso));
        program_status = OK_PRESS;
        break;
      case WAIT:
      
        break;
    }
  }



  return 0;
}
