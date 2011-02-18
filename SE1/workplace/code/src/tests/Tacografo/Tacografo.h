#ifndef __TACOGRAFO_H__
#define __TACOGRAFO_H__

#define __MAX_SPEED_UPDATE_TIMEOUT__ 	1000000		//1 seconds
#define __TICK_STOPPED_TIMEOUT__ 		3750000		//3.75 seconds - 1km/h=3.59s between ticks
#define __MAX_SAVE_TIMEOUT__		 	60			//60 seconds
#define __MAX_SAVE_DISTANCE__			1000		//1 km

#define __METERS_PER_TICK__		1

void timer0isr(void) __attribute__ ((interrupt));
void Tacografo_init();
void updateSpeed();

#endif
