#include "Percurso.h"
#include "RTC.h"
/*
typedef struct _percurso{
  DATE beginDate;
  TIME beginTime;
  U32  spentTime;		//in miliseconds
  U32  stopTime;		//in miliseconds
  U16  distance; 		//in meters
  U8   currentSpeed;	//in km/h
  U8   maxSpeed; 		//in km/h
  U8   averageSpeed; 	//in km/h
  U32  totalDistance;	//in meters
  U32  totalTime;		//in seconds
}Percurso,*pPercurso;
 * */
void percurso_init(Percurso* percurso, U32 tDistance, U32 tTime){
  rtc_getDate(&percurso->beginDate);
  rtc_getTime(&percurso->beginTime);
  percurso->spentTime=0;
  percurso->stopTime=0;
  percurso->distance=0;
  percurso->currentSpeed=0;
  percurso->maxSpeed=0;
  percurso->averageSpeed=0;
  percurso->totalDistance=tDistance;
  percurso->totalTime=tTime;
}

void percurso_resetValues(Percurso* percurso){
  percurso->totalTime+=percurso->spentTime/1000;
  percurso->totalDistance+=percurso->distance;
  rtc_getDate(&percurso->beginDate);
  rtc_getTime(&percurso->beginTime); 
  percurso->spentTime=0;
  percurso->stopTime=0;
  percurso->distance=0;
  percurso->currentSpeed=0;
  percurso->maxSpeed=0;
  percurso->averageSpeed=0;
}

inline void percurso_addStopTime(Percurso* percurso, U32 time){
  percurso->stopTime+=time;
  percurso->spentTime+=time;
}

inline void percurso_addSpentTime(Percurso* percurso, U32 time){
  percurso->spentTime+=time;
}

inline void percurso_updateDistance(Percurso* percurso, U16 dist){
  percurso->distance+=dist;
}

inline void percurso_updateAverageSpeed(Percurso* percurso){
  percurso->averageSpeed=((percurso->distance*3600)/(percurso->spentTime-percurso->stopTime));
}

inline void percurso_setCurrentSpeed(Percurso* percurso, U8 speed){
  percurso->currentSpeed=speed;
    if (speed > percurso->maxSpeed)
	percurso->maxSpeed=speed;
}
