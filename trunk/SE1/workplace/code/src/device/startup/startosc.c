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

