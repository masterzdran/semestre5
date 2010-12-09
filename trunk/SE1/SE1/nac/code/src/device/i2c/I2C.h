#ifndef I2C_H
#define I2C_h
#include "POWER.h"


#define     pI2C      (((pLPC_I2C) 0xE001C000))

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

#define __I2CONSET_MASK__       0xFC    //bits 0,1 and 7 are reserved
#define __I2EN_ENABLE__         0x80
#define __I2C_STA_ENABLE__      0x10
#define __I2C_STO_ENABLE__      0x20
#define __I2C_SI_ENABLE__       0x08
#define __I2C_AA_ENABLE__       0x04

#define __I2CONCLR_MASK__       0x6C     //bits 0,1,4 and 7 are reserved
#define __I2C_AAC_CLEAR__       0x04
#define __I2C_SIC_CLEAR__       0x08
#define __I2C_STAC_CLEAR__      0x10
#define __I2C_I2ENC_CLEAR__     0x20

#define __I2C_STATUS_MASK__     0xF8
#define __I2DAT_MASK__          0xFF

#define __I2ADR_MASK__          0xFF
#define __I2ADR_CALL__          0x01
#define __I2ADR_CALL_ADR_MASK__ 0xFE   






#endif
