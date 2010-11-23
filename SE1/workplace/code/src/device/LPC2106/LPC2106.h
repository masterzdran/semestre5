#ifndef LPC2106_H
#define LPC2106_H

//TIMER ADDRESS
#define T0_IR	((volatile unsigned int *) 0xE0004000)	//Timer 0 Interrupt Register
#define T1_IR	((volatile unsigned int *) 0xE0008000)	//Timer 1 Interrupt Register
#define Tx_TCR	0x4										//Timer Control Register
#define Tx_TC	0x8										//Timer Counter
#define Tx_PR	0xC										//Timer Prescale Register
#define Tx_PC	0x10									//Timer Prescale Counter

//CLOCK INIT
#define FOSC 	14745600
#define PLL_M 	4
#define PLL_P 	2
#define CCLK 	(FOSC * PLL_M)
#define PCLK 	(CCLK)

//TIMER CONSTANTS
#define TxTCR_RESET		0x2
#define TxTCR_ENABLE	0x1

//GPIO ADDRESS
#define	PINSEL0	((volatile unsigned int *) 0xE002C000)
#define	PINSEL1 ((volatile unsigned int *) 0xE002C004)
#define	IOPIN	((volatile unsigned int *) 0xE0028000)
#define	IOSET	((volatile unsigned int *) 0xE0028004)
#define	IODIR	((volatile unsigned int *) 0xE0028008)
#define	IOCLR	((volatile unsigned int *) 0xE002800C)


//TYPE DEFINITION
typedef volatile unsigned int U32;
typedef unsigned short int U16;
typedef unsigned char U8;


//FUNCTION DECLARATION
void lpc2106_init();	
void timer_init();
U32 timer_read();

void io_write_u32(U32* address, U32 value);
U32 io_read_u32(U32* value);

#endif
