#ifndef LCD_H
#define LCD_H
#include "TYPES.h"
#include "GPIO.h"
#include "TIMER.h"

// ****************** Mascaras Controlo******************
#define  CLEAR_MASK             0x01    //Clear do Display
#define  ENTRY_SET_MASK         0x06    //Clear do Display
#define  RETURN_HOME_MASK       0x02    //Set Position 0 on AC(address Counter)
#define  CURSOR_ON_MASK         0x0A    //Cursor Activo
#define  CURSOR_OFF_MASK        0x0B    //Cursor InActivo
#define  DISPLAY_ON_MASK        0x0E    //Display Activo
#define  DISPLAY_OFF_MASK       0x08    //Display InActivo
#define  BLINK_ON_MASK          0x09    //Blink Activo
#define  BLINK_OFF_MASK         0x08    //Blink InActivo
#define  SHIFT_MASK             0x04    //Move Cursor e Shifta Conteudo (1 nibbles)
#define  ADDR_COUNTER_MASK      0x80    //Move Cursor para a Posição
#define  DISPLAY_SIZE_MASK      16      //Tamanho do Display
#define  VALUE_MASK             0x0F    //Mascara para os Valores a serem escritos
#define  MAXTIMERISE            350;    // in miliseconds
#define  MAXTIMEFALL            400;    // in miliseconds

void LCD_init(pLPC_TIMER timer);
void LCD_write(U32  byte);
void clearLine(U8 line) ;
void posCursor(U8 line, U8 col) ;
void setCursor(U8 visible, U8 blinking);
void writeChar(U8 c) ;
void writeString(Pbyte txt);
void writeLine(U8 line, Pbyte txt);
inline void setCenter(U8 value) ;

#endif
