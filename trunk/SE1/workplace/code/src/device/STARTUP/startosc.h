#ifndef STARTOSC_H
#define STARTOSC_H
#include "TYPES.h"
#include "SCB.h"
    

#define     PLL_FEED()              {pPLL->FEED = __PLL_FEED_AA__; pPLL->FEED = __PLL_FEED_55__;}
#define		__SYSTEM_CLOCK__		58982400
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
//Ler duas vezes por causa do bug da NXP.
/*
#define getAPBDIV()			(((pAPBDIV->APBDIV) & 0x3)?((pAPBDIV->APBDIV) & 0x3):4)
#define getSystemClock()	((__FOSC__ * (((pPLL->STATUS) & 0x1F)+1)) / getAPBDIV())
*/ 
#endif
