#ifndef __MENU_FUNCTIONS_H__
#define __MENU_FUNCTIONS_H__

#include "TYPES.h"
/*
 * Menu 1 Functions
 * */
void printToLCD(char* line0,char* line1);
void printDateTime(pPercurso percurso);
void printDistance(pPercurso percurso);
void printTime(pPercurso percurso);
void printMaxSpeed(pPercurso percurso);
void printAvgSpeed(pPercurso percurso);
void printTotalDistance(pPercurso percurso);
void printTotalTime(pPercurso percurso);

/*
 * Menu 2 Functions
 * */
void setClock(pPercurso percurso);
void resetTotal(pPercurso percurso);
#endif
