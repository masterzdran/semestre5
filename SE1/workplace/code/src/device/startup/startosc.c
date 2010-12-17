#include  "startosc.h"
void StartOsc(void) {
  
    pPLL->CONFIGURATION =__PLL_P_VALUE__ | __PLL_M_VALUE__;
    PLL_FEED();
    
    pPLL->CONTROL = __PLL_CONTROL_ON_DISCONNECTED__;
    PLL_FEED();

    while (!(pPLL->STATUS & __PLLSTAT_PLOCK_MASK__));

    pPLL->CONTROL = __PLL_CONTROL_OFF_CONNECTED__;
    
    PLL_FEED();
     
    pMAM->CONTROL_REGISTER = __MAM_FULLY_ENABLE__;
     
    pMAM->TIMING = __MAMTIM_FETCH_3_CLOCK__; //according to Table 35: Suggestions for MAM timing selection 
    
    pAPBDIV->APBDIV = __APBDIV_CLOCK_EQUAL_CLOCK__;
}
/*
SysClockInfo getSystemClockInfo(){
  SysClockInfo systemClock;
  U8 div  = (pAPBDIV->APBDIV) & 0x3;
  U8 val  = pPLL->CONFIGURATION;
    
  systemClock.cclk  = __FOSC__ * (val & 0x1F);
  systemClock.fcco  = __FOSC__ * (val & 0x1F) * ((val >> 5) & 0x3) * 2;
  systemClock.div   = (div)?div:4;
  systemClock.m     = val & 0x1F;
  systemClock.p     = (val >> 5) & 0x3;
  systemClock.sclk  = (__FOSC__ * (val & 0x1F))/ ((div)?div:4);
  return systemClock;    
}
U32 getSystemClock(){
  U8 div  = (pAPBDIV->APBDIV) & 0x3;
  U8 val  = pPLL->CONFIGURATION;
  return (__FOSC__ * (val & 0x1F))/ ((div)?div:4);
}*/
