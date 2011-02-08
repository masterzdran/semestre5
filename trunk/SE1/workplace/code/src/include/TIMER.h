/**
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
**/ 
#ifndef TIMER_H
#define TIMER_H
#include "TYPES.h"
#include "GPIO.h"
#include "startosc.h"

#define __TCR_DISABLE__                  0x0
#define __TCR_ENABLE__                   0x1
#define __TCR_RESET_DISABLE__            0x0
#define __TCR_RESET_ENABLE__             0x2

#define __CTCR_MODE_0__                  0x0
#define __CTCR_MODE_1__                  0x1
#define __CTCR_MODE_2__                  0x2
#define __CTCR_MODE_3__                  0x3

#define __EMR_M

#define __INTERRUPT_MR0__                 1 << 0
#define __RESET_MR0__                     1 << 1       
#define __STOP_MR0__                      1 << 2
#define __INTERRUPT_MR1__                 1 << 3
#define __RESET_MR1__                     1 << 4
#define __STOP_MR1__                      1 << 5
#define __INTERRUPT_MR2__                 1 << 6
#define __RESET_MR2__                     1 << 7
#define __STOP_MR2__                      1 << 8
#define __INTERRUPT_MR3__                 1 << 9
#define __RESET_MR3__                     1 << 10
#define __STOP_MR3__                      1 << 11

#define __CAPTURE0_RISING_EDGE__          1 << 0
#define __CAPTURE0_FALLING_EDGE__         1 << 1       
#define __CAPTURE0_INTERRUPT__            1 << 2
#define __CAPTURE1_RISING_EDGE__          1 << 3
#define __CAPTURE1_FALLING_EDGE__         1 << 4
#define __CAPTURE1_INTERRUPT__            1 << 5

#define __CAP1_MSK__                      ~(__CAPTURE1_RISING_EDGE__|__CAPTURE1_FALLING_EDGE__|__CAPTURE1_INTERRUPT__)
#define __CAPTURE2_RISING_EDGE__          1 << 6
#define __CAPTURE2_FALLING_EDGE__         1 << 7
#define __CAPTURE2_INTERRUPT__            1 << 8
#define __CAPTURE3_RISING_EDGE__          1 << 9
#define __CAPTURE3_FALLING_EDGE__         1 << 10
#define __CAPTURE3_INTERRUPT__            1 << 11

enum TIMER_MATCH {
  MAT00 =__PINSEL0_TIMER_0_MATCH_0_0__,
  MAT01 =__PINSEL0_TIMER_0_MATCH_0_1__,
  MAT10 =__PINSEL0_TIMER_1_MATCH_1_0__,
  MAT11 =__PINSEL0_TIMER_1_MATCH_1_1__
};
typedef enum TIMER_MATCH TMatch ;

enum TIMER_CAPTURE {
  CAP00 = __PINSEL0_TIMER_0_CAPTURE_0_0__,
  CAP01 = __PINSEL0_TIMER_0_CAPTURE_0_1__,
  CAP02 = __PINSEL0_TIMER_0_CAPTURE_0_2__,
  CAP10 = __PINSEL0_TIMER_1_CAPTURE_1_0__,
  CAP11 = __PINSEL0_TIMER_1_CAPTURE_1_1__
};
typedef enum TIMER_CAPTURE TCapture ;

#define __MATCH_INTERRUPT__                 (1 << 0)
#define __MATCH_RESET__                     (1 << 1)       
#define __MATCH_STOP__                      (1 << 2)

#define __CAPTURE_RISE__                    (1<<0)
#define __CAPTURE_FALL__                    (1<<1)
#define __CAPTURE_INTERRUPT__               (1<<2)

typedef enum EMR_FUNCTION {MATCH_NOTHING=0,MATCH_CLEAR,MATCH_SET,MATCH_TOGGLE} tEmrFunction;
typedef enum CTCR_FUNCTION {TIMER_MODE=0,COUNTER_MODE_RISE,COUNTER_MODE_FALL,COUNTER_MODE_BOTH} tCtcrFunction;
typedef struct _TIMER{
    U32		IR;             
    U32		TCR;
    U32		TC;
    U32		PR;
    U32		PC;
    U32		MCR;
    U32		MR0;
    U32		MR1;
    U32		MR2;
    U32		MR3;
    U32		CCR;
    U32		CR0;
    U32		CR1;
    U32		CR2;
    U32		CR3;          
    U32		EMR;             //0xE000 403C
    U32   DUMMY01;         //0xE000 4040
    U32   DUMMY02;         //0xE000 4044
    U32   DUMMY03;         //0xE000 4048
    U32   DUMMY04;         //0xE000 404C
    U32   DUMMY05;         //0xE000 4050
    U32   DUMMY06;         //0xE000 4054
    U32   DUMMY07;         //0xE000 4058
    U32   DUMMY08;         //0xE000 405C
    U32   DUMMY09;         //0xE000 4060
    U32   DUMMY10;         //0xE000 4064
    U32   DUMMY11;         //0xE000 4068
    U32   DUMMY12;         //0xE000 406C
    U32   CTCR;            //0xE000 4070
}LPC_TIMER,*pLPC_TIMER;

#define pTIMER0 ((pLPC_TIMER) 0xE0004000)
#define pTIMER1 ((pLPC_TIMER) 0xE0008000)

#define SECOND  1
#define MILI    1000
#define MICRO   1000000
#define NANO    1000000000 //in this oscilator is not possible to go at nano level :(

//#define     timer_sleep_seconds(A,B)          (timer_delay(A,(((__SYSTEM_CLOCK__/SECOND)/((A)->PR))*B)))
//#define     timer_sleep_miliseconds(A,B)      (timer_delay(A,(((__SYSTEM_CLOCK__/MILI)/((A)->PR))*B)))
//#define     timer_sleep_microseconds(A,B)     	(timer_delay(A,(((__SYSTEM_CLOCK__/MICRO)/((A)->PR))*B)))
#define     timer_sleep_seconds(A,B)            (timer_delay(A,((( getSystemClock()/SECOND)/((A)->PR))*B)))
#define     timer_sleep_miliseconds(A,B)        (timer_delay(A,((( getSystemClock()/MILI)/((A)->PR))*B)))
#define     timer_sleep_microseconds(A,B)     	(timer_delay(A,((( getSystemClock()/MICRO)/((A)->PR))*B)))
//#define		timer_sleep_seconds(A,B) 		    (timer_delay(A,(58982400/SECOND/58)*B))
//#define     timer_sleep_miliseconds(A,B)    	(timer_delay(A,(58982400/MILI/58)*B))
//#define     timer_sleep_microseconds(A,B)   	(timer_delay(A,(58982400/MICRO/58)*B))

#define timer_start(A)                  ((A)->TCR |= __TCR_ENABLE__)
#define timer_stop(A)                   ((A)->TCR &= ~(__TCR_DISABLE__))
#define timer_elapsed(A,B)              ((A)->TC - B)

#define timer_reset(A)                  {(A)->TCR |= __TCR_RESET_ENABLE__; (A)->TCR &= ~(__TCR_RESET_DISABLE__);}

void timer_init(pLPC_TIMER timer, U32 countNbr);
void timer_delay(pLPC_TIMER timer, U32 elapse);
//void TIMER_match_init(pLPC_TIMER timer,TMatch timerMatch, U32 MatchMask, U32 countNbr);
//void TIMER_capture_init(pLPC_TIMER timer,TCapture timerCapture, U32 captureMask, U32 countNbr);
//void TIMER_ext_match_init(pLPC_TIMER timer,TMatch timerMatch, U32 MatchMask, U32 countNbr);
void TIMER_capture_init(pLPC_TIMER timer,U8 channel, U32 captureMask, U32 countNbr,tCtcrFunction ctcrFunction);
void TIMER_ext_match_init(pLPC_TIMER timer,U8 channel, U32 MatchMask, U32 countNbr,tEmrFunction emrFunction);
#endif
