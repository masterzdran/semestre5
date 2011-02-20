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
#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "TYPES.h"

/**
 * |P0.03|P0.02|P0.01|P0.00|
 * | SDA | SCL |UART0|UART0|
 * 
 * 
 * */
/**
 * Macros referentes à EEPROM 
 **/
#define __EEPROM_SLAVE_ADDRESS__                 (U32) 0xA0
#define __EEPROM_CAT24C08_ADDRESS_MASK__         (U32) 0x03FF
#define __EEPROM_READ__                          (U8)  0x1
#define __EEPROM_WRITE__                         (U8)  0x0
#define __EEPROM_BLOCK_SHIFT__                   (U8)  7
#define __EEPROM_BLOCK_MASK__                    (U8)  0x0E
#define __EEPROM_ADDRESS_LSHIFT__                (U8)  0
#define __EEPROM_ADDRESS_MASK__                  (U8)  0xFE
#define __EEPROM_MAX_BYTE_WRITE__                (U8)  0x10

/**
 * Assinatura das funções publicas 
 **/
U8 eeprom_write_block(U32 address, U8 * block, U8 size);
void eeprom_read_block(U32 address, U8 * block, U8 size);
void EEPROM_init();
/*
U8 eeprom_read_8(U32 address);
U16 eeprom_read_16(U32 address);
U32 eeprom_read_32(U32 address);
void eeprom_read_block(U32 address, U8 * block, U8 size);
void eeprom_write_8(U32 address, U8 value);
void eeprom_write_16(U32 address, U16 value);
void eeprom_write_32(U32 address, U32 value);
U8 eeprom_write_block(U32 address, U8 * block, U8 size);
U8 eeprom_checksum(U32 address, U8 size);
*/
#endif

