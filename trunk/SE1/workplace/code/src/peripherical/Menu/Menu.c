#include "Menu.h"
#include "Keyboard.h"
#include "LCD.h"
#include "WATCHDOG.h"
#include "MenuFunctions.h"

 
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

void Menu_Generic(pPercurso percurso, pOption options[], U8 sizeOf){
  U8 idx = 0,bidx = -1;
  KB_Key key;
  LCD_writeLine(0,"Press OK or Next");
  while(1){
    if (bidx != idx)
      LCD_writeLine(1,options[idx].text);
    bidx = idx;
    if (hasKey()){
      switch(key = getBitMap()){
          case OK:
            options[idx].function(percurso); break;
          case LEFT:
          case DOWN:
            idx = (++idx) % sizeOf;   break;
          case RIGHT:
          case UP:
            idx = (--idx) % sizeOf;    break;
          case CANCEL:
            return;  
          default:
              //do nothing
              break;
      }
     WD_RESETENABLE();
    }
   timer_sleep_miliseconds(pTIMER0, 200); 
  }
}
