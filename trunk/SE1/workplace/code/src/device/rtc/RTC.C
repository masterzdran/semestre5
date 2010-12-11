#include  "startosc.h"
#include "RTC.h"



/*Interrupts: See Section 16–5.1 for RTC interrupt handling. Interrupts are enabled in the VIC using the VICIntEnable register (Section 5–5.4).*/

void rtc_init(){
    /*Power: In the PCONP register (Table 3–27), set bit PCRTC = 1.*/
    pPLL->CONTROL   |= PCRTC;
    pRTC->CCR       =  __CCR_CLKEN_DISABLE__|__CCR_CTCRST_ENABLE__;
    pRTC->PREINT    = LPC_PREINT;
    pRTC->PREFRAC   = LPC_PREFRAC;
    pRTC->ILR       = __ILR_RTCALF_CLEAR__|__ILR_RTCCIF_CLEAR__;
    pRTC->ILR       = __ILR_RTCALF_DISABLE__|__ILR_RTCCIF_DISABLE__;
    pRTC->CIIR      = ~(__CIIR_IMDOM__|__CIIR_IMDOW__|__CIIR_IMDOY__|__CIIR_IMHOUR__|__CIIR_IMMIN__|__CIIR_IMMON__|__CIIR_IMSEC__|__CIIR_IMYEAR__);
    pRTC->AMR       = __AMRDOM__|__AMRDOW__|__AMRDOY__|__AMRHOUR__|__AMRMIN__|__AMRMON__|__AMRSEC__|__AMRYEAR__;
    rtc_initCalendar();
    pRTC->CCR       = __CCR_CLKEN_ENABLE__|__CCR_CTCRST_DISABLE__;
}

void rtc_initCalendar(){
  rtc_setDate(2010,01,01);
  rtc_setTime(00,00,00);
  rtc_setDOW(5);
  rtc_setDOY(1);
}

void rtc_setDate(U16 year,U8 month, U8 day){
    pRTC->YEAR      = year  & 0xFFF;
    pRTC->MONTH     = month & 0xF;
    pRTC->DOM       = day   & 0x1F;
}
void rtc_setTime(U8 hour,U8 minute, U8 seconds){
      pRTC->CCR       =  __CCR_CLKEN_DISABLE__|__CCR_CTCRST_ENABLE__;
      pRTC->HOUR      = hour    & 0x1F;
      pRTC->MIN       = minute  & 0x3F;
      pRTC->SEC       = seconds & 0x3F;
      pRTC->CCR       = __CCR_CLKEN_ENABLE__|__CCR_CTCRST_DISABLE__;  
}

void rtc_setDOW(U8 dow){
  pRTC->DOW   = dow & 0x7;
}

void rtc_setDOY(U16 doy){
    pRTC->DOY   = doy & 0x1FF;
}
