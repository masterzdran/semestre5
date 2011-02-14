#ifndef __COURSE_H__
#define __COURSE_H__
#include "TYPES.h"

typedef struct _COURSE{
  U32 TotalDistance;
  U32 TotalUsageTime;
  DATE startDate;
  TIME startTime;
}Course;

void initCourse();
void setStartDateTime(DATE date, DATE time);
void resetValues();
void addStopTime(U32 minutes);
void addWalkTime(U32 minutes);
void testAndSetMaxSpeed(U32 speed);
void saveCourse();

#endif
