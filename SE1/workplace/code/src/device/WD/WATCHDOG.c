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
#include "WATCHDOG.h"
#include "VIC.h"

void WATCHDOG_init(U32 value){
  /*
   * Set the watchdog timer constant reload value in WDTC register.
   * Setup mode in WDMOD register.
   * Start the watchdog by writing 0xAA followed by 0x55 to the WDFEED register.
   * Watchdog should be fed again before the watchdog counter underflows to prevent reset/interrupt.
   */
  if (WD_COME_FROM_RESET()) {
      //WatchDog Reset
      WD_RESET_DISABLE();
  }else{
      //WatchDog Start
  }
  WD_DISABLE();
  pWatchDog->TIMER_CONSTANT = value;	//set the time-out interval
  pWatchDog->TIMER_VALUE	= 0xFF;		//reset the counter timer value
  pWatchDog->MODE_REGISTER	= __WDTOF_MASK__|__WDINT_MASK__; //clear Int flag and TOF
  WD_RESET_ENABLE();					//make the WDTOF to set WDINT  
  //WD_RESET_DISABLE();					//make the WDTOF to reset the micro
  WD_ENABLE();							//enable WD
  WD_FEED();							//
}
/*
 * When reseting the WatchDog Interrupts must be disabled.
 * If an interrupt occurs during feed sequence an abort condition will occur
 */
void WD_reset(){
	U32 int_enabled = pVIC->IntEnable;
	pVIC->IntEnClr = int_enabled;
	WD_FEED();
	pVIC->IntEnable = int_enabled;
}
/*
 * Substituido por macros
Bool WD_isRunning(){return pWatchDog->MODE_REGISTER & __WDEN_MASK__;}
void WD_Enable(){ pWatchDog->MODE_REGISTER |= __WDEN_MASK__;}
void WD_Disable(){ pWatchDog->MODE_REGISTER &= ~(__WDEN_MASK__);}
void WD_ResetEnable(){ pWatchDog->MODE_REGISTER |= _WDRESET_ENABLE__;}
void WD_ResetDisable(){ pWatchDog->MODE_REGISTER &= ~(_WDRESET_ENABLE__)}
*/
