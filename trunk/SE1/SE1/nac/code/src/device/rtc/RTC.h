#ifndef RTC_H
#define RTC_H

#define     pRTC      (((pLPC_RTC) 0xE0024000))

typedef struct _RTC{
    U32    ILR;
    U32    CTC;
    U32    CCR;
    U32    CIIR;
    U32    AMR;
    U32    CTIME0;
    U32    CTIME1;
    U32    CTIME2;
    U32    SEC;
    U32    MIN;
    U32    HOUR;
    U32    DOM;
    U32    DOW;
    U32    DOY;
    U32    MONTH;
    U16    YEAR;
    U16    DUMMY1;
    U32    ALSEC;
    U32    ALMIN;
    U32    ALHOUR;
    U32    ALDOM;
    U32    ALDOW;
    U32    ALDOY;
    U32    ALMON;
    U32    ALYEAR;
    U32    PREINT;
    U32    PREFRAC;
}LPC_RTC,*pLPC_RTC;



#define PCRTC     0x200
#define __ILR_RTCCIF_DISABLE__     0b00
#define __ILR_RTCCIF_CLEAR__       0b01
#define __ILR_RTCALF_DISABLE__     0b00
#define __ILR_RTCALF_CLEAR__       0b10
#define __CCR_CLKEN_DISABLE__      0b0000
#define __CCR_CLKEN_ENABLE__       0b0001
#define __CCR_CTCRST_ENABLE__      0b0010
#define __CCR_CTCRST_DISABLE__     0b0000
#define __CCR_CTTEST__             0b0011

#define LPC_PREINT      ((CCLK / 32768) - 1)
#define LPC_PREFRAC     (CCLK - (((CCLK / 32768) - 1) + 1) * 32768)


#define __CIIR_IMSEC__          0b00000001
#define __CIIR_IMMIN__          0b00000010
#define __CIIR_IMHOUR__         0b00000100
#define __CIIR_IMDOM__          0b00001000
#define __CIIR_IMDOW__          0b00010000
#define __CIIR_IMDOY__          0b00100000
#define __CIIR_IMMON__          0b01000000
#define __CIIR_IMYEAR__         0b10000000  

#define __AMRSEC__          0b00000001
#define __AMRMIN__          0b00000010
#define __AMRHOUR__         0b00000100
#define __AMRDOM__          0b00001000
#define __AMRDOW__          0b00010000
#define __AMRDOY__          0b00100000
#define __AMRMON__          0b01000000
#define __AMRYEAR__         0b10000000 

void rtc_init();
void rtc_initCalendar();
void rtc_setDate(U16 year,U8 month, U8 day);
void rtc_setTime(U8 hour,U8 minute, U8 seconds);
void rtc_setDOW(U8 dow);
void rtc_setDOY(U16 doy);

#endif
