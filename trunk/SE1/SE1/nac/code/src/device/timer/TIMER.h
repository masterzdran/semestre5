#ifndef TIMER_H
#define TIMER_H

#define pTIMER0 (((pLPC_TIMER) 0xE0004000))
#define pTIMER1 (((pLPC_TIMER) 0xE0008000))


#define __TCR_DISABLE__                  0b00
#define __TCR_ENABLE__                   0b01
#define __TCR_RESET_DISABLE__            0b10
#define __TCR_RESET_ENABLE__             0b10

#define __CTCR_MODE_0__    0b00
#define __CTCR_MODE_1__    0b01
#define __CTCR_MODE_2__    0b10
#define __CTCR_MODE_3__    0b11

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
    U32		EMR;
    U32   CTCR;
}LPC_TIMER,*pLPC_TIMER;

#define SECOND  1
#define MILI    1000
#define MICRO   1000000
#define NANO    1000000000 //in this oscilator is not possible to go at nano level :(





#define     timer_sleep_seconds(A,B)          (timer_delay(A,(CCLK/SECOND)*B))
#define     timer_sleep_miliseconds(A,B)      (timer_delay(A,(CCLK/MILI)*B)
#define     timer_sleep_microseconds(A,B)     (timer_delay(A,(CCLK/MICRO)*B))

#define timer_start(A)                  ((A)->TCR |= __TCR_ENABLE__)
#define timer_stop(A)                   ((A)->TCR &= ~(__TCR_DISABLE__))
#define timer_elapsed(A,B)              ((A)->TC - B)


void timer_init(pLPC_TIMER timer, U32 countNbr);
void timer_delay(pLPC_TIMER timer, U32 elapse);
void timer_reset(pLPC_TIMER timer);

#endif
