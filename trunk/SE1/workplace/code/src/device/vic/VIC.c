#include "VIC.h"


void VIC_init(){
    pVIC->IntSelect &= ~__INTERRUPT_TIMER0_MASK__;
    pVIC_VECTCNTX->VectCntl0 = __VIC_ENABLE__|__INTERRUPT_TIMER0_VALUE__;
    pVIC_VECTADDR->VectAddr = (unsigned long) timer0ISRH;
    pVIC->IntSelect = __INTERRUPT_TIMER0_MASK__;
}
void timer0ISRH(){
}
