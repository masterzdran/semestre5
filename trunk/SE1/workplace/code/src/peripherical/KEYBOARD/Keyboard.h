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
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "TYPES.h"
#include "GPIO.h"
#include "TIMER.h"

/**
 * Macros com as Mascaras referentes ao KB
 * */
#define   __KEYBOARD_ALL_MASK__                 ((U16)0x3FC0)
#define   __KEYBOARD_MASK__                     ((U8)0xF)
#define   __DEFAULT_VALUE__                     ((U8)0xF)
#define   __KEYBOARD_PORT_LOW_NIBBLE_SHIFT_MASK__     ((U8) 0x6)
#define   __KEYBOARD_PORT_HIGH_NIBBLE_SHIFT_MASK__    ((U8) 0xA)
#define   __KEYBOARD_LOW_PORT_MASK__            (__KEYBOARD_MASK__ << __KEYBOARD_PORT_LOW_NIBBLE_SHIFT_MASK__ )
#define   __KEYBOARD_HIGH_PORT_MASK__           (__KEYBOARD_MASK__ << __KEYBOARD_PORT_HIGH_NIBBLE_SHIFT_MASK__ )
#define   __NO_KEY__                            ((U8) 0xFF)
#define   NO_KEY                                ((U8) 0xFF)

/**
 * Assinatura das funções públicas 
 **/
void keyboard_clearKey();
U8 keyboard_getPreviousKey();
U8 keyboard_getKey();
U8 keyboard_hasKey();
U8 keyboard_getPreviousBitMap();
U8 keyboard_getBitMap();
U8 keyboard_decodeKey(U8 keyBitmap);
void keyboard_readKey();
void keyboard_init(pLPC_TIMER timer);
void kbTest();
#endif
