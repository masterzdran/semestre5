/**
#=======================================================================
# SE1   - Sistemas Embebidos 1
#-----------------------------------------------------------------------
# Turma:	LI51N
# Semestre:	Inverno 2010/2011
# Data:		Novembro/2010
#-----------------------------------------------------------------------
# Nome: 	Nuno Cancelo
# Numero:	31401
#-----------------------------------------------------------------------
# Nome:		Nuno Sousa
# Numero:	33595
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Informática e Computadores
# DEETC - Dep. de Eng. Electrónica e Telecomunicações e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
**/ 
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
