#include "Keyboard.h"
#include "TYPES.h"
#include "LCD.h"
#include "WATCHDOG.h"
/**
 * ************************
 0 *    *    *     * MENU *
 * ************************
 1 *    *    *     *  OK  *
 * ************************
 2 *    * UP *     *CANCEL*
 * ************************
 3 *LEFT*DOWN*RIGHT* RESET*
 * ************************
 * *  0 *  1 *  2  *   3  *
 * ************************
 
 LOW_NIBBLE =  LINES
 HIGH_NIBBLE = COLUMNS
 
 BITMAP = HIGH_NIBLLE | LOW_NIBBLE
 
 MENU   = 0111 1110 = 0x7E 
 OK     = 0111 1101 = 0x7D
 CANCEL = 0111 1011 = 0x7B
 RESET  = 0111 0111 = 0x77
 ------------------
 UP     = 1101 1011 = 0xDB
 DOWN   = 1101 0111 = 0xD7
 LEFT   = 1110 0111 = 0xE7
 WRITE  = 1011 0111 = 0xB7
*/
/*--------------------------------------------------------------------*/
 
void resetTotal(pPercurso percurso){
    percurso->totalDistance = 0;
    percurso->totalTime =0;
    printToLCD("Total Time and","Distance reseted");
}

//Time Limits
#define HOUR_LIMIT   24
#define MINUTE_LIMIT 60
#define SECOND_LIMIT 60
#define MONTH_LIMIT  12
#define LEAP_YEAR_FEB 29
#define NON_LEAP_YEAR_FEB 28
#define NBR_FIELDS    5
#define DEFAULT_LINE_SET 1






}
 




