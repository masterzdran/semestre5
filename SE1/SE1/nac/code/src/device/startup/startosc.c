#include  "startosc.h"
void StartOsc(void) {
  
    pPLL->CONFIGURATION =__PLL_P_VALUE__ | __PLL_M_VALUE__;
    PLL_FEED();
    
    pPLL->CONTROL = __PLLE_ENABLE__;
    PLL_FEED();

    while (!(pPLL->STATUS & __PLL_PLOCK__));

    pPLL->CONTROL = (__PLLC_CONNECT__<<1) | __PLLE_ENABLE__;
    
    PLL_FEED();
     
    pMAM->CONTROL_REGISTER = __MAM_FULLY_ENABLE__;
     
    pMAM->TIMING = __MAMTIM_FETCH_4_CLOCK__;
    
    __VPB_CLOCK__   = __VPB_CLOCK_EQUAL_CLOCK__;
}

