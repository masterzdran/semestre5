#ifndef STARTOSC_H
#define STARTOSC_H
#include "LPC2106.h"
#include "SCB.h"


#define    pPLL   ((pLPC_PLL) 0xE01FC080)     
#define    pMAM   ((pLPC_MAM) 0xE01FC000)     
   

#define     PLL_FEED()              {pPLL->FEED = __PLL_FEED_AA__; pPLL->FEED = __PLL_FEED_55__;}


#define CCLK          (__PLL_M_VALUE__ * __FOSC__)
#define FCCO          (__FOSC__ * __PLL_M_VALUE__ * __PLL_P_VALUE__ * 2)
void StartOsc(void);

#endif
