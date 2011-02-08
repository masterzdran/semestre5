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
#include "VIC.h"
#include "SCB.h"
/**
 * Inicialização do VIC
 * */
void VIC_init(){
  
    U32 i ;
    PU32 vicAddr;
    PU32 vicCtrl;
    pVIC->IntEnClr                = 0xFFFFFFFF; //clear all interrupts
    pVIC->SoftIntClear            = 0xFFFFFFFF;
    pMAM->MEMORY_MAPPING_CONTROL  = __MEMORY_MAP_CONTROL_USERRAM__;
    pVIC->IntSelect               = 0;
    pVIC->IntEnable               = 0xFFFFFFFF; //clear all interrupts
/*
    for ( i = 0; i < __MAX_INTERRUPT__; i++ )
    {
      vicAddr = (PU32)(pVIC_VECTADDRX + i*4);
      vicCtrl = (PU32)(pVIC_VECTCNTX +  i*4);
      *vicAddr = 0x0;	
      *vicCtrl = 0xF;
    }
*/
}
/**
 * Função que desactiva da interrupção provocada pela fonte 'peripherical'
 * */
void disableIRQ(U8 peripherical){
  pVIC->IntEnClr |=  (1 << peripherical);
}

/**
 * Função que activa da interrupção provocada pela fonte 'peripherical'
 **/
void enableIRQ(U8 peripherical){
  pVIC->IntEnable |= (1 << peripherical);
}

/**
 * Configuração de uma interrupção, com os seguintes parametros:
 * U8 peripherical: identificação do periférico (Tabela de valores de Periférico)
 * U8 priority: prioridade a ser atribuida (0-15)
 * void (*fx)(void): função que vai tratar dessa interrupção
 **/
Bool VIC_ConfigIRQ(U8 peripherical, U8 priority,void (*fx)(void)){
  if (priority < 0 || priority > __MAX_INTERRUPT__) return false;
  if (peripherical < 0 || peripherical > __MAX_INTERRUPT__) return false;
  
  disableIRQ(peripherical);

  
  PU32 vicAddr = (PU32)(&(pVIC_VECTADDR->VectAddr0) + (U32)priority);
  PU32 vicCtrl = (PU32)(&(pVIC_VECTCNT->VectCntl0) + (U32)priority*4);
  
  
    //  *(&(pVIC_VECTADDR->VectAddr0) + (U32)priority ) = (PU32)fx;
    //  *(&(pVIC_VECTCNT->VectCntl0) + (U32)priority) = __VIC_ENABLE__|(peripherical&__VIC_VECTCNTL_MASK__);
  *(vicAddr) = (PU32)fx;
  *(vicCtrl) = __VIC_ENABLE__|(peripherical&__VIC_VECTCNTL_MASK__);
  
  enableIRQ(peripherical);  
 return true;
}
