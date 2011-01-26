#include "VIC.h"

void VIC_init(){
  
    U32 i ;
    PU32 vicAddr;
    PU32 vicCtrl;
    pVIC->IntEnClr = 0xFFFFFFFF; //clear all interrupts
    for ( i = 0; i < __MAX_INTERRUPT__; i++ )
    {
      vicAddr = (PU32)(pVIC_VECTADDRX + i*4);
      vicCtrl = (PU32)(pVIC_VECTCNTX +  i*4);
      vicAddr = 0x0;	
      vicCtrl = 0xF;
    }
}

void disableIRQ(U8 peripherical){
  pVIC->IntSelect &= ~ (1 << peripherical);
}
void enableIRQ(U8 peripherical){
  pVIC->IntSelect |= (1 << peripherical);
}

BOOL VIC_ConfigIRQ(void(*fx)(),U8 peripherical, U8 priority){
  if (priority < 0 || priority > __MAX_INTERRUPT__) return FALSE;
  if (peripherical < 0 || peripherical > __MAX_INTERRUPT__) return FALSE;
  
  disableIRQ(peripherical);
  PU32 vicAddr = (PU32)(pVIC_VECTADDRX +  peripherical*4) ;
  PU32 vicCtrl = (PU32)(pVIC_VECTCNTX + peripherical*4);
  vicCtrl = __VIC_ENABLE__ | (1 << peripherical);
  vicAddr = (PU32) fx();
  enableIRQ(peripherical);  
 return TRUE;
}
