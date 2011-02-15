#ifndef __PERCURSO_H__
#define __PERCURSO_H__
#include "TYPES.h"

#define __METERS_PER_TICK__		1

void percurso_init(Percurso* percurso, U32 tDistance, U32 tTime);
void percurso_resetValues(Percurso* percurso);
U32  percurso_addStopTime(Percurso* percurso, U32 init_time);
U32  percurso_addSpentTime(Percurso* percurso, U32 init_time);
void percurso_testAndSetMaxSpeed(Percurso* percurso, U32 speed);
void percurso_updateDistance(Percurso* percurso, U32 tick);
void percurso_saveCourse(Percurso* percurso);
void percurso_loadCourse(Percurso* percurso);

#endif
