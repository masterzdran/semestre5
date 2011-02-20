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
#include "MenuFunctions.h"
#include "LCD.h"
#include "stdio.h"
#include "RTC.h"

void printToLCD(char* line0,char* line1){
  LCD_writeLine(0,line0); LCD_writeLine(1,line1);    
}
void printDateTime(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];
  sprintf(text,"%4.4d-%2.2d-%2.2d %2.2d:%2.2d",percurso->beginDate.year,percurso->beginDate.month,percurso->beginDate.day,percurso->beginTime.hour,percurso->beginTime.minute);
  printToLCD("Route Start Date",text);
}
void printDistance(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];  
  sprintf(text,"%4d.%3.3d Km",percurso->distance/1000,percurso->distance%1000);
  printToLCD("Distance Made",text);
}
void printTime(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];  
  sprintf(text,"%5dH %2.2dM",percurso->spentTime/(3600*1000),percurso->spentTime/(60*1000));
  printToLCD("Time Spent",text);
}
void printMaxSpeed(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];
  sprintf(text,"%3d Km/h",percurso->maxSpeed);
  printToLCD("Max Speed",text);
}
void printAvgSpeed(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];
  sprintf(text,"%3d Km/h",percurso->averageSpeed);
  printToLCD("Average Speed",text);
}
void printTotalDistance(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];
  sprintf(text,"%3d.%3.3d Km",percurso->totalDistance/1000+percurso->distance/1000,percurso->totalDistance%1000+percurso->distance%1000);
  printToLCD("Total Distance",text);
}
void printTotalTime(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];
  sprintf(text,"%5dH %2.2dM",percurso->totalTime/3600+percurso->spentTime/(3600*1000),percurso->totalTime/60+percurso->spentTime/(60*1000));
  printToLCD("Total Time Spent",text);
}

void resetTotal(PVOID course){
    pPercurso percurso = (pPercurso)course;
    percurso->vptr->start(percurso,0,0);
    printToLCD("Total Time and","Distance reseted");
}
