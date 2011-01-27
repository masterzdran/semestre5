#include "SCB.h"
#include "TIMER.h"

/*
 * Possible Clock available:
 * 14745600 
 * 29491200
 * 44236800
 * 58982400     <--- Clock choosed (PCLCK = CCLKC)
* */

//PR (Prescale Register) contains the number of MCU clocks (PCLK) required to increment the Timer Counter (TC) value.
void timer_init(pLPC_TIMER timer, U32 countNbr){
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
  timer->CTCR   = __CTCR_MODE_0__;
  timer->PR     = countNbr;                           
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__; 
}
//PC (Prescale Counter) contains the current prescale counter value. 
//When this value equals the Prescale Register (PR), the Timer (TC) value is incremented.
void timer_delay(pLPC_TIMER timer, U32 elapse){
    U32 time;
    timer->PC = 0;                          
    time = timer_elapsed(timer,0);
    while(timer_elapsed(timer,time)<= elapse);
}

