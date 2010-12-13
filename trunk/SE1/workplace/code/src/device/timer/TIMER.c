#include "SCB.h"
#include "TIMER.h"

/*
 * Possible Clock available:
 * 14745600 
 * 29491200
 * 44236800
 * 58982400     <--- Clock choosed (PCLCK = CCLKC)
* */
void timer_init(pLPC_TIMER timer, U32 countNbr){
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
  timer->CTCR   = __CTCR_MODE_0__;
  timer->PR     = countNbr;
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__; 
}

void timer_delay(pLPC_TIMER timer, U32 elapse){
    U32 time;
    timer->PC = 0;
    time = timer_elapsed(timer,0);
    while(timer_elapsed(timer,time)<= elapse);  
}

