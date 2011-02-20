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
#=====================================================================
*/
#ifndef TYPES_H
#define TYPES_H
/**
 * Definição de tipos
 * */
typedef volatile unsigned int       U32;
typedef unsigned short int          U16;
typedef unsigned char               U8;

typedef signed int       			S32;
typedef signed short int          	S16;
typedef signed char        			S8;

typedef volatile unsigned long*    PU32;
typedef volatile unsigned short*   PU16;
typedef volatile unsigned char*    PU8;
typedef volatile void*    PVOID;


typedef   U8    byte;
typedef   PU8   Pbyte;
typedef   PU16  PWord;
typedef   PU32  PDWord;

/**
 * Definição da estrutura Data 
 **/
typedef struct _date{
  U16    year; 
  U8     month;
  U8     day;  
}DATE;
/**
 * Definição da estrutura Hora 
 **/
typedef struct _time{
  U8     hour;
  U8     minute;
  U8     second;  
}TIME;

enum boolean {false,true};
typedef enum boolean Bool ;

/**
 * Definição da estrutura Data/Hora 
 **/
typedef struct _datetime{
  DATE date;
  TIME time;
}DATE_TIME;

struct _percurso;
typedef struct _percurso  Percurso;

typedef struct percurso_methods{
  const void (*resetValues)        (Percurso* this);
	const void (*addStopTime)        (Percurso* this ,U32 time);
	const void (*addSpentTime)       (Percurso* this ,U32 time);
	const void (*updateDistance)     (Percurso* this ,U16 distance);
	const void (*updateAverageSpeed) (Percurso* this);
	const void (*setCurrentSpeed)    (Percurso* this, U8 speed);
	const void (*updateSpeed)        (Percurso* this, U32* tickTime, U32* tickCount);
	const void (*start)              (Percurso* this, U32 tickTime,  U32 tickCount);
}Percurso_Methods;


/**
 * Definição da estrutura Percurso 
 **/
typedef struct _percurso{
  const Percurso_Methods* vptr;
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
}*pPercurso;

/**
 * Enumerado com as teclas válidas para serem utilizadas no contexto dos Menu 
 **/
enum KEYBOARD_KEYS{
  MENU    = 0x7E,
  OK      = 0x7D,
  CANCEL  = 0x7B,
  RESET   = 0x77,
  UP      = 0xDB,
  DOWN    = 0xD7,
  LEFT    = 0xE7,
  RIGHT   = 0xB7,
  ACCEL5  = 0xEE,
  ACCEL1  = 0xDE,
  BRAKE5  = 0xED,
  BRAKE1  = 0xDD,
  START   = 0xBE,
  STOP    = 0xBD
};

typedef enum KEYBOARD_KEYS KB_Key;

/**
 * Definição da estrura Option 
 **/
typedef struct _option{
  Pbyte text;
  void (*function) (PVOID percurso);
}Option,pOption;

/**
 * Definição do enumerado com os estados válidos
 * */
typedef enum _status {MAIN=0,OK_PRESS,MENU_PRESS,RESET_PRESS,FULLRESET,READ,WRITE,WAIT} Status;
#endif
