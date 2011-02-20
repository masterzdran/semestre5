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
#include "Clock.h"
#include "Keyboard.h"
#include "LCD.h"
#include "WATCHDOG.h"
#include "RTC.h"
#include "stdio.h"
static U8 monthDays[12] ={31,28,31,30,31,30,31,31,30,31,30,31};
static char buffer[16];

//150 = 30 segundos. Tempo de espera aproximado, por cada 200ms de sleep até tecla pressionada
#define __WAIT_PERIOD_30_Seconds__    135
/**
 * Função que valida Data/hora, obrigando os valores a ficarem dentro dos limites 
 **/
 
#define MAX_MONTH_DAYS 31

U32 modulos(S32 value, U8 adj, S8 offset, U32 mod){
	register S8 val = value -adj + offset;
	if (val<0)
		val = mod -1;
	else if(val > mod-1)
		val -= mod;
	return val + adj;
}

void format(U8 position,DATE_TIME* dateTime,short value){
  U8 val; U8 tmp=0;
  Bool dateHasChanged= false;
  Bool isLeap = (IS_LEAP_YEAR((dateTime->date.year)))?true:false;
  switch (position){
      case 0:
        dateTime->date.year = (dateTime->date.year + value);
        dateHasChanged = true;
        isLeap = (IS_LEAP_YEAR((dateTime->date.year)))?true:false;
        break;
      case 1:
        dateTime->date.month =__FX1(dateTime->date.month,value,MONTH_LIMIT);
        dateHasChanged = true;
        break;
      case 2:
        tmp = (dateTime->date.month == 2 && (isLeap))?LEAP_YEAR_FEB : monthDays[ dateTime->date.month - 1 ];
        dateTime->date.day = __FX1(dateTime->date.day,value,tmp);
        //dateHasChanged = true;
        break;
      case 3:
        dateTime->time.hour = __FX0(dateTime->time.hour,value,HOUR_LIMIT);
        break;
      case 4:
        dateTime->time.minute = __FX0(dateTime->time.minute,value,MINUTE_LIMIT);
        break;
  }
  if (dateHasChanged){
    if (dateTime->date.month == 2 && isLeap){
      dateTime->date.day = __FX1(dateTime->date.day,0,LEAP_YEAR_FEB) 	 	;
    }else{
      val = dateTime->date.month -1 ;
      dateTime->date.day = __FX1(dateTime->date.day,0,monthDays[val]);
    }
  }
}

void setClock(PVOID course){
  U8 writePos[5]= {3,6,9,12,15};
  DATE_TIME dateTime;
  rtc_getDateTime(&dateTime);
  dateTime.time.second  = 0;
  U8 elapsedTime=0;
  KB_Key key;
  KB_Key prev_key=__NO_KEY__;
  
  char position = 0;
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
    if (keyboard_hasKey()){
      key = keyboard_getBitMap();
        switch(key){
            case OK:
              rtc_setDateTime(&dateTime); //commit dateTime
              LCD_setCursor(false,false);
              return;
            case LEFT:
              position = __FX0(position,-1,NBR_FIELDS);
              hasNotBeenWriten = true;
              break;
            case RIGHT:
              position= __FX0(position,1,NBR_FIELDS);
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
                key = __NO_KEY__;
                break;
        }
        elapsedTime=0;
      }else{
        //no key
        elapsedTime ++;
        if(elapsedTime>__WAIT_PERIOD_30_Seconds__){
          LCD_clear(); 
          return;
        } 
      }
     WD_reset();
     timer_sleep_miliseconds(pTIMER1, 200); 
  }
}

U8 Clock_timeDif(TIME* time_init, TIME* time_end, TIME* time_dif){
  U8 changeDay=0;
  S32 timeDifSeconds = Clock_timeToSecond(time_end)-Clock_timeToSecond(time_init);
  if (timeDifSeconds<0){
	timeDifSeconds+=(__SECONDS_IN_DAY__);
	changeDay=1;
  }
  time_dif->hour   = Clock_timeSecToHour(timeDifSeconds);
  time_dif->minute = Clock_timeSecToMin(timeDifSeconds);
  time_dif->second = Clock_timeSecToSec(timeDifSeconds); 
  return changeDay;
}

//diferença apenas tem em conta os dias, fazer passagem de ano
U16 Clock_dateDif(DATE* date_init, DATE* date_end){
  U16 numberDays=0;
  if (date_end->month == date_init->month){
	numberDays=date_end->day-date_init->day;
  }else{
    numberDays=monthDays[date_init->month]-date_init->day;
    numberDays+=date_end->day;
  }
  U8 aux;
  for(aux=date_init->month+1; aux<date_end->month-1;aux++){
    numberDays+=monthDays[aux];
  }
  return numberDays;
}
