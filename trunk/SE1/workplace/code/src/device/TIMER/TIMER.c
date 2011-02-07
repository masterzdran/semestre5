/**
#=======================================================================
# SE1   - Sistemas Embebidos 1
#-----------------------------------------------------------------------
# Turma:	LI51N
# Semestre:	Inverno 2010/2011
# Data:		Novembro/2010
#-----------------------------------------------------------------------
# Nome: 	Nuno Cancelo
# Numero:	31401
#-----------------------------------------------------------------------
# Nome:		Nuno Sousa
# Numero:	33595
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Informática e Computadores
# DEETC - Dep. de Eng. Electrónica e Telecomunicações e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
**/ 
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
/**
 * LPC_TIMER timer: Timer
 * TCapture timerCapture: Pin enable
 * U32 captureMask: Counting Method
 * U32 countNbr: Number of counting 
 * */
void TIMER_capture_init(pLPC_TIMER timer,TCapture timerCapture, U32 captureMask, U32 countNbr){
  //Enable GPIO for Timer Capture or Else
  if (timer  == pTIMER0 )
    gpio_init_PINSEL0(timerCapture);
  else if (timer == pTIMER1)
    gpio_init_PINSEL1(timerCapture);
  else {
    return;
  }
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;  //disable timer
  timer->CR0    = countNbr;
  timer->CCR    = captureMask;                         //config counting method
  //timer->PR     = countNbr;                              //define count number  
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__;  // enable timer  
}
/**
 * LPC_TIMER timer: Timer
 * TMatch timerMatch: Pin enable
 * U32 MatchMask: Counting Method
 * U32 countNbr: Number of counting 
 * */
void TIMER_match_init(pLPC_TIMER timer,TMatch timerMatch, U32 MatchMask, U32 countNbr){
  //Enable GPIO for Timer Capture or Else
  if (timer  == pTIMER0 )
    gpio_init_PINSEL0(timerMatch);
  else if (timer == pTIMER1)
    gpio_init_PINSEL1(timerMatch);
  else {
    return;
  }
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;  //disable timer
  timer->MCR    = MatchMask;                         	//config counting method
  timer->PR     = countNbr;                              //define count number  
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__;  // enable timer  
}

/**
 * LPC_TIMER timer: Timer
 * TMatch timerMatch: Pin enable
 * U32 MatchMask: Counting Method
 * U32 countNbr: Number of counting 
 * 
 * TODO: Working, need to be Generic...
 * */
void TIMER_ext_match_init(pLPC_TIMER timer,TMatch timerMatch, U32 MatchMask, U32 countNbr){
  //Enable GPIO for Timer Capture or Else
  if (timer  == pTIMER0 )
    gpio_init_PINSEL0(timerMatch);
  else if (timer == pTIMER1)
    gpio_init_PINSEL1(timerMatch);
  else {
    return;
  }
  
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;  //disable timer
  timer->MR1    = countNbr;  
  timer->MCR    = MatchMask;                         	//config counting method
  timer->EMR    |= 0xC0;                           //define count number  
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__;  // enable timer  
}
