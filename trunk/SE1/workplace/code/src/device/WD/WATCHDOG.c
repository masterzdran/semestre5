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
Bool WD_isRunning(){return pWatchDog->MODE_REGISTER & __WDEN_MASK__;}
void WD_Enable(){ pWatchDog->MODE_REGISTER |= __WDEN_MASK__;}
void WD_Disable(){ pWatchDog->MODE_REGISTER &= ~(__WDEN_MASK__);}
void WD_ResetEnable(){ pWatchDog->MODE_REGISTER |= _WDRESET_ENABLE__;}
void WD_ResetDisable(){ pWatchDog->MODE_REGISTER &= ~(_WDRESET_ENABLE__)}
