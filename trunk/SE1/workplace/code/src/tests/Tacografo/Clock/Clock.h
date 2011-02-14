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
#ifndef __CLOCK_H__
#define __CLOCK_H__
#include "TYPES.h"

//Time Limits
#define HOUR_LIMIT   24
#define MINUTE_LIMIT 60
#define SECOND_LIMIT 60
#define MONTH_LIMIT  12
#define LEAP_YEAR_FEB 29
#define NON_LEAP_YEAR_FEB 28
#define NBR_FIELDS    5
#define DEFAULT_LINE_SET 1

#define __FX(A,B,C)   ((A - 1 + B) % C + 1) //Because do not start at 0
#define __FX0(A,B,C)		(modulos(A,0,(S8)(B),C))
#define __FX1(A,B,C)		(modulos(A,1,(S8)(B),C))

#define IS_LEAP_YEAR(A)       (((A) % 400) == 0  ||  ((A) % 100) == 0 || ((A) % 4) == 0)
// | Y | Y | Y | Y | - | M | M | - | D | D |   | H | H | : | M | M |
// | 00| 01| 02| 03| 04| 05| 06| 07| 08| 09| 10| 11| 12| 13| 14| 15|

#define Clock_timeToSecond(A)	((A)->hour*60*60+(A)->minute*60+(A)->second)
#define Clock_timeSecToHour(A)((A)/secondsInDay)
#define Clock_timeSecToMin(A)	((A-((A/secondsInDay)*secondsInDay))/60)
#define Clock_timeSecToSec(A)	((A)%60)

void Clock_timeDif(TIME* time1, TIME* time2, TIME* time_res);
U16  Clock_dateDif(DATE* date_init, DATE* date_end);

void setClock(PVOID course);
U32  modulos(S32 value, U8 adj, S8 offset, U32 mod);


#endif
