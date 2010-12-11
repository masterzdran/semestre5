#ifndef STARTOSC_H
#define STARTOSC_H
#include "TYPES.h"
#include "LPC2106.h"
#include "SCB.h"
    

#define     PLL_FEED()              {pPLL->FEED = __PLL_FEED_AA__; pPLL->FEED = __PLL_FEED_55__;}


#define     CCLK          (__PLL_M_VALUE__ * __FOSC__)
#define     FCCO          (__FOSC__ * __PLL_M_VALUE__ * __PLL_P_VALUE__ * 2)

void StartOsc(void);

#endif
