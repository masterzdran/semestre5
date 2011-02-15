#ifndef __TACOGRAFO_H__
#define __TACOGRAFO_H__

#define isRunning(A)	((((A)->CR1)==0)?0:1)

void timer0isr(void) __attribute__ ((interrupt));
void Tacografo_init();
void updateSpeed();

#endif
