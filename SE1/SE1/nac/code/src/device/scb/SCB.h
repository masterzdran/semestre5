#ifndef SCB_H
#define SCB_H

#define    pEXT_INT       ((pLPC_EXT_INT) 0xE01FC140)
#define    pMAM           ((pLPC_MAM)     0xE01FC000)     
#define    pPLL           ((pLPC_PLL)     0xE01FC080)     
#define    pPOWER         ((pLPC_POWER)   0xE01FC0C0)
#define    pAPBDIV        ((pLPC_APB)     0xE01FC100)
#define    pSCS           ((pLPC_SCS)     0xE01FC1A0)


typedef struct _EXT{
    U8     EXTINT;
    U8     DUMMY01;
    U16    DUMMY02;
    U8     EXTWAKE;
    U8     DUMMY03;
    U16    DUMMY04;
    U8     EXTMODE;
    U8     DUMMY05;
    U16    DUMMY06;
    U8     EXTPOLAR;
    U8     DUMMY07;
    U16    DUMMY08;
}LPC_EXT_INT,*pLPC_EXT_INT;


typedef struct _MAM{
    U32 CONTROL_REGISTER;
    U32 TIMING;          
    U32 DUMMY01;         
    U32 DUMMY02;         
    U32 DUMMY03;         
    U32 DUMMY04;         
    U32 DUMMY05;         
    U32 DUMMY06;         
    U32 DUMMY07;         
    U32 DUMMY08;         
    U32 DUMMY09;         
    U32 DUMMY10;         
    U32 DUMMY11;         
    U32 DUMMY12;         
    U32 DUMMY13;         
    U32 DUMMY14;         
    U8  MEMORY_MAPPING_CONTROL; 
    U8  DUMMY15;
    U16 DUMMY16;
}LPC_MAM,*pLPC_MAM;


typedef struct _PLL{
    U8    CONTROL;
    U8    DUMMY01;
    U16   DUMMY02;
    U8    CONFIGURATION;
    U8    DUMMY03;
    U16   DUMMY04;
    U16   STATUS;
    U16   DUMMY05;
    U8    FEED;
    U8    DUMMY06;
    U16   DUMMY07;
}LPC_PLL,*pLPC_PLL;

typedef struct _POWER{
    U32   POWER_CONTROL;
    U32   POWER_CONTROL_PERIPHERICAL;
}LPC_POWER,*pLPC_POWER;



typedef struct _APB{
    U32   APBDIV;
}LPC_APB,*pLPC_APB;

typedef struct _SCS{
    U32   SCS; b  
}LPC_SCS,*pLPC_SCS;


#define __EXTERNAL_INT_EINT0_ENABLE__               ((const unsigned char )0x01)
#define __EXTERNAL_INT_EINT1_ENABLE__               ((const unsigned char )0x02)
#define __EXTERNAL_INT_EINT2_ENABLE__               ((const unsigned char )0x04)
#define __EXTERNAL_INT_MASK__                       ((const unsigned char )0x07)

#define __INTERRUPT_WAKEUP_EXTWAKE0_ENABLE__        ((const unsigned char )0x01)
#define __INTERRUPT_WAKEUP_EXTWAKE1_ENABLE__        ((const unsigned char )0x02)
#define __INTERRUPT_WAKEUP_EXTWAKE2_ENABLE__        ((const unsigned char )0x04)
#define __INTERRUPT_WAKEUP_MASK__                   ((const unsigned char )0x07)

#define __EXTERNAL_INT_MODE_EXTMODE0_ENABLE__       ((const unsigned char )0x01)
#define __EXTERNAL_INT_MODE_EXTMODE0_ENABLE__       ((const unsigned char )0x02)
#define __EXTERNAL_INT_MODE_EXTMODE0_ENABLE__       ((const unsigned char )0x04)
#define __EXTERNAL_INT_MODE_EXTMODE0_ENABLE__       ((const unsigned char )0x07)

#define __EXTERNAL_INT_POLARITY_EXTPOLAR0_ENABLE__  ((const unsigned char )0x01)
#define __EXTERNAL_INT_POLARITY_EXTPOLAR1_ENABLE__  ((const unsigned char )0x02)
#define __EXTERNAL_INT_POLARITY_EXTPOLAR2_ENABLE__  ((const unsigned char )0x04)
#define __EXTERNAL_INT_POLARITY_MASK__              ((const unsigned char )0x07)

#define __SYSTEM_CONTROL_AND_STATUS_ENABLE__        ((const unsigned char )0x01)
#define __SYSTEM_CONTROL_AND_STATUS_MASK__          ((const unsigned char )0x01)

#define __MEMORY_MAP_CONTROL_BOOTLOADER__           ((const unsigned char )0x00)
#define __MEMORY_MAP_CONTROL_USERFLASH__            ((const unsigned char )0x01)
#define __MEMORY_MAP_CONTROL_USERRAM__              ((const unsigned char )0x02)
#define __MEMORY_MAP_CONTROL_RESERVED__             ((const unsigned char )0x03)
#define __MEMORY_MAP_CONTROL_MASK__                 ((const unsigned char )0x03)

#define     __PLL_M_VALUE__                         ((const unsigned char ) 0x03 )
#define     __PLL_P_VALUE__                         ((const unsigned char ) 0x20 )
#define     __PLL_FEED_AA__                         ((const unsigned char ) 0xAA )
#define     __PLL_FEED_55__                         ((const unsigned char ) 0x55 )

#define     __PLLCON_PLLE_ENABLE__                  ((const unsigned char ) 0x1 )
#define     __PLLCON_PLLC_CONNECT__                 ((const unsigned char ) 0x2 )
#define     __PLLCON_MASK__                         ((const unsigned char ) 0x3 )

#define     __PLLCFG_MSEL_MASK__                    ((const unsigned char ) 0x1F)
#define     __PLLCFG_PSEL_MASK__                    ((const unsigned char ) 0x96)
#define     __PLLCFG_MASK__                         ((const unsigned char ) 0x7F)

#define     __PLLSTAT_MSEL_MASK__                   ((const unsigned char ) 0x1F)
#define     __PLLSTAT_PSEL_MASK__                   ((const unsigned char ) 0x96)
#define     __PLLSTAT_PLLE_MASK__                   ((const unsigned short) 0x100) 
#define     __PLLSTAT_PLLC_MASK__                   ((const unsigned short) 0x200) 
#define     __PLLSTAT_PLOCK_MASK__                  ((const unsigned short) 0x400) 
#define     __PLL_MASK__                            ((const unsigned short) 0x7FF) 

#define     __PLL_CONTROL_OFF_DISCONNECTED__        ((const unsigned char ) 0x00)
#define     __PLL_CONTROL_ON_DISCONNECTED__         ((const unsigned char ) 0x01)
#define     __PLL_CONTROL_OFF_DISCONNECTED_PLLCON__ ((const unsigned char ) 0x02)
#define     __PLL_CONTROL_OFF_CONNECTED__           ((const unsigned char ) 0x03)

#define     __POWER_CONTROL_IDL_ENABLE__            ((const unsigned char ) 0x01)
#define     __POWER_CONTROL_PD_ENABLE__             ((const unsigned char ) 0x02)

#define     __PCTIM0_ENABLE__     ((const unsigned U32 ) 0x000002)
#define     __PCTIM1_ENABLE__     ((const unsigned U32 ) 0x000004)
#define     __PCUART0_ENABLE__    ((const unsigned U32 ) 0x000008)
#define     __PCUART1_ENABLE__    ((const unsigned U32 ) 0x000010)
#define     __PCPWM0_ENABLE__     ((const unsigned U32 ) 0x000020)
#define     __PCI2C_ENABLE__      ((const unsigned U32 ) 0x000080)
#define     __PCSPI_ENABLE__      ((const unsigned U32 ) 0x000100)
#define     __PCRTC_ENABLE__      ((const unsigned U32 ) 0x000200)
#define     __PCSSP_ENABLE__      ((const unsigned U32 ) 0x200000)
#define     __POWER_MASK__        ((const unsigned U32 ) 0x2003BE)

#define     __APBDIV_CLOCK_1_FOURTH_CLOCK__            ((const unsigned short) 0x0 )
#define     __APBDIV_CLOCK_EQUAL_CLOCK__               ((const unsigned short) 0x1 )
#define     __APBDIV_CLOCK_HALF_CLOCK__                ((const unsigned short) 0x2 )
#define     __APBDIV_MASK__                            ((const unsigned short) 0x3 ) 

#define     __MAM_FULLY_ENABLE__                    ((const unsigned char ) 0x2 )
#define     __MAM_PARTIAL_ENABLE__                  ((const unsigned char ) 0x1 )
#define     __MAM_DISABLE__                         ((const unsigned char ) 0x0 )

#define     __MAMTIM_FETCH_4_CLOCK__                ((const unsigned char ) 0x4 )



#endif
