/*
#=======================================================================
# SE1   - Sistemas Embebidos 1
#-----------------------------------------------------------------------
# Turma:	LI51N
# Semestre:	Inverno 2010/2011
# Data:		Novembro/2010
#-----------------------------------------------------------------------
# Nome: 	Nuno Cancelo
# Numero:	31401
#-----------------------------------------------------------------------
# Nome:		Nuno Sousa
# Numero:	33595
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Informática e Computadores
# DEETC - Dep. de Eng. Electrónica e Telecomunicações e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
*/
#ifndef LPC2106_H
#define LPC2106_H
/*
//TYPE DEFINITION
typedef volatile unsigned int       U32;
typedef unsigned short int          U16;
typedef unsigned char               U8;

typedef volatile unsigned long *   PU32;
typedef volatile unsigned short *  PU16;
typedef volatile unsigned char *   PU8;


typedef U8  byte;
typedef PU8 Pbyte;
typedef PU16 PWord;
typedef PU32 PDWord;
*/

/*---------------------Mapeamento dos periféricos---------------------*/
#define     __WatchdogTimer__                (*((Pbyte) 0xE0000000))
#define     __Timer0__                       (*((PDWord) 0xE0004000))
#define     __Timer1__                       (*((PDWord) 0xE0008000))
#define     __UART0__                        (*((Pbyte) 0xE000C000))
#define     __UART1__                        (*((Pbyte) 0xE0010000))
#define     __PWM0__                         (*((PDWord) 0xE0014000))
#define     __I2C__                          (*((Pbyte) 0xE001C000))
#define     __SPI__                          (*((Pbyte) 0xE0020000))
#define     __RTC__                          (*((Pbyte) 0xE0024000))
#define     __GPIO__                         (*((PDWord) 0xE0028000))
#define     __PinConnectBlock__              (*((PDWord) 0xE002C000))
#define     __SystemControlBlock__           (*((Pbyte) 0xE01FC000))
#define     __VectoredInterruptController__  (*((PDWord) 0xFFFFF000))

/*-----------------------Relógio do sistema P.35----------------------*/
#define     __FOSC__                        ((const unsigned int) 14745600)
#define     __VPB_CLOCK__                     (*((Pbyte) 0xE01FC100))

/*-----------------------Relógio dos periféricos----------------------*/

/*------------------Registos de controlo do PLL P.27------------------*/
#define     __PLL_CONTROL__                  (*((Pbyte) 0xE01FC080))         
#define     __PLL_CONFIGURATION__            (*((Pbyte) 0xE01FC084))         
#define     __PLL_STATUS__                   (*((PWord) 0xE01FC088))         
#define     __PLL_FEED__                     (*((Pbyte) 0xE01FC08C))         

/*-------------------------Consumo de energia P.17---------------------*/
#define     __POWER_CONTROL__                (*((Pbyte)  0xE01FC0C0))         
#define     __POWER_CONTROL_PERIPHERICAL__   (*((PDWord) 0xE01FC0C4))         

/*-------------------Mapeamento da memória P.41-----------------------*/
#define     __MAM_CONTROL_REGISTER__         (*((Pbyte) 0xE01FC000)) 
#define     __MAM_TIMING__                   (*((Pbyte) 0xE01FC004)) 
#define     __MEMORY_MAP_CONTROL__           (*((Pbyte) 0xE01FC040))         

/*----------------General Purpose Input/Output P.63-------------------*/
#define     __PINSEL0__                      (*((PDWord)0xE002C000))
#define     __PINSEL1__                      (*((PDWord)0xE002C004))
#define     __IO0PIN__                        (*((PDWord)0xE0028000))
#define     __IO0SET__                        (*((PDWord)0xE0028004))
#define     __IO0DIR__                        (*((PDWord)0xE0028008)) 
#define     __IO0CLR__                        (*((PDWord)0xE002800C))

/*------------------------------Timer P.190---------------------------*/
/*--------------------------------Timer 0-----------------------------*/
#define     __TIMER_0_IR__                           (*((PDWord) 0xE0004000))
#define     __TIMER_0_TCR__                          (*((PDWord) 0xE0004004))
#define     __TIMER_0_TC__                           (*((PDWord) 0xE0004008))
#define     __TIMER_0_PR__                           (*((PDWord) 0xE000400C))
#define     __TIMER_0_PC__                           (*((PDWord) 0xE0004010))
#define     __TIMER_0_MCR__                          (*((PDWord) 0xE0004014))
#define     __TIMER_0_MR0__                          (*((PDWord) 0xE0004018))
#define     __TIMER_0_MR1__                          (*((PDWord) 0xE000401C))
#define     __TIMER_0_MR2__                          (*((PDWord) 0xE0004020))
#define     __TIMER_0_MR3__                          (*((PDWord) 0xE0004024))
#define     __TIMER_0_CCR__                          (*((PDWord) 0xE0004028))
#define     __TIMER_0_CR0__                          (*((PDWord) 0xE000402C))
#define     __TIMER_0_CR1__                          (*((PDWord) 0xE0004030))
#define     __TIMER_0_CR2__                          (*((PDWord) 0xE0004034))
#define     __TIMER_0_CR3__                          (*((PDWord) 0xE0004038))
#define     __TIMER_0_EMR__                          (*((PDWord) 0xE000403C))
/*--------------------------------Timer 1-----------------------------*/
#define     __TIMER_1_IR__                           (*((PDWord) 0xE0008000))
#define     __TIMER_1_TCR__                          (*((PDWord) 0xE0008004))
#define     __TIMER_1_TC__                           (*((PDWord) 0xE0008008))
#define     __TIMER_1_PR__                           (*((PDWord) 0xE000800C))
#define     __TIMER_1_PC__                           (*((PDWord) 0xE0008010))
#define     __TIMER_1_MCR__                          (*((PDWord) 0xE0008014))
#define     __TIMER_1_MR0__                          (*((PDWord) 0xE0008018))
#define     __TIMER_1_MR1__                          (*((PDWord) 0xE000801C))
#define     __TIMER_1_MR2__                          (*((PDWord) 0xE0008020))
#define     __TIMER_1_MR3__                          (*((PDWord) 0xE0008024))
#define     __TIMER_1_CCR__                          (*((PDWord) 0xE0008028))
#define     __TIMER_1_CR0__                          (*((PDWord) 0xE000802C))
#define     __TIMER_1_CR1__                          (*((PDWord) 0xE0008030))
#define     __TIMER_1_CR2__                          (*((PDWord) 0xE0008034))
#define     __TIMER_1_CR3__                          (*((PDWord) 0xE0008038))
#define     __TIMER_1_EMR__                          (*((PDWord) 0xE000803C))

/*-------------------------Real Time Clock (RTC)----------------------*/
/*----------------------------ADDRESS P.210---------------------------*/
#define     __RTC_ILR__                            (*((Pbyte) 0xE0024000))
#define     __RTC_CTC__                            (*((PWord) 0xE0024004))
#define     __RTC_CCR__                            (*((Pbyte) 0xE0024008))
#define     __RTC_CIIR__                           (*((Pbyte) 0xE002400C))
#define     __RTC_AMR__                            (*((Pbyte) 0xE0024010))
#define     __RTC_CTIME0__                         (*((PDWord) 0xE0024014))
#define     __RTC_CTIME1__                         (*((PDWord) 0xE0024018))
#define     __RTC_CTIME2__                         (*((PDWord) 0xE002401C))
#define     __RTC_SEC__                            (*((Pbyte) 0xE0024020))
#define     __RTC_MIN__                            (*((Pbyte) 0xE0024024))
#define     __RTC_HOUR__                           (*((Pbyte) 0xE0024028))
#define     __RTC_DOM__                            (*((Pbyte) 0xE002402C))
#define     __RTC_DOW__                            (*((Pbyte) 0xE0024030))
#define     __RTC_DOY__                            (*((PWord) 0xE0024034))
#define     __RTC_MONTH__                          (*((Pbyte) 0xE0024038))
#define     __RTC_YEAR__                           (*((PWord) 0xE002403C))
#define     __RTC_ALSEC__                          (*((Pbyte) 0xE0024060))
#define     __RTC_ALMIN__                          (*((Pbyte) 0xE0024064))
#define     __RTC_ALHOUR__                         (*((Pbyte) 0xE0024068))
#define     __RTC_ALDOM__                          (*((Pbyte) 0xE002406C))
#define     __RTC_ALDOW__                          (*((Pbyte) 0xE0024070))
#define     __RTC_ALDOY__                          (*((Pbyte) 0xE0024074))
#define     __RTC_ALMON__                          (*((Pbyte) 0xE0024078))
#define     __RTC_ALYEAR__                         (*((PWord) 0xE002407C))
#define     __RTC_PREINT__                         (*((PWord) 0xE0024080))
#define     __RTC_PREFRAC__                        (*((PWord) 0xE0024084))

/*-----------Universal Asynchronous Receiver/Transmitter (UART)-------*/


/*-----------------------------SPI P.183------------------------------*/
#define     __SPI_CONTROL_REGISTER__               (*((Pbyte) 0xE0020000))       
#define     __SPI_STATUS_REGISTER__                (*((Pbyte) 0xE0020004))       
#define     __SPI_DATA_REGISTER__                  (*((Pbyte) 0xE0020008))       
#define     __SPI_CLOCK_COUNTER_REGISTER__         (*((Pbyte) 0xE002000C))       
#define     __SPI_INTERRUPT_FLAG__                 (*((Pbyte) 0xE002001C))       

/*----------------------------Interrupções----------------------------*/
/*---------------------------External P.20----------------------------*/
#define     __EXTERNAL_INT_FLAG_REGISTER__         (*((Pbyte) 0xE01FC140))
#define     __EXTERNAL_INT_WAKEUP_REGISTER__       (*((Pbyte) 0xE01FC144))

/*-----------------------------I2C P.129------------------------------*/
#define     __I2C_CONTROL_SET_REGISTER__                 (*((Pbyte) 0xE001C000))
#define     __I2C_STATUS_REGISTER__                      (*((Pbyte) 0xE001C004))
#define     __I2C_DATA_REGISTER__                        (*((Pbyte) 0xE001C008))
#define     __I2C_SLAVE_ADDRESS_REGISTER__               (*((Pbyte) 0xE001C00C))
#define     __I2C_DUTY_CYCLE_HIGH_HALF_WORD_REGISTER__   (*((Pbyte) 0xE001C010))
#define     __I2C_DUTY_CYCLE_LOW_HALF_WORD_REGISTER__    (*((Pbyte) 0xE001C014))
#define     __I2C_CONTROL_CLEAR_REGISTER__               (*((Pbyte) 0xE001C018))

/*---------------------------WatchDog P.222---------------------------*/
#define     __WATCHDOG_MODE_REGISTER__                   (*((Pbyte) 0xE0000000))
#define     __WATCHDOG_TIMER_CONSTANT_REGISTER__         (*((PDWord) 0xE0000004))
#define     __WATCHDOG_FEED_SEQUENCE_REGISTER__          (*((Pbyte) 0xE0000008))
#define     __WATCHDOG_TIMER_VALUE_REGISTER__            (*((PDWord) 0xE000000C))

#endif
