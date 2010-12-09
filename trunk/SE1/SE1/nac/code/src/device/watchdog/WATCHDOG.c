#include "WATCHDOG.h"

#define pWatchDog     ((pLPC_WATCHDOG)  0xE0000000)

typedef struct _WATCHDOG{
    U8		MODE_REGISTER;
    U8    DUMMY01;
    U16   DUMMY02;
    U32		TIMER_CONSTANT;
    U8		FEED_SEQUENCE;
    U8    DUMMY03;
    U16   DUMMY04;
    U32		TIMER_VALUE;
}LPC_WATCHDOG, *pLPC_WATCHDOG;


void WATCHDOG_init(U32 value){
  /*
   * Set the watchdog timer constant reload value in WDTC register.
   * Setup mode in WDMOD register.
   * Start the watchdog by writing 0xAA followed by 0x55 to the WDFEED register.
   * Watchdog should be fed again before the watchdog counter underflows to prevent reset/interrupt.
   */
pWatchDog->TIMER_CONSTANT = value;

}
