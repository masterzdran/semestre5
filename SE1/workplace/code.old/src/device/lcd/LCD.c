#include LCD.h

void LCD_init(){
    /*
     * display (D)
     * cursor (C)
     * blinking (B)
     * data length (DL)
     * duty (N)
     * fonts (F)
     * Display shift (S)
     * Increment/Decrement (I/D)
     */
    //Pag51: Table 6. Interface Data Length : Four bits
    /* Begin inicialization */
    sleep(50);          //Wait for 45 ms or more after VDD
    writebits(0x3);    
    sleep(5);           //Wait for 4,1 ms or more
    writebits(0x3);    
    sleep(1);           //Wait for 100 μs or more
    writebits(0x3);    

    writebits(0x2);    //Functon set (interface data length : 4 bits)
    writebits(0x2);    //Function Set (0x28) 
    writebits(0x8);    //Function Set (0x28) -> Set Duty
    writebits(0x0);    //Display OFF (0x08)
    writebits(0x8);    //Display OFF (0x08)
    writebits(0x0);    //Display Clear (0x01)
    writebits(0x1);    //Display Clear (0x01)
    writebits(0x0);    //Entry Mode Set (0x07)
    writebits(0x7);    //Entry Mode Set (0x07) -> Set Increment, Display shift
    
    /* Entry Mode Set */
    writebits(0x0);                 //Entry Mode Set (0x06)
    writebits(ENTRY_SET_MASK);      //Entry Mode Set (0x06) -> Set Increment
    
    /* Activate the Display */
    writebits(DISPLAY_ON_MASK);    //Entry Mode Set (0x06)
    writebits(CURSOR_ON_MASK);    //Entry Mode Set (0x06) -> Set Increment
}
