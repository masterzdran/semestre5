#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "TYPES.h"
#include "I2C.h"

#define __EEPROM_SLAVE_ADDRESS__                 (U32) 0x10100000
#define __EEPROM_CAT24C08_ADDRESS_MASK__         (U32)    0x03FF
#define __EEPROM_READ__                          (U8)     0x1
#define __EEPROM_WRITE__                         (U8)     0x0
#define __EEPROM_BLOCK_SHIFT__                   (U8)     6
#define __EEPROM_BLOCK_MASK__                    (U8)     0x0E
#define __EEPROM_ADDRESS_LSHIFT__                (U8)     1
#define __EEPROM_ADDRESS_MASK__                  (U8)     0xFE


U8 eeprom_read_8(U32 address);
U16 eeprom_read_16(U32 address);
U32 eeprom_read_32(U32 address);
void eeprom_read_block(U32 address, U8 * block, U32 size);
void eeprom_write_8(U32 address, U8 value);
void eeprom_write_16(U32 address, U16 value);
void eeprom_write_32(U32 address, U32 value);
U32 eeprom_write_block(U32 address, U8 * block, U32 size);
U8 eeprom_checksum(U32 address, U32 size);

#endif
