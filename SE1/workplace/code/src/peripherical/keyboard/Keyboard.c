#include "Keyboard.h"
//bitmaps
static U8 previous_key;
static U8 key;

static pLPC_TIMER ptimer;

/**
 * Initialization of the keyboard
 * No GPIO port's are defined yet, since the keyboard read may not be done yet.
 * 
 * */
void keyboard_init(pLPC_TIMER timer){
    //gpio_set_direction(__KEYBOARD_LOW_PORT_MASK__, GPIO_OUT); // define output 0x00F0
    //gpio_set_direction(__KEYBOARD_HIGH_PORT_MASK__, GPIO_IN); 
    previous_key = key =   __DEFAULT_VALUE__; //define default value 0xF
    ptimer = timer;
}

static U8 readNibble(U8 inputMask, U8 outputMask){
  U8 nibble;
 
  //Resistencias de Pull-Up
  gpio_set_direction(outputMask, GPIO_OUT);   // define output 0x00F0
  gpio_set_direction(inputMask, GPIO_IN);     // define output 0x0F00
  gpio_clear(outputMask);                      // 'Injecta' Zeros
  
  nibble = gpio_read(inputMask);
  timer_sleep_miliseconds(ptimer,10);         //Bounce
  
  return (nibble = gpio_read(inputMask));     //Há Tecla Pressionada!?  
}

/**
 * This funcion tries to read a key.
 * If no key is pressed or an error occurred while attempting to read the
 * keyboard, no valid value is affect. This means that call of the function
 * hasKey() will return the NO_KEY (0xFF)value.
 * */
void readKey(){
  U8 lowByteKey, highByteKey;
  U8 recentKey;

  //Read Lines
  lowByteKey = readNibble(__KEYBOARD_HIGH_PORT_MASK__,__KEYBOARD_LOW_PORT_MASK__ );
  if (lowByteKey  == __DEFAULT_VALUE__ ){       //There is an key pressed!?
    key = __NO_KEY__;  
    return;
  }

  //Read Columns
  highByteKey = readNibble(__KEYBOARD_LOW_PORT_MASK__,__KEYBOARD_HIGH_PORT_MASK__);
  if (highByteKey == __DEFAULT_VALUE__){       //Something went wrong, value discarted
    key = __NO_KEY__;
    return; 
  }

  recentKey = (highByteKey<<__KEYBOARD_PORT_LOW_NIBBLE_SHIFT_MASK__) | lowByteKey;
  
  if (recentKey != key)  key  = recentKey;    //Save the bitmap
  
  do{
    timer_sleep_miliseconds(ptimer,50);      //wait until the key is released
  }while((readNibble(__KEYBOARD_HIGH_PORT_MASK__,__KEYBOARD_LOW_PORT_MASK__ )) != __DEFAULT_VALUE__ );
  
}
/**
 * Check if it is an valid key stored from an previous call to read.
 * returns 0 if there is no Key, otherwise if there is.
 * */
U8 hasKey(){ return (key == __NO_KEY__); }

/**
 * Return the key read in the last call of readKey.
 * Should be a previous call to hasKey for best practice.
 * 
 * Returns the key read or NO_KEY if else
 * */
U8 getKey(){
  U8 keyBitMap = key;
  if (key == __NO_KEY__)  return __NO_KEY__;
  previous_key = key;
  key = __NO_KEY__;
  return decodeKey(keyBitMap);  
}
/**
 * Returns the previous key pressed ou NO_KEY if else 
 * */
U8 getPreviousKey(){ 
  if (previous_key == __NO_KEY__)  return __NO_KEY__;
  return decodeKey(previous_key);
}


/**
 * Decode the bitmap to an valid key.
 * If simultaneos keys were pressed, returns the last valid combination
 * */
static U8 decodeKey(U8 keyBitmap){
    register U8 colCount=0,lineCount=0;
    register U8 nibble;
    
    nibble = keyBitmap & __KEYBOARD_MASK__;
    for (;nibble;colCount++)
      nibble = nibble >> 1 ;
    
    nibble = (keyBitmap >> __KEYBOARD_PORT_LOW_NIBBLE_SHIFT_MASK__) & __KEYBOARD_MASK__;
    for (;nibble;lineCount++)
      nibble = nibble >> 1 ; 
      
    colCount--;lineCount--;
    return (lineCount << 2) | colCount;
}
/**
 * Clears the values of both stored keys
 * */
void clearKey(){previous_key = key = __NO_KEY__;}

