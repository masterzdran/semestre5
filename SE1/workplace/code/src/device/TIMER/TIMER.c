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

#define _Timer0_Capture_MAX 3

#define _Timer1_Capture_MAX 2
#define _Timer0_Match_MAX 2

#define _Timer1_Match_MAX 2

//PR (Prescale Register) contains the number of MCU clocks (PCLK) required to increment the Timer Counter (TC) value.
void TIMER_init(pLPC_TIMER timer, U32 countNbr){
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
  //timer->CTCR   |= __CTCR_MODE_0__;
  timer->PR     = countNbr;                           
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__; 
}

//PC (Prescale Counter) contains the current prescale counter value. 
//When this value equals the Prescale Register (PR), the Timer (TC) value is incremented.
void TIMER_delay(pLPC_TIMER timer, U32 elapse){
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

void TIMER_capture_init(pLPC_TIMER timer,U8 channel, U32 captureMask, U32 countNbr,tCtcrFunction ctcrFunction){
  U32 _Timer0_Capture_Mask[3]={__PINSEL0_TIMER_0_CAPTURE_0_0__,__PINSEL0_TIMER_0_CAPTURE_0_1__,__PINSEL0_TIMER_0_CAPTURE_0_2__};
  U32 _Timer1_Capture_Mask[2]={__PINSEL0_TIMER_1_CAPTURE_1_0__,__PINSEL0_TIMER_1_CAPTURE_1_1__};

  //Enable GPIO for Timer Capture or Else
  if (timer  == pTIMER0 ){
    if (channel >= _Timer0_Capture_MAX)
      return;
    gpio_init_PINSEL0(_Timer0_Capture_Mask[channel]);
  }else if (timer == pTIMER1){
    if (channel >= _Timer1_Capture_MAX)
      return;
    gpio_init_PINSEL1(_Timer1_Capture_Mask[channel]);
  }else {
    return;
  }
  
  timer->TCR                    = __TCR_DISABLE__|__TCR_RESET_ENABLE__; 
  timer->CCR                    |= (captureMask)<<(3*channel);                         
  if(captureMask & __CAPTURE_INTERRUPT__)
	  timer->IR		= (1<<(channel+4));  
  timer->TCR                    = __TCR_ENABLE__|__TCR_RESET_DISABLE__; 
}
/**
 * LPC_TIMER timer: Timer
 * TMatch timerMatch: Pin enable
 * U32 MatchMask: Counting Method
 * U32 countNbr: Number of counting 
 * 
 * TODO: Working, need to be Generic...
 * 
 * */
void TIMER_ext_match_init(pLPC_TIMER timer,U8 channel, U32 MatchMask, U32 countNbr,tEmrFunction emrFunction){
  U32 _Timer1_Match_Mask[2]={__PINSEL0_TIMER_1_MATCH_1_0__,__PINSEL0_TIMER_1_MATCH_1_1__};
  U32 _Timer0_Match_Mask[2]={__PINSEL0_TIMER_0_MATCH_0_0__,__PINSEL0_TIMER_0_MATCH_0_1__};
  if (timer  == pTIMER0 ){
    if (channel >= _Timer0_Match_MAX)
      return;
    gpio_init_PINSEL0(_Timer0_Match_Mask[channel]);
  }else if (timer == pTIMER1){
    if (channel >= _Timer1_Match_MAX)
      return;
    gpio_init_PINSEL1(_Timer1_Match_Mask[channel]);
  }else {
    return;
  }

  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
  *(&(timer->MR0) + channel)    = countNbr;  
  timer->MCR    |= (MatchMask)<<(3*channel);
  timer->EMR    |= (1<<channel) | ((emrFunction << 2*channel)<<4) ;                              
  if(MatchMask & __MATCH_INTERRUPT__)
	  timer->IR		= (1<<channel);
  //After being configured needs to be started
  //timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__;
}

void TIMER_ext_match_changeTime(pLPC_TIMER timer,U8 channel, U8 dif){
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
  *(&(timer->MR0) + channel) += dif;
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__;
}

void TIMER_ext_match_stop(pLPC_TIMER timer){
  timer->TCR    = __TCR_DISABLE__|__TCR_RESET_ENABLE__;
}

void TIMER_ext_match_start(pLPC_TIMER timer){
  timer->TCR    = __TCR_ENABLE__|__TCR_RESET_DISABLE__;
}

/**
 * LPC_TIMER timer: Timer
 * TMatch timerMatch: Pin enable
 * U32 MatchMask: Counting Method
 * U32 countNbr: Number of counting 
 * Not Tested:Deprecated
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

