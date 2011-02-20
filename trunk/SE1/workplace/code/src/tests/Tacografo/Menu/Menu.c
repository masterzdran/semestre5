/**
#=======================================================================
# SE1   - Sistemas Embebidos 1
#-----------------------------------------------------------------------
# Turma:	LI51N
# Semestre:	Inverno 2010/2011
# Data:		Novembro/2010
#-----------------------------------------------------------------------
# Nome: 	Nuno Cancelo
# Numero:	31401
#-----------------------------------------------------------------------
# Nome:		Nuno Sousa
# Numero:	33595
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Informática e Computadores
# DEETC - Dep. de Eng. Electrónica e Telecomunicações e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
**/ 
#include "Menu.h"
#include "Keyboard.h"
#include "LCD.h"
#include "WATCHDOG.h"
#include "MenuFunctions.h"
#include "TIMER.h"
#include "RTC.h"
#include "Clock.h"
//150 = 30 segundos. Tempo de espera aproximado, por cada 200ms de sleep até tecla pressionada
#define __WAIT_PERIOD_30_Seconds__    135


Option menu2Options[__MAX_FUNCTION_MENU_2__] =
{
  {"1- Setting Clock",setClock}, 
  {"2- Reset Total",resetTotal}  
};


Option menu1Options[__MAX_FUNCTION_MENU_1__] = 
{
  {"1- Route Start",printDateTime},
  {"2- Distance Made",printDistance},
  {"3- Time Spent",printTime},
  {"4- Max Speed",printMaxSpeed},
  {"5- Average Speed",printAvgSpeed},
  {"6- Total Km",printTotalDistance},
  {"7- Total Time",printTotalTime}  
};

void Menu_Generic(PVOID course, pOption options[], U8 sizeOf){
  pPercurso percurso = (pPercurso)course;
  U32 currentTime=rtc_getCurrentTime();
  U8 elapsedTime=0;
  U8 idx = 0,bidx = -1;
  KB_Key key;
  
  
  while(1){
    if (bidx != idx){
      LCD_clear();
      LCD_writeLine(0,"Press OK or Next");
      LCD_writeLine(1,options[idx].text);
      bidx = idx;
    }
    if (keyboard_hasKey()){
      currentTime=rtc_getCurrentTime();
      switch(key = keyboard_getBitMap()){
          case OK:
            options[idx].function(percurso);
            break;
          case RIGHT:
          case DOWN:
            idx = __FX0(idx,1,sizeOf); break;
          case LEFT:
          case UP:
            idx = __FX0(idx,-1,sizeOf);    break;
          case CANCEL:
            LCD_clear();
            return;  
          default:
              //do nothing
              break;
      }
      elapsedTime=0;
    }else{
      //no key
      elapsedTime ++;
      
      if(elapsedTime >__WAIT_PERIOD_30_Seconds__){
        LCD_clear(); 
        return;
      }
      timer_sleep_miliseconds(pTIMER1, 200);
    }
    WD_reset();
  }
}


