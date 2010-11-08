.global _start

.data
GPIO_ADDR:      .word   0xE0028000   //Endereço do Porto GPIO

OUTPUT_MASK:     .word   0x000000F0  //Mascara de um porto I/O
INPUT_MASK:      .word   0x00000F00  //Mascara de um porto I/O


IOPIN:          .word   0xE0028000   //Definição do Endereço da IOPIN
IOSET:          .word   0xE0028004   //Definição do Endereço da IOSET
IODIR:          .word   0xE0028008   //Definição do Endereço da IODIR
IOCLR:          .word   0xE002800C   //Definição do Endereço da IOCLR



.text
/* int main() */
_start:

    str [IOCLR],0xFFFFFFFF      //Clear GPIO
    str [IODIR], OUTPUT_MASK     //Porto de Output



    /* END */
    b   .


/*Funtions*/
//void led_blink(int n)
led_blink:

