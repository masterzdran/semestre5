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
 
 
U8 eeprom_read_8(U32 address){

}
U16 eeprom_read_16(U32 address);
U32 eeprom_read_32(U32 address);
void eeprom_read_block(U32 address, U8 * block, size_t size);
void eeprom_write_8(U32 address, U8 value);
void eeprom_write_16(U32 address, U16 value);
void eeprom_write_32(U32 address, U32 value);
size_t eeprom_write_block(U32 address, U8 * block, size_t size);
U8 eeprom_checksum(U32 address, size_t size);
