#ifndef STARTOSC_H
#define STARTOSC_H
#include "TYPES.h"
#include "SCB.h"
    

#define     PLL_FEED()              {pPLL->FEED = __PLL_FEED_AA__; pPLL->FEED = __PLL_FEED_55__;}

typedef struct _system_clock{
  U32 cclk;
  U32 fcco;
  U32 sclk;
  U8  div;
  U8  m;
  U8  p;
  U8  DUMMY;  
}SysClockInfo;


void StartOsc(void);
SysClockInfo getSystemClockInfo();
U32 getSystemClock();
#endif
