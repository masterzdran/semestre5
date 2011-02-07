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
#include "I2C.h"
#include "GPIO.h"
#include "TIMER.h"
#include "SCB.h"

#define I2C_FREQ_DIV 800
/**
 * Iniciação do periferico I2C
 * */
void I2C_init(){
  //I2C Power On
  pPOWER->POWER_CONTROL |= __PCI2C_ENABLE__;
  //I2C Pin Select
  gpio_init_PINSEL0(__PINSEL0_I2C_SCL__|__PINSEL0_I2C_SDA__);
  //Clear Bits
  pI2C->CONTROL_CLEAR_REGISTER = __I2CONCLR_MASK__;

  /*
  Bit Frequency = fCLK / (I2SCLH + I2SCLL)
  Where fCLK is the frequency of pclk. 
  The values for I2SCLL and I2SCLH don’t have to be the same. Software can set different duty cycles on SCL by setting these
  two registers. But the value of the register must ensure that the data rate is in the I2C data rate range of 0 through 400KHz. So
  the value of I2SCLL and I2SCLH has some restrictions. Each register value should be greater than or equal to 4.
   * */
  pI2C->DUTY_CYCLE_HIGH_HALF_WORD_REGISTER = (I2C_FREQ_DIV * 2/3);
	pI2C->DUTY_CYCLE_LOW_HALF_WORD_REGISTER  = (I2C_FREQ_DIV * 1/3); // 66% duty cycle
  //enable
  pI2C->CONTROL_SET_REGISTER =  __I2EN_ENABLE__;
}

/**
 * Função que envia um bit para o periférico 'escravo' 
 **/
static void write_bit(U8 d) {
	/* Colocar em SDA o valor a escrever */
  
  if (d & 1)
    gpio_set(__I2C_SDA_PIN__);
  else
    gpio_clear(__I2C_SDA_PIN__);

	/* Clock Pulse Width Low */ /* Data In Setup Time - 100 ns */
	timer_sleep_microseconds(pTIMER1,micro_wait);
		
	/* Gerar um impulso em SCL */ 
  gpio_set(__I2C_SCL_PIN__);
    
	timer_sleep_microseconds(pTIMER1,micro_wait);	/* Clock Pulse Width High */
  gpio_clear(__I2C_SCL_PIN__);
	/* Data In Hold Time - 0 ns */
}

/**
 * Função que lê um bit do periférico 'escravo' 
 **/
static U8 read_bit() {
	/* Colocar em alta-impedancia para aceitar os dados impostos pelo dispositivo */
  gpio_set(__I2C_SDA_PIN__);
	
	/* Clock Pulse Width Low */
	timer_sleep_microseconds(pTIMER1,micro_wait);

	/* Gerar um impulso em SCL */ 
	gpio_set(__I2C_SCL_PIN__);
	
	timer_sleep_microseconds(pTIMER1,micro_wait);	/* Clock Pulse Width High */
	U32 tmp = gpio_read(__I2C_SDA_PIN__);
  gpio_clear(__I2C_SCL_PIN__);
	
	return (tmp & __I2C_SDA_PIN__)?1:0;
}


/**
 * Função com a sequencia de START da Comunicação 
 **/
void I2C_start(){
  gpio_set_direction(__I2C_SCL_PIN__|__I2C_SDA_PIN__,GPIO_OUT);
  gpio_write(__I2C_SCL_PIN__|__I2C_SDA_PIN__,__I2C_SCL_PIN__|__I2C_SDA_PIN__);
	timer_sleep_microseconds(pTIMER1,micro_wait);						/* Start Setup Time */
  /* Primeiro a data ... */
	gpio_clear(__I2C_SDA_PIN__);
	timer_sleep_microseconds(pTIMER1,micro_wait);						/* Start Hold Time */
	/* ... e depois o clock */
	gpio_clear(__I2C_SCL_PIN__);
}
/**
 * Função com a sequencia de STOP da Comunicação 
 **/
void I2C_stop(){
	/* Colocar ambos a 0 */
	gpio_clear(__I2C_SCL_PIN__|__I2C_SDA_PIN__);
	timer_sleep_microseconds(pTIMER1,micro_wait);
	/* Primeiro o clock ... */
	gpio_set(__I2C_SCL_PIN__);
	timer_sleep_microseconds(pTIMER1,micro_wait);					/* Stop Hold Time */
	/* ... e depois a data	*/
	gpio_set(__I2C_SDA_PIN__);
}
/**
 * Envia um byte 
 **/
void I2C_write_byte(U8 value){
  gpio_set_direction(__I2C_SCL_PIN__|__I2C_SDA_PIN__,GPIO_OUT);
	U8 i;
	for (i = 0; i < 8; ++i)
		write_bit(value >> (7 - i));  
}
/**
 * Lê um byte 
 **/
U8 I2C_read_byte(){
  gpio_set_direction(__I2C_SCL_PIN__|__I2C_SDA_PIN__,GPIO_IN);
	U8 tmp = 0;
	U8 i;
	for (i = 0; i < 8; ++i) {
		tmp = (tmp << 1) + read_bit();
	}
	return tmp;  
}

/**
 * Função que lê o sinal de acknowladge enviado pelo periferico 'escravo'
 **/
U32 I2C_slave_ack(){return read_bit();}
/**
 * Função que envia o sinal de acknowladge para o periferico 'escravo'
 **/
void I2C_master_ack(){ write_bit(0); }
/**
 * Função que envia o sinal de not acknowladge para o periferico 'escravo'
 **/
void I2C_master_nack(){ write_bit(1); }


