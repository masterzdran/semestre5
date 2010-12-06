#include  "startosc.h"
#include "TIMER.h"

/*
 * Possible Clock available:
 * 14745600 
 * 29491200
 * 44236800
 * 58982400     <--- Clock choosed (PCLCK = CCLKC)
* */



/*
void sleep_seconds(pLPC_TIMER timer,U32 seconds){timer_delay(timer,(CCLK/SECOND)*seconds);}
void sleep_miliseconds(pLPC_TIMER timer, U32 miliseconds){timer_delay(timer,(CCLK/MILI)*miliseconds);}
void sleep_microseconds(pLPC_TIMER timer,U32 microseconds){timer_delay(timer,(CCLK/MICRO)*microseconds);}
*/

void timer_init(pLPC_TIMER timer, U32 countNbr){
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
  timer->CTCR   = __CTCR_MODE_0__;
  timer->PR     = countNbr;
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__; 
}
/*
void timer_start(pLPC_TIMER timer){timer->TCR |= __TCR_ENABLE__;}
void timer_stop(pLPC_TIMER timer){timer->TCR &= ~(__TCR_DISABLE__);}
U32 timer_elapsed(pLPC_TIMER timer,U32 initial){ return timer->TC - initial;}
*/
void timer_delay(pLPC_TIMER timer, U32 elapse){
    int time;
    timer->PC = 0;
    time = timer_elapsed(timer,0);
    while(timer_elapsed(timer,time)< elapse);  
}
void timer_reset(pLPC_TIMER timer) {
    timer->TCR |= __TCR_RESET_ENABLE__;
    timer->TCR &= ~(__TCR_RESET_DISABLE__);
}
