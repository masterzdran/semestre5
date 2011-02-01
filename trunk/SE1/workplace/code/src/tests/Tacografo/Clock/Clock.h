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

#define IS_LEAP_YEAR (year)       ((year % 400) == 0  ||  (year % 100) == 0 || (year % 4) == 0)
// | Y | Y | Y | Y | - | M | M | - | D | D |   | H | H | : | M | M |
// | 00| 01| 02| 03| 04| 05| 06| 07| 08| 09| 10| 11| 12| 13| 14| 15|

void setClock(PVOID course);


#endif
