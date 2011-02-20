#ifndef __PERCURSO_H__
#define __PERCURSO_H__
#include "TYPES.h"
#include "TIMER.h"
#define __MAX_SPEED_UPDATE_TIMEOUT__ 	1000000		//1 seconds
#define __TICK_STOPPED_TIMEOUT__ 		3750000		//3.75 seconds - 1km/h=3.59s between ticks
#define __MAX_SAVE_TIMEOUT__		 	60			//60 seconds
#define __MAX_SAVE_DISTANCE__			1000		//1 km

#define __METERS_PER_TICK__		1

void percurso_init(Percurso* percurso, U32 tDistance, U32 tTime);
/*
void percurso_resetValues(Percurso* percurso);
void percurso_addStopTime(Percurso* percurso, U32 time);
void percurso_addSpentTime(Percurso* percurso, U32 time);
void percurso_updateDistance(Percurso* percurso, U16 dist);
void percurso_updateAverageSpeed(Percurso* percurso);
void percurso_setCurrentSpeed(Percurso* percurso, U8 speed);
void percurso_updateSpeed(Percurso* percurso, U32* tickTime, U32* tickCount);
*/
#endif
