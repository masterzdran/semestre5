#include  "startosc.h"
#include "RTC.h"
/*Interrupts: 
 * See Section 16–5.1 for RTC interrupt handling. 
 * Interrupts are enabled in the VIC using the VICIntEnable register (Section 5–5.4).
 * */

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

DATE getDate(){
    DATE date;
    date.year   = (pRTC->CTIME1 >> 16) &&   __YEAR_MASK__;
    date.month  = (pRTC->CTIME1 >> 8)  &&   __MONTH_MASK__;
    date.day    =  pRTC->CTIME1        &&   __DAY_MASK__;
    return date;  
}
TIME getTime(){
    TIME time;
    time.hour   = (pRTC->CTIME0 >> 16) &&   __HOUR_MASK__;
    time.minute = (pRTC->CTIME0 >> 8)  &&   __MINUTE_MASK__;
    time.second =  pRTC->CTIME0        &&   __SECOND_MASK__;
    return time;
}

void rtc_initCalendar(){
  rtc_setDate(__DEFAULT_YEAR__,__DEFAULT_MONTH__,__DEFAULT_DAY__);
  rtc_setTime(__DEFAULT_HOUR__,__DEFAULT_MINUTE__,__DEFAULT_SECOND__);
  rtc_setDOW(__DEFAULT_DOW__);
  rtc_setDOY(__DEFAULT_DOY__);
}

void rtc_setDate(U16 year,U8 month, U8 day){
    pRTC->YEAR      = year  & __YEAR_MASK__;
    pRTC->MONTH     = month & __MONTH_MASK__;
    pRTC->DOM       = day   & __DAY_MASK__;
}
void rtc_setTime(U8 hour,U8 minute, U8 seconds){
      pRTC->CCR       =  __CCR_CLKEN_DISABLE__|__CCR_CTCRST_ENABLE__;
      pRTC->HOUR      = hour    & __HOUR_MASK__;
      pRTC->MIN       = minute  & __MINUTE_MASK__;
      pRTC->SEC       = seconds & __SECOND_MASK__;
      pRTC->CCR       = __CCR_CLKEN_ENABLE__|__CCR_CTCRST_DISABLE__;  
}

void rtc_setDOW(U8 dow){
  pRTC->DOW   = dow & __DOW_MASK__;
}

void rtc_setDOY(U16 doy){
    pRTC->DOY   = doy & __DOY_MASK__;
}
