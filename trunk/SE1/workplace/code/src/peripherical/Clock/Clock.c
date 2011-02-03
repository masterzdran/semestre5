#include "Clock.h"
#include "Keyboard.h"
#include "LCD.h"
#include "WATCHDOG.h"
#include "RTC.h"
#include "stdio.h"
static U8 monthDays[12] ={31,28,31,30,31,30,31,31,30,31,30,31};
static char buffer[16];
/**
 * Função que valida Data/hora, obrigando os valores a ficarem dentro dos limites 
 **/
 
#define __FX(A,B,C)   ((A - 1 + B) % C + 1) //Because do not start at 0
#define MAX_MONTH_DAYS 31

void format(U8 position,DATE_TIME* dateTime,U16 value){
  U8 val;
  Bool dateHasChanged= false;
  switch (position){
      case 0:
        dateTime->date.year = (dateTime->date.year + value);
        dateHasChanged = true;
        break;
      case 1:
        //dateTime->date.month = (dateTime->date.month -1  + value) % MONTH_LIMIT + 1;
        dateTime->date.month = __FX(dateTime->date.month,value,MONTH_LIMIT);
        dateHasChanged = true;
      case 2:
        //dateTime->date.day = (dateTime->date.day -1 + value) % MONTH_LIMIT +1;
        dateTime->date.day = __FX(dateTime->date.day,value,MAX_MONTH_DAYS);
        dateHasChanged = true;
        break;
      case 3:
          dateTime->time.hour = (dateTime->time.hour + value) % HOUR_LIMIT;
        break;
      case 4:
          dateTime->time.minute = (dateTime->time.minute + value) % MINUTE_LIMIT;
      break;
  }
  if (dateHasChanged){
    if (dateTime->date.month == 2 && IS_LEAP_YEAR((dateTime->date.year))){
      dateTime->date.day = (dateTime->date.day) % LEAP_YEAR_FEB;
    }else{
      val = dateTime->date.month -1 ;
      dateTime->date.day = (dateTime->date.day) % monthDays[val];
    }
  }
}

#define PRINT_DATE_TIME "dummy to be print"
void setClock(PVOID course){
  U8 writePos[5]= {3,6,9,12,15};
  DATE_TIME dateTime;
  dateTime.date.year    = rtc_getYear();
  dateTime.date.month   = rtc_getMonth();
  dateTime.date.day     = rtc_getDom();
  dateTime.time.hour    = rtc_getHour();
  dateTime.time.minute  = rtc_getMin();
  dateTime.time.second  = 0;
  
  KB_Key key;
  KB_Key prev_key=__NO_KEY__;
  
  U8 position = 0;
  Bool hasNotBeenWriten = true;
  U16 val;
  LCD_setCursor(true,true);
  LCD_writeString("Set date/time");
  LCD_posCursor(DEFAULT_LINE_SET, 0);
  while(1){
    if (hasNotBeenWriten){
      sprintf(buffer,"%4.4d-%2.2d-%2.2d %2.2d:%2.2d",dateTime.date.year,dateTime.date.month,dateTime.date.day,dateTime.time.hour,dateTime.time.minute);
      LCD_posCursor(DEFAULT_LINE_SET, 0);
	  LCD_writeString(buffer);
      LCD_posCursor(DEFAULT_LINE_SET, writePos[position]);
      hasNotBeenWriten = false;
    }
    if (hasKey()){
      key = getBitMap();
      if (key != prev_key){
        switch(key){
            case OK:
              rtc_setDateTime(&dateTime); //commit dateTime
              break;
            case LEFT:
              position = (position==0)? NBR_FIELDS-1:--position;
              hasNotBeenWriten = true;
              break;
            case RIGHT:
              position=(++position % NBR_FIELDS);
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
          LCD_setCursor(false,false);
              return;  
            default:
                //do nothing
                break;
        }
        prev_key = key;
      }
     
     WD_RESET_ENABLE();
    }else{
      prev_key = __NO_KEY__;
    }
   timer_sleep_miliseconds(pTIMER0, 200); 
  }
}
