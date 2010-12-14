#ifndef STARTOSC_H
#define STARTOSC_H
#include "TYPES.h"
#include "LPC2106.h"
#include "SCB.h"
    

#define     PLL_FEED()              {pPLL->FEED = __PLL_FEED_AA__; pPLL->FEED = __PLL_FEED_55__;}




void StartOsc(void);

#endif
