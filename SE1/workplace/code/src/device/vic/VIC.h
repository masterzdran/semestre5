#ifndef VIC_H
#define VIC_H

#define         pVIC              ((pLPC_VIC)           0xFFFFF000)
#define         pVIC_VECTADDR     ((pLPC_VIC_VECTADDR)  0xFFFFF030)
#define         pVIC_VECTADDRX    ((pLPC_VIC_VECTADDRX) 0xFFFFF100)
#define         pVIC_VECTCNTX     ((pLPC_VIC_VECTCNTX)  0xFFFFF200)


typedef struct _VIC_VECTCNTX{
      U8 VectCntl0;        //0xFFFF F200
      U8  DUMMY03;
      U16 DUMMY04;
      U8 VectCntl1;        //0xFFFF F204
      U8  DUMMY05;
      U16 DUMMY06;      
      U8 VectCntl2;        //0xFFFF F208
      U8  DUMMY07;
      U16 DUMMY08;            
      U8 VectCntl3;        //0xFFFF F20C
      U8  DUMMY09;
      U16 DUMMY10;            
      U8 VectCntl4;        //0xFFFF F210
      U8  DUMMY11;
      U16 DUMMY12;            
      U8 VectCntl5;        //0xFFFF F214
      U8  DUMMY13;
      U16 DUMMY14;            
      U8 VectCntl6;        //0xFFFF F218
      U8  DUMMY15;
      U16 DUMMY16;            
      U8 VectCntl7;        //0xFFFF F21C
      U8  DUMMY17;
      U16 DUMMY18;            
      U8 VectCntl8;        //0xFFFF F220
      U8  DUMMY19;
      U16 DUMMY20;            
      U8 VectCntl9;        //0xFFFF F224
      U8  DUMMY21;
      U16 DUMMY22;            
      U8 VectCntl10;       //0xFFFF F228
      U8  DUMMY23;
      U16 DUMMY24;            
      U8 VectCntl11;       //0xFFFF F22C
      U8  DUMMY25;
      U16 DUMMY26;            
      U8 VectCntl12;       //0xFFFF F230
      U8  DUMMY27;
      U16 DUMMY28;
      U8 VectCntl13;       //0xFFFF F234
      U8  DUMMY29;
      U16 DUMMY30;
      U8 VectCntl14;       //0xFFFF F238
      U8  DUMMY31;
      U16 DUMMY32;
      U8 VectCntl15;       //0xFFFF F23C
      U8  DUMMY33;
      U16 DUMMY34;  
}LPC_VIC_VECTCNTX,*pLPC_VIC_VECTCNTX;  

typedef struct _VIC_VECTADDRX{
      U32 VectAddr0;        //0xFFFF F100
      U32 VectAddr1;        //0xFFFF F104
      U32 VectAddr2;        //0xFFFF F108
      U32 VectAddr3;        //0xFFFF F10C
      U32 VectAddr4;        //0xFFFF F110
      U32 VectAddr5;        //0xFFFF F114
      U32 VectAddr6;        //0xFFFF F118
      U32 VectAddr7;        //0xFFFF F11C
      U32 VectAddr8;        //0xFFFF F120
      U32 VectAddr9;        //0xFFFF F124
      U32 VectAddr10;       //0xFFFF F128
      U32 VectAddr11;       //0xFFFF F12C
      U32 VectAddr12;       //0xFFFF F130
      U32 VectAddr13;       //0xFFFF F134
      U32 VectAddr14;       //0xFFFF F138
      U32 VectAddr15;       //0xFFFF F13C  
}LPC_VIC_VECTADDRX,*pLPC_VIC_VECTADDRX;

typedef struct _VIC_VECTADDR{
      U32 VectAddr;         //0xFFFF F030
      U32 DefVectAddr;      //0xFFFF F034  
}LPC_VIC_VECTADDR,*pLPC_VIC_VECTADDR;

typedef struct _VIC{
      U32 IRQStatus;        //0xFFFF F000
      U32 FIQStatus;        //0xFFFF F004
      U32 RawIntr;          //0xFFFF F008
      U32 IntSelect;        //0xFFFF F00C
      U32 IntEnable;        //0xFFFF F010
      U32 IntEnClr;         //0xFFFF F014
      U32 SoftInt;          //0xFFFF F018
      U32 SoftIntClear;     //0xFFFF F01C
      U8 Protection;        //0xFFFF F020
      U8  DUMMY01;
      U16 DUMMY02;  
}LPC_VIC,*pLPC_VIC;

#define __VIC_VECTCNTL_MASK__       (U8) 0x1F
#define __VIC_PROTECTION_MASK__     (U8) 0x01
#define __VIC_ENABLE__              (U8) 0x20


//Interrupts Sources

#define     __INTERRUPT_WDT_MASK__           (U32)   0x00000001
#define     __INTERRUPT_SOFTWARE_MASK__      (U32)   0x00000002
#define     __INTERRUPT_DbgCommRx_MASK__     (U32)   0x00000004
#define     __INTERRUPT_DbgCommTX_MASK__     (U32)   0x00000008
#define     __INTERRUPT_TIMER0_MASK__        (U32)   0x00000010
#define     __INTERRUPT_TIMER1_MASK__        (U32)   0x00000020
#define     __INTERRUPT_UART0_MASK__         (U32)   0x00000040
#define     __INTERRUPT_UART1_MASK__         (U32)   0x00000080
#define     __INTERRUPT_PWM_MASK__           (U32)   0x00000100
#define     __INTERRUPT_I2C_MASK__           (U32)   0x00000200
#define     __INTERRUPT_SPI_SSP_MASK__       (U32)   0x00000400
#define     __INTERRUPT_RESERVED_MASK__      (U32)   0x00000800     
#define     __INTERRUPT_PLL_MASK__           (U32)   0x00001000
#define     __INTERRUPT_RTC_MASK__           (U32)   0x00002000
#define     __INTERRUPT_EINT0_MASK__         (U32)   0x00004000
#define     __INTERRUPT_EINT1_MASK__         (U32)   0x00008000
#define     __INTERRUPT_EINT2_MASK__         (U32)   0x00010000
#define     __INTERRUPT_ALL__                (U32)   0x0001FFFF

#define     __INTERRUPT_WDT_VALUE__          (U8)    0x0
#define     __INTERRUPT_SOFTWARE_VALUE__     (U8)    0x1
#define     __INTERRUPT_DbgCommRx_VALUE__    (U8)    0x2
#define     __INTERRUPT_DbgCommTX_VALUE__    (U8)    0x3
#define     __INTERRUPT_TIMER0_VALUE__       (U8)    0x4
#define     __INTERRUPT_TIMER1_VALUE__       (U8)    0x5
#define     __INTERRUPT_UART0_VALUE__        (U8)    0x6
#define     __INTERRUPT_UART1_VALUE__        (U8)    0x7
#define     __INTERRUPT_PWM_VALUE__          (U8)    0x8
#define     __INTERRUPT_I2C_VALUE__          (U8)    0x9
#define     __INTERRUPT_SPI_SSP_VALUE__      (U8)    0xA
#define     __INTERRUPT_RESERVED_VALUE__     (U8)    0xB     
#define     __INTERRUPT_PLL_VALUE__          (U8)    0xC
#define     __INTERRUPT_RTC_VALUE__          (U8)    0xD
#define     __INTERRUPT_EINT0_VALUE__        (U8)    0xE
#define     __INTERRUPT_EINT1_VALUE__        (U8)    0xF
#define     __INTERRUPT_EINT2_VALUE__        (U8)    0x10


#endif
