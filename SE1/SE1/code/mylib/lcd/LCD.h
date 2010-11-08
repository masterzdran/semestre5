#ifndef LCD_H
#define LCD_H

#define  RS_MASK                0x40    //PIN 4
#define  ENABLE_MASK            0x80    //PIN 8
#define  DATA_MASK              0x0F    //PIN 11-14, DB4-7
#define  NIBBLE_SHIFT_MASK      4       //N. Bits a serem deslocados
// ****************** Mascaras Controlo******************
#define  CLEAR_MASK             0x01    //Clear do Display
#define  ENTRY_SET_MASK         0x06    //Clear do Display
#define  RETURN_HOME_MASK       0x02    //Set Position 0 on AC(address Counter)
#define  CURSOR_ON_MASK         0x0A    //Cursor Activo
#define  CURSOR_OFF_MASK        0x0B    //Cursor InActivo
#define  DISPLAY_ON_MASK        0x0C    //Display Activo
#define  DISPLAY_OFF_MASK       0x08    //Display InActivo
#define  BLINK_ON_MASK          0x09    //Blink Activo
#define  BLINK_OFF_MASK         0x08    //Blink InActivo
#define  SHIFT_MASK             0x04    //Move Cursor e Shifta Conteudo (2 nibbles)
#define  ADDR_COUNTER_MASK      0x80    //Move Cursor para a Posição
#define  DISPLAY_SIZE_MASK      16      //Tamanho do Display
#define  VALUE_MASK             0x0F    //Mascara para os Valores a serem escritos
#define  MAXTIMERISE            350;    // in miliseconds
#define  MAXTIMEFALL            400;    // in miliseconds



#endif
