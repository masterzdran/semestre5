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
#include "LCD.h"
/* 
 * 
 * |     |P0.07|P0.06|P0.15|P0.14|P0.13|P0.12|
 * | R/!W| EN  | RS  | DB7 | DB6 | DB5 | DB4 |
 * 
 * */
#define DATA_BITS_SHIFT          ((U8)0x4)
#define CLEAN_MASK               ((U8)0xF)
#define RS_MASK                  ((U16)0x0040)  //Ultimo nibble para Data
#define ENABLE_MASK              ((U16)0x0080)  //Ultimo nibble para Data
#define RW_MASK                  ((U16)0x0000)  //Ultimo nibble para Data

#define DATA_MASK                ((U16)0xF000)
#define LCD_GPIO_MASK_SHIFT      ((U8) 0xC)
#define LCD_GPIO_MASK            ((U16)0xF0C0)



U8 value = 0;
U8 isCentered = 0;
pLPC_TIMER ptimer;
/**
 * Função para contar o comprimento da string
 * */
inline U32 Wstrlen(const Pbyte str){
  register Pbyte p;
	for (p=str ; *p ; p++);
	return p - str;
}

inline static void LCD_resetOutputValue(){
  gpio_clear(ENABLE_MASK);
  gpio_set_direction(DATA_MASK, GPIO_OUT);
  gpio_set(DATA_MASK);  
}
/**
 * Escreve no LCD
 * */
static void LCD_write(U32  byte){
  gpio_write(DATA_MASK,(byte<<LCD_GPIO_MASK_SHIFT)&DATA_MASK);
}

/**
 * Escreve um nibble 
 **/
static void processValue_nibble(U8 rs, U8 value){
  gpio_set_direction(LCD_GPIO_MASK, GPIO_OUT);
  gpio_set(ENABLE_MASK);
  if (rs)
	gpio_set(RS_MASK);
  else
	gpio_clear(RS_MASK);
  LCD_write( value );
  timer_sleep_miliseconds(ptimer,2);
  gpio_clear(ENABLE_MASK);
}
/**
 * Processa o byte
 * */
static void processValue(U8 rs, U8 value){
  processValue_nibble(rs,(((value) >> DATA_BITS_SHIFT)&CLEAN_MASK));
  timer_sleep_miliseconds(ptimer,20);
  processValue_nibble(rs,value&CLEAN_MASK);
}  
/**
 * Inicialização do LCD
 * */
void LCD_init(pLPC_TIMER timer){
    //Pag51: Table 6. Interface Data Length : Four bits
    /* Begin inicialization */

    ptimer=timer;
    gpio_init_PINSEL0(__PINSEL0_GPIO_PORT_0_11__|__PINSEL0_GPIO_PORT_0_10__|__PINSEL0_GPIO_PORT_0_9__|__PINSEL0_GPIO_PORT_0_8__|__PINSEL0_GPIO_PORT_0_7__|__PINSEL0_GPIO_PORT_0_6__);
    gpio_set_direction(LCD_GPIO_MASK,GPIO_OUT);
    gpio_clear(RS_MASK);
    gpio_clear(ENABLE_MASK);
  
  
    timer_sleep_miliseconds(timer,46);          //Wait for 45 ms or more after VDD
    processValue_nibble(0,0x3);    
    timer_sleep_miliseconds(timer,5);           //Wait for 4,1 ms or more
    processValue_nibble(0,0x3);    
    timer_sleep_microseconds(timer,110);           //Wait for 100 μs or more
    processValue_nibble(0,0x3);    

    processValue_nibble(0,0x2);    //Functon set (interface data length : 4 bits)

    timer_sleep_miliseconds(timer,5);
    
    processValue(0,0x28);    //Function Set (0x28) -> Set Duty
    processValue(0,0x08);    //Display OFF (0x08)
    processValue(0,0x01);    //Display Clear (0x01)
    processValue(0,0x07);    //Entry Mode Set (0x07) -> Set Increment, Display shift
    
    /* Entry Mode Set */
    processValue(0,ENTRY_SET_MASK);      //Entry Mode 
    
    /* Activate the Display */
    processValue(0,DISPLAY_ON_MASK);    //Display  
    //processValue(0,CURSOR_ON_MASK);    //Cursor
}

/**
 * Activa o modo de entrada de dados
 */
void LCD_entryModeSet() {processValue(0,ENTRY_SET_MASK);}
  
/**
 * Activa o mostrador
 */
void LCD_displayControlOn() {processValue(0,DISPLAY_ON_MASK | CURSOR_ON_MASK);}
/**
 * Desactiva o mostrador
 */
void LCD_displayControlOff() {processValue(0,DISPLAY_OFF_MASK);}
/**
 * Desactiva o Blink
 */
void LCD_blinkOff() {processValue(0,DISPLAY_ON_MASK | BLINK_OFF_MASK);}

/**
 * Apaga todos os caracteres do display
 * */
void LCD_clear() {processValue(0,CLEAR_MASK);}
/**
 * Apaga todos os caracteres de uma linha
 * */
void LCD_clearLine(U8 line) {
  LCD_posCursor(line, 0);
  register U8 i=0;
  for (; i < 16; i++)
  LCD_writeChar(' ');
  LCD_posCursor(line, 0);
}

/**
 * 
 *  Posiciona o cursor na linha (0..1) e coluna (0..15) indicadas
 */
void LCD_posCursor(U8 line, U8 col) { processValue(0,ADDR_COUNTER_MASK | (LINE_ADDRESS * line + col));}

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
void LCD_setCursor(U8 visible, U8 blinking) {
  processValue(0,(char) (visible ? CURSOR_ON_MASK | (blinking ? BLINK_ON_MASK : BLINK_OFF_MASK):(CURSOR_OFF_MASK | (blinking ? BLINK_ON_MASK : BLINK_OFF_MASK))) | DISPLAY_ON_MASK);
}

/**
 * 
 * Escreve o caracter indicado no local do cursor e o cursor
 * avança para a proxima coluna
 */
void LCD_writeChar(U8 c) {processValue(1,c);}

/**
 * 
 * Escreve o texto indicado no local do cursor e o cursor avança
 * para a coluna seguinte
 */
void LCD_writeString(Pbyte txt) {
  gpio_set(RS_MASK);
  while(*txt){
      processValue(1,*txt);
      txt++;
  }
  //LCD_resetOutputValue();
}

/**
 * Escreve o texto indicado na linha indicada (0 ou 1). O resto
 * da linha é texto fica centrado ou alinhado à
 * esquerda,dependendo da última chamada a SetCenter()
 */
void LCD_writeLine(U8 line, Pbyte txt) {
  int length = Wstrlen(txt),i=0,idx;
  if (isCentered){
    idx =  (DISPLAY_SIZE_MASK - length) / 2;
  }else{
	idx=0;
  }
  LCD_posCursor(line,0);
  for(i=0;i<idx;++i)
	LCD_writeChar(' ');
//  LCD_clearLine(line);
  LCD_writeString(txt);
  for(i+=length;i<16;++i)
	LCD_writeChar(' ');
 
}

/**
 * Indica se o texto escrito com writeLine() nas chamadas
 * seguintes deve ou não ficar centrado na linha
 */
inline void LCD_setCenter(U8 value) {isCentered = value;}

/**
 * Recebe uma string e o numero de caracteres a recuar e calcula
 * onde vai escrever.
 * x=Total de Caracteres do LCD (16) y=Total de Caracteres da String
 * se centrado pos=(x - y)/2 + (y - b) = (x - y + 2y - 2b)/2 = (x +
 * y -2b)/2 se não centrado pos= y - b
 */
static int getPos(Pbyte txt, U8 b) {
  int length = Wstrlen(txt);
  return (isCentered) ? (DISPLAY_SIZE_MASK + length - 2 * b) / 2 : (length - 3);
}

