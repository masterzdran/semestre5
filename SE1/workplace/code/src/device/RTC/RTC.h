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
#ifndef RTC_H
#define RTC_H
#include "TYPES.h"
#define     pRTC      (((pLPC_RTC) 0xE0024000))

typedef struct _RTC{
                      //SIZE|Description                  |Address
    U8     ILR;       //  02|Interrupt Location Register  |0xE002 4000
    U8     DUMMY01;
    U16    DUMMY02;
    /*----------------------------------------------------------------*/
    U16    CTC;       //  15|Clock Tick Counter           |0xE002 4004
    U16    DUMMY03;
    /*----------------------------------------------------------------*/
    U8     CCR;       //  04|Clock Control Register       |0xE002 4008
    U8     DUMMY04;
    U16    DUMMY05;
    /*----------------------------------------------------------------*/
    U8     CIIR;      //  08|Counter Increment Interrupt Register|0xE002 400C
    U8     DUMMY06;
    U16    DUMMY07;
    /*----------------------------------------------------------------*/
    U8     AMR;       //  08|Alarm Mask Register          |0xE002 4010
    U8     DUMMY08;
    U16    DUMMY09;
    /*----------------------------------------------------------------*/
    U32    CTIME0;    //  32|Consolidated Time Register 0 |0xE002 4014
    U32    CTIME1;    //  32|Consolidated Time Register 1 |0xE002 4018
    U32    CTIME2;    //  32|Consolidated Time Register 2 |0xE002 401C
    /*----------------------------------------------------------------*/
    U8     SEC;       //  06|Seconds Counter              |0xE002 4020
    U8     DUMMY10;
    U16    DUMMY11;
    /*----------------------------------------------------------------*/
    U8     MIN;       //  06|Minutes Register             |0xE002 4024
    U8     DUMMY12;
    U16    DUMMY13;
    /*----------------------------------------------------------------*/
    U8     HOUR;      //  05|Hours Register               |0xE002 4028
    U8     DUMMY14;
    U16    DUMMY15;
    /*----------------------------------------------------------------*/
    U8     DOM;       //  05|Day of Month Register        |0xE002 402C
    U8     DUMMY16;
    U16    DUMMY17;
    /*----------------------------------------------------------------*/
    U8     DOW;       //  03|Day of Week Register         |0xE002 4030
    U8     DUMMY18;
    U16    DUMMY19;
    /*----------------------------------------------------------------*/
    U16    DOY;       //  09|Day of Year Register         |0xE002 4034
    U16    DUMMY20;
    /*----------------------------------------------------------------*/
    U8     MONTH;     //  04|Months Register              |0xE002 4038
    U8     DUMMY21;
    U16    DUMMY22;
    /*----------------------------------------------------------------*/
    U16    YEAR;      //  12|Years Register               |0xE002 403C
    U16    DUMMY23;  
	/*----------------------------------------------------------------*/
	U32	   DUMMY24;   //								  |0xE002 4040
	U32	   DUMMY25;   //								  |0xE002 4044
	U32	   DUMMY26;   //								  |0xE002 4048
	U32	   DUMMY27;   //								  |0xE002 404C
	U32	   DUMMY28;   //								  |0xE002 4050
	U32	   DUMMY29;   //								  |0xE002 4054
	U32	   DUMMY30;   //								  |0xE002 4058
	U32	   DUMMY31;   //								  |0xE002 405C
    /*----------------------------------------------------------------*/
    U8     ALSEC;     //  06|Alarm value for Seconds      |0xE002 4060
    U8     DUMMY32;
    U16    DUMMY33;
    /*----------------------------------------------------------------*/    
    U8     ALMIN;     //  06|Alarm value for Minutes     |0xE002 4064
    U8     DUMMY34;
    U16    DUMMY35;
    /*----------------------------------------------------------------*/
    U8     ALHOUR;    //  05|Alarm value for Hours       |0xE002 4068
    U8     DUMMY36;
    U16    DUMMY37;
    /*----------------------------------------------------------------*/
    U8     ALDOM;     //  05|Alarm value for Day of Month|0xE002 406C
    U8     DUMMY38;
    U16    DUMMY39;
    /*----------------------------------------------------------------*/
    U8     ALDOW;     //  03|Alarm value for Day of Week |0xE002 4070
    U8     DUMMY40;
    U16    DUMMY41;
    /*----------------------------------------------------------------*/
    U16    ALDOY;     //  09|Alarm value for Day of Year |0xE002 4074
    U16    DUMMY42;
    /*----------------------------------------------------------------*/
    U8     ALMON;     //  04|Alarm value for Months      |0xE002 4078
    U8     DUMMY43;
    U16    DUMMY44;
    /*----------------------------------------------------------------*/
    U16    ALYEAR;    //  12|Alarm value for Year        |0xE002 407C
    U16    DUMMY45;
    /*----------------------------------------------------------------*/
    U16    PREINT;    //  13|Prescaler value, integer portion|0xE002 4080
    U16    DUMMY46;
    /*----------------------------------------------------------------*/
    U16    PREFRAC;   //  15|Prescaler value, integer portion|0xE002 4084
    U16    DUMMY47;
    /*----------------------------------------------------------------*/
}LPC_RTC,*pLPC_RTC;



#define PCRTC     0x200
#define __ILR_RTCCIF_DISABLE__     0x0
#define __ILR_RTCCIF_CLEAR__       0x1
#define __ILR_RTCALF_DISABLE__     0x0
#define __ILR_RTCALF_CLEAR__       0x2
#define __CCR_CLKEN_DISABLE__      0x0
#define __CCR_CLKEN_ENABLE__       0x1
#define __CCR_CTCRST_ENABLE__      0x2
#define __CCR_CTCRST_DISABLE__     0x0
#define __CCR_CTTEST__             0x3

#define LPC_PREINT      ((__SYSTEM_CLOCK__ / 32768) - 1)
#define LPC_PREFRAC     (__SYSTEM_CLOCK__ - (((__SYSTEM_CLOCK__ / 32768) - 1) + 1) * 32768)


#define __CIIR_IMSEC__          ((U8) 0x1   )
#define __CIIR_IMMIN__          ((U8) 0x1<<1)
#define __CIIR_IMHOUR__         ((U8) 0x1<<2)
#define __CIIR_IMDOM__          ((U8) 0x1<<3)
#define __CIIR_IMDOW__          ((U8) 0x1<<4)
#define __CIIR_IMDOY__          ((U8) 0x1<<5)
#define __CIIR_IMMON__          ((U8) 0x1<<6)
#define __CIIR_IMYEAR__         ((U8) 0x1<<7)

#define __CIIR_MASK__           ((U8) 0xF)

#define __AMRSEC__          0x1<<0
#define __AMRMIN__          0x1<<1
#define __AMRHOUR__         0x1<<2
#define __AMRDOM__          0x1<<3
#define __AMRDOW__          0x1<<4
#define __AMRDOY__          0x1<<5
#define __AMRMON__          0x1<<6
#define __AMRYEAR__         0x1<<7

void rtc_init();
void rtc_initCalendar();
void rtc_setDate(U16 year,U8 month, U8 day);
void rtc_setTime(U8 hour,U8 minute, U8 seconds);
void rtc_setDOW(U8 dow);
void rtc_setDOY(U16 doy);
void rtc_getDate(DATE* date);
void rtc_getTime(TIME* time);
void rtc_setDateTime(DATE_TIME* datetime);
void rtc_getDateTime(DATE_TIME* datetime);

#define rtc_setDom(A)	  	((pRTC->DOM) = A & __DAY_MASK__)
#define rtc_setMonth(A)		((pRTC->MONTH) = A & __MONTH_MASK__)
#define rtc_setYear(A)		((pRTC->YEAR) = A & __YEAR_MASK__)
#define rtc_setHour(A)		((pRTC->HOUR) = A & __HOUR_MASK__)
#define rtc_setMin(A)	  	((pRTC->MIN) = A & __MINUTE_MASK__)
#define rtc_setSec(A)	  	((pRTC->SEC) = A & __SECOND_MASK__)
#define rtc_getDom()	  	((pRTC->CTIME1     )  & __DAY_MASK__)
#define rtc_getMonth()		((pRTC->CTIME1 >> 8)  & __MONTH_MASK__)
#define rtc_getYear()	  	((pRTC->CTIME1>> 16)  & __YEAR_MASK__)
#define rtc_getHour()   	((pRTC->CTIME0 >> 16) & __HOUR_MASK__)
#define rtc_getMin()	  	((pRTC->CTIME0 >> 8)  & __MINUTE_MASK__)
#define rtc_getSec()	  	(pRTC->CTIME0 & __SECOND_MASK__)

#define __YEAR_MASK__       0xFFF
#define __MONTH_MASK__      0xF
#define __DAY_MASK__        0x1F
#define __HOUR_MASK__       0x1F
#define __MINUTE_MASK__     0x3F
#define __SECOND_MASK__     0x3F
#define __DOW_MASK__        0x7
#define __DOY_MASK__        0x1FF
#define __DEFAULT_YEAR__    2010
#define __DEFAULT_MONTH__   01
#define __DEFAULT_DAY__     01
#define __DEFAULT_HOUR__    00
#define __DEFAULT_MINUTE__  00
#define __DEFAULT_SECOND__  00
#define __DEFAULT_DOY__     01
#define __DEFAULT_DOW__     05


#endif
