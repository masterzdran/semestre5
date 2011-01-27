#include "WATCHDOG.h"



void WATCHDOG_init(U32 value){
  /*
   * Set the watchdog timer constant reload value in WDTC register.
   * Setup mode in WDMOD register.
   * Start the watchdog by writing 0xAA followed by 0x55 to the WDFEED register.
   * Watchdog should be fed again before the watchdog counter underflows to prevent reset/interrupt.
   */
pWatchDog->TIMER_CONSTANT = value;

}
