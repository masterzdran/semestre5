#include "I2C.h"



void I2C_init(){
    //Power: In the PCONP register (table 3-27) set bit PCI2C
    //    Remark: On reset, I2C is enable (PCI2C = 1)
    //Pins: Select I2C pins in registers PINSEL0 (Section 7-2)
    //    Remark: The I2C pins SDA and SCL are open-drain pins
    //Interrupts: interrupts are enabled in the VIC using VICIntEnable
    //register (Table 5-43)
    //Initialization:
    //  -> I2ADR is loaded with the part's own slave address and the general call bit (GC)
    //  -> The I2C interrupt enable and interrupt priority bits are set
    //  -> The slave mode is enabled by simultaneously setting the I2EN and AA bits in I2CON
    //and the serial clock frequency(for master modes) is defined by loading CR0 and Cr1
    //in I2CON. The master routines must be started in the main program
    
    //1- Load I2ADR with own slave address, enable general call recognition if needed
    //2- Enable I2C interrupt
    //3- Write 0x44 to I2CONSET to set the I2EN and AA bits, enabling salve functions.
    //For master only functions, write 0x40 to I2CONSET
    pPower->POWER_CONTROL |= __PCI2C_ENABLE__;
    
}
