#include "LPC2106.h"

void lpc2106_init(){
	
	
}

void io_write_u32(U32* address, U32 value){
	*address = value;
}

U32 io_read_u32(U32* address){
	return (*address);
}

void timer_init(){
	io_write_u32(T0_IR + Tx_PR, PCLK / 1000);
	io_write_u32(T0_IR + Tx_TCR, TxTCR_RESET);
	io_write_u32(T0_IR + Tx_TCR, TxTCR_ENABLE);	
}

U32 timer_read(){
	return io_read_u32(T0_IR + Tx_TC);		
}

