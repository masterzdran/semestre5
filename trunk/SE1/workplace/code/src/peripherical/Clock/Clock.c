#include "Clock.h"
#include "Clock.h"
#include "Keyboard.h"
#include "LCD.h"
#include "WATCHDOG.h"
#include "RTC.h"
static U8 monthDays[12] ={31,28,31,30,31,30,31,31,30,31,30,31};

void format(U8 position,DATE_TIME* dateTime,U16 value){
  U8 val;
  switch (position){
      case 0:
        dateTime->date.year = (dateTime->date.year + value);
        if (dateTime->date.month == 2 && isleapYear(dateTime->date.year)){
          dateTime->date.day %=  LEAP_YEAR_FEB;
        }else{
          val = dateTime->date.month -1 ;
          dateTime->date.day %=  monthDays[ val];
        }
        break;
      case 1:
        dateTime->date.month = (dateTime->date.month + value) % MONTH_LIMIT;
        if (dateTime->date.month == 2 && isleapYear(dateTime->date.year)){
          dateTime->date.day %=  LEAP_YEAR_FEB;
        }else{
          val = dateTime->date.month -1 ;
          dateTime->date.day %=  monthDays[ val];
        }
        break;
      case 2:
        if (dateTime->date.month == 2 && isleapYear(dateTime->date.year)){
          dateTime->date.day = (dateTime->date.day + value) % LEAP_YEAR_FEB;
        }else{
          val = dateTime->date.month -1 ;
          dateTime->date.day = (dateTime->date.day + value) % monthDays[val];
        }
        break;
      case 3:
          dateTime->time.hour = (dateTime->time.hour + value) % HOUR_LIMIT;
        break;
      case 4:
          dateTime->time.minute = (dateTime->time.minute + value) % MINUTE_LIMIT;
      break;
  }
}

#define PRINT_DATE_TIME "dummy to be print"
void setClock(pPercurso percurso){
  U8 writePos[5]= {3,6,9,12,15};
  DATE_TIME dateTime;
  dateTime.date.year    = pRTC->YEAR;
  dateTime.date.month   = pRTC->MONTH;
  dateTime.date.day     = pRTC->DOM;
  dateTime.time.hour    = pRTC->HOUR;
  dateTime.time.minute  = pRTC->MIN;
  dateTime.time.second  = pRTC->SEC;
  
  KB_Key key;
  U8 position = 0;
  Bool hasNotBeenWriten = true;
  U16 val;
  while(1){
    if (hasNotBeenWriten){
      writeLine(DEFAULT_LINE_SET, PRINT_DATE_TIME);
      posCursor(DEFAULT_LINE_SET, writePos[position]) ;
      hasNotBeenWriten = false;
    }
    if (hasKey()){
      switch(key = getBitMap()){
          case OK:
            //commitDate(); 
            break;
          case LEFT:
            --position % NBR_FIELDS;
            hasNotBeenWriten = true;
            break;
          case RIGHT:
            ++position % NBR_FIELDS;
            hasNotBeenWriten = true;
            break;
          case DOWN:
            format(position, &dateTime, -1);
            hasNotBeenWriten = true;
            break;
          case UP:
            format(position, &dateTime, 1);
            hasNotBeenWriten = true;
            break;
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
