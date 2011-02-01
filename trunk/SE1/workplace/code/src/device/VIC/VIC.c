#include "VIC.h"
/**
 * Inicialização do VIC
 * */
void VIC_init(){
  
    U32 i ;
    PU32 vicAddr;
    PU32 vicCtrl;
    pVIC->IntEnClr = 0xFFFFFFFF; //clear all interrupts
    for ( i = 0; i < __MAX_INTERRUPT__; i++ )
    {
      vicAddr = (PU32)(pVIC_VECTADDRX + i*4);
      vicCtrl = (PU32)(pVIC_VECTCNTX +  i*4);
      *vicAddr = 0x0;	
      *vicCtrl = 0xF;
    }
}
/**
 * Função que desactiva da interrupção provocada pela fonte 'peripherical'
 * */
void disableIRQ(U8 peripherical){
  pVIC->IntSelect &= ~ (1 << peripherical);
}

/**
 * Função que activa da interrupção provocada pela fonte 'peripherical'
 **/
void enableIRQ(U8 peripherical){
  pVIC->IntSelect |= (1 << peripherical);
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
  PU32 vicAddr = (PU32)(pVIC_VECTADDRX +  peripherical*4) ;
  PU32 vicCtrl = (PU32)(pVIC_VECTCNTX + peripherical*4);
  *vicCtrl = __VIC_ENABLE__ | (1 << peripherical);
  *vicAddr = (U32)fx;
  enableIRQ(peripherical);  
 return true;
}
