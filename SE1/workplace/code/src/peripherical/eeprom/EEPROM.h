#ifndef __EEPROM_H__
#define __EEPROM_H__
#include "TYPES.h"

U8 eeprom_read_8(U32 address);
U16 eeprom_read_16(U32 address);
U32 eeprom_read_32(U32 address);
void eeprom_read_block(U32 address, U8 * block, size_t size);
void eeprom_write_8(U32 address, U8 value);
void eeprom_write_16(U32 address, U16 value);
void eeprom_write_32(U32 address, U32 value);
size_t eeprom_write_block(U32 address, U8 * block, size_t size);
U8 eeprom_checksum(U32 address, size_t size);

#endif
