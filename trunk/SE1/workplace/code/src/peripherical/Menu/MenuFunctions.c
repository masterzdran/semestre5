#include "MenuFunctions.h"
#include "LCD.h"
#include "stdio.h"

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
  sprintf(text,"%3.3d Km/h",percurso->distance);
  printToLCD("Distance Made",text);
}
void printTime(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];  
  sprintf(text,"%5.5dH %2.2M",percurso->spentTime/60,percurso->spentTime%60);
  printToLCD("Time Spent",text);

}
void printMaxSpeed(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];
  sprintf(text,"%3.3d Km/h",percurso->maxSpeed);
  printToLCD("Max Speed",text);

}
void printAvgSpeed(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];
  sprintf(text,"%3.3d Km/h",percurso->averageSpeed);
  printToLCD("Average Speed",text);
}
void printTotalDistance(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];
  sprintf(text,"%3.3d Km",percurso->totalDistance);
  printToLCD("Total Distance",text);
}
void printTotalTime(PVOID course){
  pPercurso percurso = (pPercurso)course;
  char text[16];
  sprintf(text,"%5.5dH %2.2M",percurso->totalTime/60,percurso->totalTime%60);
  printToLCD("Total Time Spent",text);
}

void resetTotal(PVOID course){
    pPercurso percurso = (pPercurso)course;
    percurso->totalDistance = 0;
    percurso->totalTime =0;
    printToLCD("Total Time and","Distance reseted");
}
