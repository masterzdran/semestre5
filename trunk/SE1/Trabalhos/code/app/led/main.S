
.global _start



.text

	/*Register address declaration*/

	PINSEL0  =	0xE002C000
	PINSEL1  =	0xE002C004

	IOPIN	 =	0xE0028000
	IOSET	 =	0xE0028004
	IODIR	 =	0xE0028008
	IOCLR	 =	0xE002800C
	
	COL_MASK =	0x00000F00
	ROW_MASK =	0x000000F0
	LED_MASK =	0x00001000


KEYBOARD_READ:
	/* PIN Function Selection Register */
	LDR R1, =PINSEL0
	EOR R2, R2, R2
	STR R2, [R1]
	LDR R4, =COL_MASK
	LDR R5, =ROW_MASK
	
	/* PIN Direction Control Register */
	/* 0-INPUT 1-OUTPUT */


	/*Set Output to Column*/
    LDR R1, =IODIR
    STR R4, [R1] 
	
	/*Set column to 1*/
	LDR R1, =IOSET
	STR R4,[R1]
	
READ_LINE:
	/*Read row status*/
	LDR R1, =IOPIN
	LDR R2, [R1]

	/* R2 tem leitura de pins input - line*/
	ANDS R2, R2, R5
	CMP R2, R5
	/***** jump para sleep antes de tentar novamente*****/
	BEQ READ_LINE
	
	/*Clear Col Output*/
	LDR R1, =IOCLR
    STR R4, [R1]
	
	/*Set Output to Row*/
    LDR R1, =IODIR
    STR R5, [R1]
	
	/*Set row to 1*/
	LDR R1, =IOSET
	STR R5, [R1]
	
READ_COLUMN:
	/*Read col status*/
	LDR R1, =IOPIN
	LDR R3, [R1]

	/* R3 tem leitura de pins input - row*/
	AND R3, R3, R4

	/* R2 tem valor linha e R3 valor coluna*/
	EOR R2, R2, R5
	EOR R3, R3, R4

	MOV R2, R2, LSR #4
	MOV R1, R3, LSR #8
	MOV R0,#0
	MOV R1,#0
W1:
	CMP R2, #0
	BEQ W2
	ADD R0, R0, #1
	MOV R2, R2, LSR #1
	B W1
W2:
	CMP R3, #0
	BEQ CONT
	ADD R1, R1, #1
	MOV R3, R3, LSR #1
	B W2
CONT:
	MOV R0, R0, LSL #2
	ORR R0, R0, R1
	MOV PC, LR
	
/*	
COUNT:
	MOV R0,#0
W:
	CMP R1, #0
	MOVEQ PC, LR
	ADD R0, R0, #1
	MOV R1, R1, LSR #1
	B W
*/

LED_BLINK:

	/* PIN Function Selection Register */
	LDR R1, =PINSEL0
	EOR R2, R2, R2
	STR R2, [R1]

	/*Liga Led*/
    LDR R1, =IODIR
	LDR R2, =LED_MASK
    STR R2, [R1]
BLINK:	
	CMP R0, #0 
	MOVEQ PC, LR
	
	LDR R1, =IOSET
	STR R2, [R1]
	
	MOV R3, #0x5000
SLEEP:
	SUBS R3, R3, #1
	BNE SLEEP 
	
	/*Desliga Led*/		
	LDR R1, =IOCLR
	STR R2, [R1]

	MOV R3, #0x5000
SLEEP1:
	SUBS R3, R3, #1
	BNE SLEEP1
	SUB R0, R0, #1
	B BLINK


_start:
	bl 	KEYBOARD_READ
	bl 	LED_BLINK
	b 	_start
