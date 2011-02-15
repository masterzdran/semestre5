#include "Percurso.h"
#include "RTC.h"
#include "Clock.h"

void percurso_init(Percurso* percurso, U32 tDistance, U32 tTime){
  rtc_getDate(&percurso->beginDate);
  rtc_getTime(&percurso->beginTime);
  percurso->spentTime=0;
  percurso->stopTime=0;
  percurso->distance=0;
  percurso->maxSpeed=0;
  percurso->averageSpeed=0;
  percurso->totalDistance=tDistance;
  percurso->totalTime=tTime;
}

void percurso_resetValues(Percurso* percurso){
  percurso->totalTime+=Clock_timeSecToMin(percurso->spentTime);
  percurso->totalDistance+=percurso->distance;
  rtc_getDate(&percurso->beginDate);
  rtc_getTime(&percurso->beginTime); 
  percurso->spentTime=0;
  percurso->stopTime=0;
  percurso->distance=0;
  percurso->maxSpeed=0;
  percurso->averageSpeed=0;
}

U32 percurso_addStopTime(Percurso* percurso, U32 init_time){
  U32 now = Clock_getCurrentTimeSeconds();
  percurso->stopTime+=now-init_time;
  percurso->spentTime+=now-init_time;
  return now;
}
U32 percurso_addSpentTime(Percurso* percurso, U32 init_time){
  U32 now = Clock_getCurrentTimeSeconds();
  percurso->spentTime+=now-init_time;
  return now;
}

void percurso_testAndSetMaxSpeed(Percurso* percurso, U32 speed){
  if (speed > percurso->maxSpeed)
	percurso->maxSpeed=speed;
}
void percurso_updateDistance(Percurso* percurso, U32 tick){
  percurso->distance+=tick * __METERS_PER_TICK__;
}
void percurso_updateAverageSpeed(Percurso* percurso){
  percurso->averageSpeed=(percurso->distance/(percurso->spentTime-percurso->stopTime))*3.6;
}

void percurso_saveCourse(Percurso* percurso){
	
}
void percurso_loadCourse(Percurso* percurso){
	
}
