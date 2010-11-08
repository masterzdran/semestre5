
.global MAIN
/*
.data
	LAST_KEY:	.word 0x00000000
*/	
.text

	/*Register address declaration*/
	PINSEL0  =	0xE002C000
	PINSEL1  =	0xE002C004
	IOPIN	 =	0xE0028000
	IOSET	 =	0xE0028004
	IODIR	 =	0xE0028008
	IOCLR	 =	0xE002800C
	
	COL_MASK =	0x000000F0
	ROW_MASK =	0x00000F00
	LED_MASK =	0x00001000
	
	SLEEP_MASK = 0x20000

KEYBOARD_READ:
	/* PIN Function Selection Register */
	LDR R1, =PINSEL0
	EOR R2, R2, R2
	STR R2, [R1]
	LDR R4, =COL_MASK
	LDR R5, =ROW_MASK
	/*LDR R3, LAST_KEY_ADDR*/
	/*MOV R6, #0*/
	/* PIN Direction Control Register */
	/* 0-INPUT 1-OUTPUT */

GET_KEY:
	/*Set Output to Column*/
    LDR R1, =IODIR
    STR R4, [R1] 
	
	/*Set column to 0*/
	LDR R1, =IOCLR
	STR R4,[R1]

	/*Read row status*/
	LDR R1, =IOPIN
	LDR R2, [R1]
	AND R2, R2, R5
	
	/*If row has no key sleep and start over*/	
	CMP R2, R5
	BNE READ_COL
	MOV R6, #0
	B GET_KEY
	
READ_COL:
	/*Clear Col Output*/
	LDR R1, =IOCLR
    STR R4, [R1]
	
	/*Set Output to Row*/
    LDR R1, =IODIR
    STR R5, [R1]
	
	/*Set row to 0*/
	LDR R1, =IOCLR
	STR R5, [R1]

	/*Read col status*/
	LDR R1, =IOPIN
	LDR R3, [R1]
	AND R3, R3, R4

	/* R2 = ROW e R3 = COL*/
	EOR R2, R2, R5
	EOR R3, R3, R4

	/*Check Bitmap to see key change*/
	ORRS R0, R2, R3
	CMP R6, R0
	BEQ GET_KEY
	/*save current key to last key*/
	/*LDR R1, LAST_KEY_ADDR
	STR R0, [R1]*/
	MOV R6, R0
	
	/*Key decoding*/
	/*shift results to the right and remove one unit to adjust to
		keyboard values*/
	MOV R2, R2, LSR #9
	MOV R3, R3, LSR #5
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


/*	LAST_KEY_ADDR: .word LAST_KEY*/
	
LED_BLINK:

	/* PIN Function Selection Register */
	LDR R1, =PINSEL0
	EOR R2, R2, R2
	STR R2, [R1]

	/*Activate Led Pin output*/
    LDR R1, =IODIR
	LDR R2, =LED_MASK
    STR R2, [R1]
	/*make sure the led is off*/
	LDR R1, =IOCLR
	STR R2, [R1]
	
BLINK:	
	CMP R0, #0 
	MOVEQ PC, LR
	
	/*LED ON*/
	LDR R1, =IOSET
	STR R2, [R1]
	
	LDR R3, =SLEEP_MASK
SLEEP:
	SUBS R3, R3, #1
	BNE SLEEP 
	
	/*LED OFF*/		
	LDR R1, =IOCLR
	STR R2, [R1]

	LDR R3, =SLEEP_MASK
SLEEP1:
	SUBS R3, R3, #1
	BNE SLEEP1
	SUB R0, R0, #1
	B BLINK

MAIN:
	bl 	KEYBOARD_READ
	bl 	LED_BLINK
	b 	MAIN
