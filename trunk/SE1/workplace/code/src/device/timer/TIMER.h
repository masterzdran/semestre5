#ifndef TIMER_H
#define TIMER_H
#include "TYPES.h"
#include "startosc.h"

#define __TCR_DISABLE__                  0x0
#define __TCR_ENABLE__                   0x1
#define __TCR_RESET_DISABLE__            0x0
#define __TCR_RESET_ENABLE__             0x2

#define __CTCR_MODE_0__                  0x0
#define __CTCR_MODE_1__                  0x1
#define __CTCR_MODE_2__                  0x2
#define __CTCR_MODE_3__                  0x3

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
    U32		EMR;          //0xE000 403C
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
    U32   CTCR;         //0xE000 4070
}LPC_TIMER,*pLPC_TIMER;

#define pTIMER0 ((pLPC_TIMER) 0xE0004000)
#define pTIMER1 ((pLPC_TIMER) 0xE0008000)

#define SECOND  1
#define MILI    1000
#define MICRO   1000000
#define NANO    1000000000 //in this oscilator is not possible to go at nano level :(
#define XCLOCK  58982400

//#define     timer_sleep_seconds(A,B)          (timer_delay(A,(XCLOCK/SECOND/(A)->PR)*B))
//#define     timer_sleep_miliseconds(A,B)      (timer_delay(A,(XCLOCK/MILI/(A)->PR)*B))
#define     timer_sleep_miliseconds(A,B)      (timer_delay(A,(58982400/1000/58)*B))
//#define     timer_sleep_microseconds(A,B)     (timer_delay(A,(XCLOCK/MICRO/(A)->PR)*B))

#define timer_start(A)                  ((A)->TCR |= __TCR_ENABLE__)
#define timer_stop(A)                   ((A)->TCR &= ~(__TCR_DISABLE__))
#define timer_elapsed(A,B)              ((A)->TC - B)

#define timer_reset(A)                  {(A)->TCR |= __TCR_RESET_ENABLE__; (A)->TCR &= ~(__TCR_RESET_DISABLE__);}

void timer_init(pLPC_TIMER timer, U32 countNbr);
void timer_delay(pLPC_TIMER timer, U32 elapse);

#endif
