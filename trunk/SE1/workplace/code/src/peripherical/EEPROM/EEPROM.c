/*
 * 1024 * 1 byte
 * Write 1 Byte
 * Write 1 Page = 16 Bytes
 * 64 Pages
 * TOTAL:
 * [4 Bytes] TOTAL DISTANCE    //• totalização de distância percorrida pelo veículo, em quilómetros;
 * [4 Bytes] TOTAL USAGE TIME  //• totalização de tempo de utilização, em horas.
 * CURRENT:  
 * [7 Bytes]START             //• data/hora de início do percurso;
 * [4 Bytes]DISTANCE          //• distância percorrida;
 * [4 Bytes]TIME              //• tempo despendido no percurso;
 * [4 Bytes]STOPTIME          //• tempo parado - soma dos períodos de tempo em que o veículo esteve parado.
 * [4 Bytes]MAX SPEED         //• velocidade máxima – a velocidade máxima instantânea atingida pelo veículo;
 * -----------------------------------------------------------------------------
 * 
 * */
#include "EEPROM.h"
#include "I2C.h"

/**
 * Inicialização da EEPROM 
 **/
void EEPROM_init(){
  I2C_init();
}
/**
 * Obtem o endereço 'escravo' a ser utilizado
 * */
U8 getSlaveAddr(U32 address){
  U16 adr = address & __EEPROM_CAT24C08_ADDRESS_MASK__;
  return ((adr <<  __EEPROM_ADDRESS_LSHIFT__) & __EEPROM_ADDRESS_MASK__) ;
}

/**
 * Obtem o endereço bloco a ser utilizado 
 **/
U8 getBlocAddr(U32 address){
  U16 adr = address & __EEPROM_CAT24C08_ADDRESS_MASK__;
  return ((adr >> __EEPROM_BLOCK_SHIFT__) & __EEPROM_BLOCK_MASK__ );
}
/**
 * Função  de envio de bytes e espera pelo ACK do 'escravo'
 * */
void sendFunction(Bool isStart, U8 byte){
  if (isStart){
    I2C_start();
  }
  I2C_write_byte(byte);
  while(I2C_slave_ack == 0);
}
/**
 * Le bloco da EEPROM
 * */
void eeprom_read_block(U32 address, U8 * block, U8 size){
  if (address == 0 || block == 0 || size == 0 ) return;
  U8 blocAddress = getBlocAddr(address) | __EEPROM_READ__;
  U8 slaveAdress   = getSlaveAddr(address) | __EEPROM_READ__;

  sendFunction(true,blocAddress);
  sendFunction(false,slaveAdress);
  sendFunction(true,blocAddress);
  
  for(;size;--size,++block){
    *block = I2C_read_byte();
    if ((size-1))
      I2C_master_ack();
    else
      I2C_master_nack();
  }
  I2C_stop();
}

/**
 * Escreve bloco na EEPROM
 * */
U8 eeprom_write_block(U32 address, U8 * block, U8 size){
  if (address == 0 || block == 0 || size <= 0 || size > __EEPROM_MAX_BYTE_WRITE__) return;
  U8 blocAddress = getBlocAddr(address) | __EEPROM_WRITE__;
  U8 slaveAdress = getSlaveAddr(address) | __EEPROM_WRITE__;

  sendFunction(true,blocAddress);
  sendFunction(false,slaveAdress); 
  
  for (;size;--size,++block){
    sendFunction(false,*block);
  }
  I2C_stop();
}

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
