#include "Keyboard.h"
#include "TYPES.h"
#include "LCD.h"
#include "WATCHDOG.h"
/**
 * ************************
 0 *    *    *     * MENU *
 * ************************
 1 *    *    *     *  OK  *
 * ************************
 2 *    * UP *     *CANCEL*
 * ************************
 3 *LEFT*DOWN*RIGHT* RESET*
 * ************************
 * *  0 *  1 *  2  *   3  *
 * ************************
 
 LOW_NIBBLE =  LINES
 HIGH_NIBBLE = COLUMNS
 
 BITMAP = HIGH_NIBLLE | LOW_NIBBLE
 
 MENU   = 0111 1110 = 0x7E 
 OK     = 0111 1101 = 0x7D
 CANCEL = 0111 1011 = 0x7B
 RESET  = 0111 0111 = 0x77
 ------------------
 UP     = 1101 1011 = 0xDB
 DOWN   = 1101 0111 = 0xD7
 LEFT   = 1110 0111 = 0xE7
 WRITE  = 1011 0111 = 0xB7
*/

enum KEYBOARD_KEYS{
  MENU    = 0x7E,
  OK      = 0x7D,
  CANCEL  = 0x7B,
  RESET   = 0x77,
  UP      = 0xDB,
  DOWN    = 0xD7,
  LEFT    = 0xE7,
  RIGHT   = 0xB7  
};
typedef enum KEYBOARD_KEYS KB_Key;

/*--------------------------------------------------------------------*/

typedef struct _percurso{
  DATE beginDate;
  TIME beginTime;
  U16  spentTime;//in minutes
  U16  distance; //in meters
  U8   maxSpeed; //in KM/s
  U8   averageSpeed; // in KM/s
  U32  totalDistance;
  U32  totalTime;
}Percurso,*pPercurso;

typedef struct _option{
  char* text;
  char* value;
}Option,pOption;

void printToLCD(char* line0,char* line1){
  writeLine(0,line0); writeLine(1,line1);    
}
void printDateTime(pPercurso percurso){
  char text[16];
  sprintf(text,"%4.4d-%2.2d-%2.2d %2.2d:%2.2d",percurso->beginDate.year,percurso->beginDate.month,percurso->beginDate.day,percurso->beginTime.hour,percurso->beginTime.minute);
  printToLCD("Route Start Date",text);
}
void printDistance(pPercurso percurso){
  char text[16];  
  sprintf(text,"%3.3d Km/h",percurso->distance);
  printToLCD("Distance Made",text);
}
void printTime(pPercurso percurso){
  char text[16];  
  sprintf(text,"%5.5dH %2.2M",percurso->spentTime/60,percurso->spentTime%60);
  printToLCD("Time Spent",text);

}
void printMaxSpeed(pPercurso percurso){
  char text[16];
  sprintf(text,"%3.3d Km/h",percurso->maxSpeed);
  printToLCD("Max Speed",text);

}
void printAvgSpeed(pPercurso percurso){
  char text[16];
  sprintf(text,"%3.3d Km/h",percurso->averageSpeed);
  printToLCD("Average Speed",text);
}
void printTotalDistance(pPercurso percurso){
  char text[16];
  sprintf(text,"%3.3d Km",percurso->totalDistance);
  printToLCD("Total Distance",text);
}
void printTotalTime(pPercurso percurso){
  char text[16];
  sprintf(text,"%5.5dH %2.2M",percurso->totalTime/60,percurso->totalTime%60);
  printToLCD("Total Time Spent",text);
}

#define __MAX_FUNCTION_MENU_1__  7
void (*fxM1[__MAX_FUNCTION_MENU_1__]) (pPercurso percurso) = 
{
  printDateTime,
  printDistance,
  printTime,
  printMaxSpeed,
  printAvgSpeed,
  printTotalDistance,
  printTotalTime
};

typedef enum _status {MAIN=0,OK,MENU,RESET,FULLRESET,READ,WRITE,WAIT} Status;

void menu1(pPercurso percurso){
  int idx = 0;
  Status stat = OK;
  KB_Key key;
  while(1){
    fxM1[idx](percurso);
    if (hasKey() ){
      if (key = getBitMap) == OK || key == RIGHT || key == DOWN)
        idx = (++idx) % __MAX_FUNCTION_MENU_1__;   
      if (key == LEFT || key == UP)
        idx = (--idx) % __MAX_FUNCTION_MENU_1__;   
      else if ( key == CANCEL)
        return;   
     WD_RESETENABLE();
    }
   timer_sleep_miliseconds(pTIMER0, 200); 
  }
}
/*--------------------------------------------------------------------*/
 void setClock(pPercurso percurso);
 void resetTotal(pPercurso percurso){
    percurso->totalDistance = 0;
    percurso->totalTime =0;
    printToLCD("Total Time and","Distance reseted");
 }
 
 #define __MAX_FUNCTION_MENU_2__ 2
 
 void (*fxM2[__MAX_FUNCTION_MENU_2__]) (pPercurso percurso) = 
{
  setClock,
  resetTotal
};

void menu2(pPercurso percurso){
  int idx = 0;
  Status stat = OK;
  KB_Key key;
  while(1){
    fxM2[idx](percurso);
    if (hasKey() ){
      if (key = getBitMap) == OK || key == RIGHT || key == DOWN)
        idx = (++idx) % __MAX_FUNCTION_MENU_2__;   
      if (key == LEFT || key == UP)
        idx = (--idx) % __MAX_FUNCTION_MENU_2__;   
      else if ( key == CANCEL)
        return;  
    
     WD_RESETENABLE();
    }
   timer_sleep_miliseconds(pTIMER0, 200); 
  }
}
