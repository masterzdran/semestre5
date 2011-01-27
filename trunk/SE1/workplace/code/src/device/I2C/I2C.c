#include "I2C.h"
#include "GPIO.h"
#include "TIMER.h"
#include "SCB.h"
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
    pPOWER->POWER_CONTROL |= __PCI2C_ENABLE__;
    
    gpio_init(__PINSEL0_I2C_SCL__|__PINSEL0_I2C_SDA__,0);
    
    gpio_write(__I2C_SCL_PIN__|__I2C_SDA_PIN__,__I2C_SCL_PIN__|__I2C_SDA_PIN__);
    
    gpio_set_direction(__I2C_SCL_PIN__|__I2C_SDA_PIN__,GPIO_OUT);
    
    
}

static void write_bit(U8 d) {
	/* Colocar em SDA o valor a escrever */
  
  if (d & 1)
    gpio_set(__I2C_SDA_PIN__);
  else
    gpio_clear(__I2C_SDA_PIN__);

	/* Clock Pulse Width Low */ /* Data In Setup Time - 100 ns */
	timer_sleep_microseconds(pTIMER0,micro_wait);
		
	/* Gerar um impulso em SCL */ 
  gpio_set(__I2C_SCL_PIN__);
    
	timer_sleep_microseconds(pTIMER0,micro_wait);	/* Clock Pulse Width High */
  gpio_clear(__I2C_SCL_PIN__);
	/* Data In Hold Time - 0 ns */
}

static U8 read_bit() {
	/* Colocar em alta-impedancia para aceitar os dados impostos pelo dispositivo */
  gpio_set(__I2C_SDA_PIN__);
	
	/* Clock Pulse Width Low */
	timer_sleep_microseconds(pTIMER0,micro_wait);

	/* Gerar um impulso em SCL */ 
	gpio_set(__I2C_SCL_PIN__);
	
	timer_sleep_microseconds(pTIMER0,micro_wait);	/* Clock Pulse Width High */
	U32 tmp = gpio_read(__I2C_SDA_PIN__);
  gpio_clear(__I2C_SCL_PIN__);
	
	return (tmp & __I2C_SDA_PIN__)?1:0;
}


void I2C_start(){  
  gpio_write(__I2C_SCL_PIN__|__I2C_SDA_PIN__,__I2C_SCL_PIN__|__I2C_SDA_PIN__);
	timer_sleep_microseconds(pTIMER0,micro_wait);						/* Start Setup Time */
  /* Primeiro a data ... */
	gpio_clear(__I2C_SDA_PIN__);
	timer_sleep_microseconds(pTIMER0,micro_wait);						/* Start Hold Time */
	/* ... e depois o clock */
	gpio_clear(__I2C_SCL_PIN__);
}

void I2C_stop(){
	/* Colocar ambos a 0 */
	gpio_clear(__I2C_SCL_PIN__|__I2C_SDA_PIN__);
	timer_sleep_microseconds(pTIMER0,micro_wait);
	/* Primeiro o clock ... */
	gpio_set(__I2C_SCL_PIN__);
	timer_sleep_microseconds(pTIMER0,micro_wait);					/* Stop Hold Time */
	/* ... e depois a data	*/
	gpio_set(__I2C_SDA_PIN__);
}
void I2C_write_byte(U8 value){
	U8 i;
	for (i = 0; i < 8; ++i)
		write_bit(value >> (7 - i));  
}
U8 I2C_read_byte(){
	U8 tmp = 0;
	U8 i;
	for (i = 0; i < 8; ++i) {
		tmp = (tmp << 1) + read_bit();
	}
	return tmp;  
}

U32 I2C_slave_ack(){return read_bit();}
void I2C_master_ack(){ write_bit(0); }
void I2C_master_nack(){ write_bit(1); }


