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
  pWatchDog->TIMER_CONSTANT = value;
  WD_ENABLE();
  WD_FEED();
}
/*
 * Substituido por macros
Bool WD_isRunning(){return pWatchDog->MODE_REGISTER & __WDEN_MASK__;}
void WD_Enable(){ pWatchDog->MODE_REGISTER |= __WDEN_MASK__;}
void WD_Disable(){ pWatchDog->MODE_REGISTER &= ~(__WDEN_MASK__);}
void WD_ResetEnable(){ pWatchDog->MODE_REGISTER |= _WDRESET_ENABLE__;}
void WD_ResetDisable(){ pWatchDog->MODE_REGISTER &= ~(_WDRESET_ENABLE__)}
*/
