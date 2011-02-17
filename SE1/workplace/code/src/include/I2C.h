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
#ifndef I2C_H
#define I2C_H

#include "TYPES.h"
/**
 * Definição do endereço do periférico I2C 
 **/
#define     pI2C      (((pLPC_I2C) 0xE001C000))

/**
 * Definição da estrutura I2C
 * */
typedef struct _I2C{
  U8 CONTROL_SET_REGISTER;
  U8  DUMMY01;
  U16 DUMMY02;
  
  U8 STATUS_REGISTER;
  U8  DUMMY03;
  U16 DUMMY04;
  
  U8 DATA_REGISTER;
  U8  DUMMY05;
  U16 DUMMY06;
  
  U8 SLAVE_ADDRESS_REGISTER;
  U8  DUMMY07;
  U16 DUMMY08;
  
  U16 DUTY_CYCLE_HIGH_HALF_WORD_REGISTER;
  U16 DUMMY09;  

  U16 DUTY_CYCLE_LOW_HALF_WORD_REGISTER;
  U16 DUMMY10;  

  U8 CONTROL_CLEAR_REGISTER;
  U8  DUMMY11;
  U16 DUMMY12;
}LPC_I2C,*pLPC_I2C;



/**
 * Mascaras referentes ao I2C 
 **/
#define __I2CONSET_MASK__       0xFC    //bits 0,1 and 7 are reserved
#define __I2EN_ENABLE__         0x40
#define __I2C_STA_ENABLE__      0x20
#define __I2C_STO_ENABLE__      0x10
#define __I2C_SI_ENABLE__       0x08
#define __I2C_AA_ENABLE__       0x04

#define __I2CONCLR_MASK__       0x6C     //bits 0,1,4 and 7 are reserved
#define __I2C_AAC_CLEAR__       0x04
#define __I2C_SIC_CLEAR__       0x08
#define __I2C_STAC_CLEAR__      0x20
#define __I2C_I2ENC_CLEAR__     0x40

#define __I2C_STATUS_MASK__     0xF8
#define __I2DAT_MASK__          0xFF

#define __I2ADR_MASK__          0xFF
#define __I2ADR_CALL__          0x01
#define __I2ADR_CALL_ADR_MASK__ 0xFE   

/**
 * Definição dos portos I2C 
 **/
#define __I2C_SCL_PIN__         ((U8)   1 << 0x2)
#define __I2C_SDA_PIN__         ((U8)   1 << 0x3)


/**
 * Definição do modo de Leitura/Escrita do I2C
 **/
#define __I2C_READ__            ((U8) 0x0)
#define __I2C_WRITE__           ((U8) 0x1)
#define     micro_wait    5

/**
 * Assinatura das funções publicas
 **/
void I2C_init();
void I2C_start();
void I2C_stop();
void I2C_write_byte(U8 value);
U32 I2C_slave_ack();
U8 I2C_read_byte();
void I2C_master_ack();
void I2C_master_nack();

#endif
