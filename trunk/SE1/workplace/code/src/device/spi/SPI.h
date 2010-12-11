#ifndef SPI_H
#define SPI_H

#define pSPI      ((pLPC_SPI) 0xE0020000)

typedef struct _SPI{
    U32		CONTROL;
    U32		STATUS;
    U32		DATA;
    U32		CLOCK_COUNTER;
}LPC_SPI,pLPC_SPI;


#endif
