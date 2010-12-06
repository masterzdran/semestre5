#include "LCD.h"
#include "TIMER.h"
#include "GPIO.h"


/* 
 * 
 * |     |     |P0.13|P0.12|P0.11|P0.10|P0.09|
 * | R/!W| EN  | RS  | DB7 | DB6 | DB5 | DB4 |
 * 
 * */
#define DATA_BITS_SHIFT          4
#define CLEAN_MASK               0xF
#define RS_MASK                  0x010  //Ultimo nibble para Data
#define ENABLE_MASK              0x020  //Ultimo nibble para Data
#define RW_MASK                  0x040  //Ultimo nibble para Data

#define DATA_MASK                0x0F0
#define LCD_GPIO_SHIFT           8
#define LCD_GPIO                 0x7F0    


static unsigned char value = 0;
static 

void LCD_init(){
    //Pag51: Table 6. Interface Data Length : Four bits
    /* Begin inicialization */
    
    processValue(0,ENABLE_MASK|RS_MASK|DATA_MASK)
    timer_sleep_miliseconds(TIMER,46);          //Wait for 45 ms or more after VDD
    processValue(0,0x03);    
    timer_sleep_miliseconds(TIMER,5);           //Wait for 4,1 ms or more
    processValue(0,0x03);    
    timer_sleep_microseconds(TIMER,110);           //Wait for 100 μs or more
    processValue(0,0x03);    

    processValue(0,0x02);    //Functon set (interface data length : 4 bits)
    processValue(0,0x28);    //Function Set (0x28) -> Set Duty
    processValue(0,0x08);    //Display OFF (0x08)
    processValue(0,0x01);    //Display Clear (0x01)
    processValue(0,0x07);    //Entry Mode Set (0x07) -> Set Increment, Display shift
    
    /* Entry Mode Set */
    processValue(0,ENTRY_SET_MASK);      //Entry Mode 
    
    /* Activate the Display */
    processValue(0,DISPLAY_ON_MASK);    //Display  
    processValue(0,CURSOR_ON_MASK);    //Cursor
}


void LCD_write(char byte){
  gpio_write(LCD_GPIO,(byte<<LCD_GPIO_SHIFT)&&LCD_GPIO);
}

static void processValue(unsigned char rs, unsigned char value){
  LCD_write((rs | ((byte >> DATA_BITS_SHIFT)&CLEAN_MASK));
  LCD_write((rs | (byte & CLEAN_MASK));
}

/**
 * Activa o modo de entrada de dados
 */
void entryModeSet() {processValue(0,ENTRY_SET_MASK);}
  
/**
 * Activa o mostrador
 */
void displayControlOn() {processValue(0,DISPLAY_ON_MASK | CURSOR_ON_MASK);}
/**
 * Desactiva o mostrador
 */
void displayControlOff() {processValue(0,DISPLAY_OFF_MASK);}
/**
 * Desactiva o Blik
 */
void blinkOff() {processValue(0,DISPLAY_ON_MASK | BLINK_OFF_MASK);}

/**
 * Apaga todos os caracteres do display
 * */
void clear() {processValue(0,LicConstants.CLEAR_MASK);}
/**
 * Apaga todos os caracteres de uma linha
 * */
void clearLine(unsigned char line) {
  posCursor(line, 0);
  for (int i = 0; i < 40; i++)
    writeChar(' ');
  posCursor(line, 0);
}

/**
 * 
 *  Posiciona o cursor na linha (0..1) e coluna (0..15) indicadas
 */
void posCursor(unsigned char line, unsigned char col) { processValue(0,LicConstants.ADDR_COUNTER_MASK | (0x40 * line + col));}

/**
 * 
 * Acerta o tipo de cursor: Visivel ou invisivel; A piscar ou
 * constante
 * 
 * Cursor/Blink Control Circuit The cursor/blink control circuit
 * generates the cursor or character blinking. The cursor or the
 * blinking will appear with the digit located at the display
 * data RAM (DDRAM) address set in the address counter (AC).
 */
void setCursor(unsigned char visible, unsigned char blinking) {
  processValue(0,(char) (visible ? CURSOR_ON_MASK | (blinking ? BLINK_ON_MASK : BLINK_OFF_MASK):(CURSOR_OFF_MASK | (blinking ? BLINK_ON_MASK : BLINK_OFF_MASK))));
}

/**
 * 
 * Escreve o caracter indicado no local do cursor e o cursor
 * avança para a proxima coluna
 */
void writeChar(char c) {processValue(1,c);}

/**
 * 
 * Escreve o texto indicado no local do cursor e o cursor avança
 * para a coluna seguinte
 */
void writeString(char* txt) {
  while(*txt){
      processValue(1,*txt);
      txt++;
  }
}

/**
 * Escreve o texto indicado na linha indicada (0 ou 1). O resto
 * da linha é texto fica centrado ou alinhado à
 * esquerda,dependendo da última chamada a SetCenter()
 */
void writeLine(unsigned char line, char* txt,) {
  int length = 0;
  char* txttmp= txt;
  if (isCentered){
    for(;*txttmp;txttmp++, length++); 
    length =  (DISPLAY_SIZE_MASK - length) / 2;
  }
  posCursor(line, (length);
  writeString(txt);
}

/**
 * Indica se o texto escrito com writeLine() nas chamadas
 * seguintes deve ou não ficar centrado na linha
 */
void setCenter(unsigned char value) {isCentered = value;}

/**
 * Recebe uma string e o numero de caracteres a recuar e calcula
 * onde vai escrever.
 * x=Total de Caracteres do LCD (16) y=Total de Caracteres da String
 * se centrado pos=(x - y)/2 + (y - b) = (x - y + 2y - 2b)/2 = (x +
 * y -2b)/2 se não centrado pos= y - b
 */
int getPos(char* txt, unsigned char b) {
  char* txttmp= txt;
  int length = 0;
  for(;*txttmp;txttmp++, length++); 
  return (isCentered) ? (DISPLAY_SIZE_MASK + length - 2 * b) / 2 : (length - 3);
}




