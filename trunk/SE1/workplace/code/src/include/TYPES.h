/*
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
#=====================================================================
*/
#ifndef TYPES_H
#define TYPES_H
//TYPE DEFINITION
typedef volatile unsigned int       U32;
typedef unsigned short int          U16;
typedef unsigned char               U8;

typedef volatile unsigned long*    PU32;
typedef volatile unsigned short*   PU16;
typedef volatile unsigned char*    PU8;


typedef   U8    byte;
typedef   PU8   Pbyte;
typedef   PU16  PWord;
typedef   PU32  PDWord;


typedef struct _date{
  U16    year; 
  U8     month;
  U8     day;  
}DATE;

typedef struct _time{
  U8     hour;
  U8     minute;
  U8     second;  
}TIME;

enum boolean {false,true};
typedef enum boolean Bool ;


typedef struct _datetime{
  DATE date;
  TIME time;
}DATE_TIME;

typedef struct _percurso{
  DATE beginDate;
  TIME beginTime;
  U16  spentTime;//in minutes
  U16  distance; //in meters
  U8   maxSpeed; //in KM/s
  U8   averageSpeed; // in KM/s
  U32  totalDistance;
  U32  totalTime;
}Percurso,*pPercurso;

enum KEYBOARD_KEYS{
  MENU    = 0x7E,
  OK      = 0x7D,
  CANCEL  = 0x7B,
  RESET   = 0x77,
  UP      = 0xDB,
  DOWN    = 0xD7,
  LEFT    = 0xE7,
  RIGHT   = 0xB7  
};
typedef enum KEYBOARD_KEYS KB_Key;

typedef struct _option{
  char* text;
  void (*function) (pPercurso percurso);
}Option,pOption;

typedef enum _status {MAIN=0,OK_PRESS,MENU_PRESS,RESET_PRESS,FULLRESET,READ,WRITE,WAIT} Status;
#endif
