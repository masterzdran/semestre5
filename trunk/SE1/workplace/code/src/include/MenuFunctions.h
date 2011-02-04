#ifndef __MENU_FUNCTIONS_H__
#define __MENU_FUNCTIONS_H__

#include "TYPES.h"
/*
 * Menu 1 Functions
 * */
void printToLCD(char* line0,char* line1);
void printDateTime(PVOID course);
void printDistance(PVOID course);
void printTime(PVOID course);
void printMaxSpeed(PVOID course);
void printAvgSpeed(PVOID course);
void printTotalDistance(PVOID course);
void printTotalTime(PVOID course);

/*
 * Menu 2 Functions
 * */
void setClock(PVOID percurso);
void resetTotal(PVOID percurso);
#endif
