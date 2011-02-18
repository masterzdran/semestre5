#ifndef __PERCURSO_H__
#define __PERCURSO_H__
#include "TYPES.h"

void percurso_init(Percurso* percurso, U32 tDistance, U32 tTime);
void percurso_resetValues(Percurso* percurso);
void  percurso_addStopTime(Percurso* percurso, U32 time);
void  percurso_addSpentTime(Percurso* percurso, U32 time);
void percurso_updateDistance(Percurso* percurso, U16 dist);
void percurso_updateAverageSpeed(Percurso* percurso);
void percurso_setCurrentSpeed(Percurso* percurso, U8 speed);

#endif
