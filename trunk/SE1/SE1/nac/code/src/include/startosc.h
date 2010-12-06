#ifndef STARTOSC_H
#define STARTOSC_H
#include "LPC2106.h"

#define    pPLL   ((pLPC_PLL) 0xE01FC080)     
#define    pMAM   ((pLPC_MAM) 0xE01FC000)     

typedef struct _PLL{
    U32    CONTROL;
    U32    CONFIGURATION;
    U32    STATUS;
    U32    FEED;
}LPC_PLL,*pLPC_PLL;

typedef struct _MAM{
    U32 CONTROL_REGISTER;
    U32 TIMING;
}LPC_MAM,*pLPC_MAM;

    


#define     __PLL_M_VALUE__         ((const unsigned char ) 0x03 )
#define     __PLL_P_VALUE__         ((const unsigned char ) 0x20 )
#define     __PLL_FEED_AA__         ((const unsigned char ) 0xAA )
#define     __PLL_FEED_55__         ((const unsigned char ) 0x55 )

#define     __PLLE_DISABLE__        ((const unsigned char ) 0x0 )
#define     __PLLE_ENABLE__         ((const unsigned char ) 0x1 )
#define     __PLLC_DISCONNECT__     ((const unsigned char ) 0x0 )
#define     __PLLC_CONNECT__        ((const unsigned char ) 0x1 )
#define     __PLOCK_LOCK__          ((const unsigned char ) 0x1 )
#define     __PLOCK_NOTLOCK__       ((const unsigned char ) 0x0 )

#define     __MAM_FULLY_ENABLE__    ((const unsigned char ) 0x2 )
#define     __MAM_PARTIAL_ENABLE__  ((const unsigned char ) 0x1 )
#define     __MAM_DISABLE__         ((const unsigned char ) 0x0 )

#define     __MAMTIM_FETCH_4_CLOCK__    ((const unsigned char ) 0x4 )

#define     __PLL_PLOCK__           ((const unsigned short ) 0x400 )

#define     __VPB_CLOCK_1_FOURTH_CLOCK__    ((const unsigned short) 0x0 )
#define     __VPB_CLOCK_EQUAL_CLOCK__       ((const unsigned short) 0x1 )
#define     __VPB_CLOCK_HALF_CLOCK__        ((const unsigned short) 0x2 )



#define     PLL_FEED()              {pPLL->FEED = __PLL_FEED_AA__; pPLL->FEED = __PLL_FEED_55__;}


#define CCLK          (__PLL_M_VALUE__ * __FOSC__)
#define FCCO          (__FOSC__ * __PLL_M_VALUE__ * __PLL_P_VALUE__ * 2)
void StartOsc(void);

#endif
