#ifndef UART_H
#define UART_H

#define pUART0              ((pLPC_UART) 0xE0000000)
#define pUART1              ((pLPC_UART) 0xE0010000)

typedef struct _UART{
  union{
    U8    RBR;               //0xE000 C000
    U8    THR;
    U8    DLL;
    U32   DUMMY01;           //Alinhamento a 32 bits
  };
  union{
    U8    DLM;              //0xE000 C004
    U8    IER;
    U16   DUMMY02;          //Alinhamento a 32 bits
  };
  union{
    U8    IIR;              //0xE000 C008
    U8    FCR;
    U32   DUMMY03;          //Alinhamento a 32 bits
  };
  U8      LCR ;             //0xE000 C00C
  U8      DUMMY05;
  U16     DUMMY06;
  U32     DUMMY07;
  U8      LSR;              //0xE000 C014
  U8      DUMMY08;
  U16     DUMMY09;
  U8      SCR;              //0xE000 C01C
  U8      DUMMY10;
  U16     DUMMY11;
  U16     ACR;              //0xE000 C020
  U16     DUMMY13;
  U32     DUMMY14;
  U32     FDR;              //0xE000 C028
  U32     DUMMY15;
  U8      TER;              //0xE000 C030
  U8      DUMMY16;
  U16     DUMMY17;
}LPC_UART,*pLPC_UART;



#endif
