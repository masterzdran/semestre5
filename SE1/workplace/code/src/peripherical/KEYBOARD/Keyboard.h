#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "TYPES.h"
#include "GPIO.h"
#include "TIMER.h"

/**
 * Macros com as Mascaras referentes ao KB
 * */
#define   __KEYBOARD_ALL_MASK__                 ((U16)0x0FF0)
#define   __KEYBOARD_MASK__                     ((U8)0xF)
#define   __DEFAULT_VALUE__                     ((U8)0xF)
#define   __KEYBOARD_PORT_LOW_NIBBLE_SHIFT_MASK__     ((U8) 0x4)
#define   __KEYBOARD_PORT_HIGH_NIBBLE_SHIFT_MASK__    ((U8) 0x8)
#define   __KEYBOARD_LOW_PORT_MASK__            (__KEYBOARD_MASK__ << __KEYBOARD_PORT_LOW_NIBBLE_SHIFT_MASK__ )
#define   __KEYBOARD_HIGH_PORT_MASK__           (__KEYBOARD_MASK__ << __KEYBOARD_PORT_HIGH_NIBBLE_SHIFT_MASK__ )
#define   __NO_KEY__                            ((U8) 0xFF)
#define   NO_KEY                                ((U8) 0xFF)

/**
 * Assinatura das funções públicas 
 **/
void clearKey();
U8 getPreviousKey();
U8 getKey();
U8 hasKey();
U8 getPreviousBitMap();
U8 getBitMap();
U8 decodeKey(U8 keyBitmap);
void readKey();
void keyboard_init(pLPC_TIMER timer);
void kbTest();
#endif
