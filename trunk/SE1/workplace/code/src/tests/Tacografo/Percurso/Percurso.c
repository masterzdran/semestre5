#include "Percurso.h"
#include "RTC.h"

void percurso_updateSpeed(Percurso* percurso, U32* tickTime, U32* tickCount){
  U32 Time= (U32)(*tickTime);
  U32 Count= (U32)(*tickCount);
  if (tickTime){
    //is running
    percurso->vptr->addSpentTime(percurso, (Time)/1000);
    percurso->vptr->updateDistance(percurso, (Count)*__METERS_PER_TICK__);
    //speed in km/h
    percurso->vptr->setCurrentSpeed(percurso, (((Count) * __METERS_PER_TICK__)*3600000)/(Time));
    percurso->vptr->updateAverageSpeed(percurso);
    *tickCount=0;
    *tickTime=0;
    
  }else{
    //is stopped
    percurso->vptr->addStopTime(percurso, (pTIMER0->TC)/1000);
    timer_reset(pTIMER0);
    percurso->vptr->setCurrentSpeed(percurso,0);
  }
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

void percurso_addStopTime(Percurso* percurso, U32 time){
  percurso->stopTime+=time;
  percurso->spentTime+=time;
}

void percurso_addSpentTime(Percurso* percurso, U32 time){
  percurso->spentTime+=time;
}

void percurso_updateDistance(Percurso* percurso, U16 dist){
  percurso->distance+=dist;
}

void percurso_updateAverageSpeed(Percurso* percurso){
  percurso->averageSpeed=((percurso->distance*3600)/(percurso->spentTime-percurso->stopTime));
}

void percurso_setCurrentSpeed(Percurso* percurso, U8 speed){
  percurso->currentSpeed=speed;
  if (speed > percurso->maxSpeed)
    percurso->maxSpeed=speed;
}

void percurso_start(Percurso* percurso, U32 tDistance, U32 tTime){
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
/**
 * Tabela de métodos virtuais
 * */
const static Percurso_Methods percurso_vtable={
	(const void (*) (Percurso*))        percurso_resetValues,
	(const void (*) (Percurso*,U32))    percurso_addStopTime,
	(const void (*) (Percurso*,U32))    percurso_addSpentTime,
	(const void (*) (Percurso*,U16))    percurso_updateDistance,
	(const void (*) (Percurso*))        percurso_updateAverageSpeed,
	(const void (*) (Percurso*,U8))     percurso_setCurrentSpeed,
	(const void (*) (Percurso*,U32, U32))        percurso_updateSpeed,
	(const void (*) (Percurso*,U32, U32))        percurso_start
};

void percurso_init(Percurso* percurso, U32 tDistance, U32 tTime){
  percurso->vptr = &percurso_vtable;
  percurso->vptr->start(percurso,0,0);
}


