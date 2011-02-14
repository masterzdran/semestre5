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
#include  "startosc.h"
#include "RTC.h"
void rtc_init(){
    /*Power: In the PCONP register (Table 3–27), set bit PCRTC = 1.*/
    pPLL->CONTROL   |= PCRTC;
    pRTC->CCR       =  __CCR_CLKEN_DISABLE__|__CCR_CTCRST_ENABLE__;
    pRTC->PREINT    = LPC_PREINT;
    pRTC->PREFRAC   = LPC_PREFRAC;
    pRTC->ILR       = __ILR_RTCALF_CLEAR__|__ILR_RTCCIF_CLEAR__;
    pRTC->ILR       = __ILR_RTCALF_DISABLE__|__ILR_RTCCIF_DISABLE__;
    pRTC->CIIR      = (~(__CIIR_IMDOM__|__CIIR_IMDOW__|__CIIR_IMDOY__|__CIIR_IMHOUR__|__CIIR_IMMIN__|__CIIR_IMMON__|__CIIR_IMSEC__|__CIIR_IMYEAR__) & __CIIR_MASK__);
    pRTC->AMR       = __AMRDOM__|__AMRDOW__|__AMRDOY__|__AMRHOUR__|__AMRMIN__|__AMRMON__|__AMRSEC__|__AMRYEAR__;
    rtc_initCalendar();
    pRTC->CCR       = __CCR_CLKEN_ENABLE__|__CCR_CTCRST_DISABLE__;
}

void rtc_getDate(DATE* date){
    date->year   = rtc_getYear();
    date->month  = rtc_getMonth();
    date->day    = rtc_getDom();
}
void rtc_getTime(TIME* time){
    time->hour   = rtc_getHour();
    time->minute = rtc_getMin();
    time->second =  rtc_getSec();
}

void rtc_initCalendar(){
  rtc_setDate(__DEFAULT_YEAR__,__DEFAULT_MONTH__,__DEFAULT_DAY__);
  rtc_setTime(__DEFAULT_HOUR__,__DEFAULT_MINUTE__,__DEFAULT_SECOND__);
  rtc_setDOW(__DEFAULT_DOW__);
  rtc_setDOY(__DEFAULT_DOY__);
}

void rtc_setDate(U16 year,U8 month, U8 day){
	rtc_setDom(day);
	rtc_setMonth(month);
	rtc_setYear(year);
}

void rtc_setTime(U8 hour,U8 minute, U8 seconds){
    pRTC->CCR       =  __CCR_CLKEN_DISABLE__|__CCR_CTCRST_ENABLE__;
	rtc_setHour(hour);
	rtc_setMin(minute);
	rtc_setSec(seconds);
    pRTC->CCR       = __CCR_CLKEN_ENABLE__|__CCR_CTCRST_DISABLE__;  
}

void rtc_setDOW(U8 dow){
  pRTC->DOW   = dow & __DOW_MASK__;
}

void rtc_setDOY(U16 doy){
    pRTC->DOY   = doy & __DOY_MASK__;
}

void rtc_setDateTime(DATE_TIME* datetime){
  rtc_setDate(datetime->date.year,datetime->date.month,datetime->date.day);
  rtc_setTime(datetime->time.hour,datetime->time.minute,datetime->time.second);
}
void rtc_getDateTime(DATE_TIME* datetime){
  rtc_getDate(&(datetime->date));
  rtc_getTime(&(datetime->time));
}

