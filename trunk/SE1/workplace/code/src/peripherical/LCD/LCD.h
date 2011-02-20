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
#define  CURSOR_OFF_MASK        0x08    //Cursor InActivo
#define  DISPLAY_ON_MASK        0x0C    //Display Activo
#define  DISPLAY_OFF_MASK       0x08    //Display InActivo
#define  BLINK_ON_MASK          0x09    //Blink Activo
#define  BLINK_OFF_MASK         0x08    //Blink InActivo
#define  SHIFT_MASK             0x04    //Move Cursor e Shifta Conteudo (1 nibbles)
#define  ADDR_COUNTER_MASK      0x80    //Move Cursor para a Posição
#define  DISPLAY_SIZE_MASK      16      //Tamanho do Display
#define  VALUE_MASK             0x0F    //Mascara para os Valores a serem escritos
#define  MAXTIMERISE            350     // in miliseconds
#define  MAXTIMEFALL            400     // in miliseconds
#define  LINE_ADDRESS			0x40    //endereço da 2ª linha


void LCD_init(pLPC_TIMER timer);
void LCD_clearLine(U8 line) ;
void LCD_posCursor(U8 line, U8 col) ;
void LCD_setCursor(U8 visible, U8 blinking);
void LCD_writeChar(U8 c) ;
void LCD_writeString(Pbyte txt);
void LCD_writeLine(U8 line, Pbyte txt);
inline void LCD_setCenter(U8 value);


#endif
