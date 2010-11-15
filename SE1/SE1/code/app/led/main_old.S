
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
	LED_MASK =	0x00002000
	
	SLEEP_MASK = 0x20000

KEYBOARD_READ:
	/* PIN Function Selection Register */
	ldr 	r1, =PINSEL0
	eor 	r2, r2, r2
	str 	r2, [r1]
	ldr 	r4, =COL_MASK
	ldr 	r5, =ROW_MASK
	/*ldr 	r3,	LAST_KEY_ADDR*/
	/*mov		r6, #0*/
	/* PIN Direction Control Register */
	/* 0-INPUT 1-OUTPUT */

GET_KEY:
	/*Set Output to Column*/
    ldr 	r1, =IODIR
    str 	r4, [r1] 
	
	/*Set column to 0*/
	ldr 	r1, =IOCLR
	str 	r4,[r1]

	/*Read row status*/
	ldr 	r1, =IOPIN
	ldr 	r2, [r1]
	and 	r2, r2, r5
	
	/*If row has no key start over*/	
	cmp 	r2, r5
	bne 	READ_COL
	mov 	r6, #0
	b 		GET_KEY
	
READ_COL:
	/*Clear Col Output*/
	ldr 	r1, =IOCLR
    str 	r4, [r1]
	
	/*Set Output to Row*/
    ldr 	r1, =IODIR
    str 	r5, [r1]
	
	/*Set row to 0*/
	ldr 	r1, =IOCLR
	str 	r5, [r1]

	/*Read col status*/
	ldr 	r1, =IOPIN
	ldr 	r3, [r1]
	and 	r3, r3, r4

	/*If col has no key start over*/	
	cmp 	r3, r4
	bne 	DECODE_KEY
	mov 	r6, #0
	b 		GET_KEY
	
DECODE_KEY:	
	/* R2 = ROW e R3 = COL*/
	eor 	r2, r2, r5
	eor 	r3, r3, r4

	/*Check Bitmap to see key change*/
	orrs 	r0, r2, r3
	cmp 	r6, r0
	beq 	GET_KEY
	
	/*Check is new key is NO_KEY*/
	cmp		r6,	#0
	beq		GET_KEY
	
	/*save current key to last key*/
	/*ldr 	r1, LAST_KEY_ADDR
	str 	r0, [r1]*/
	mov 	r6, r0
	
	/*Key decoding*/
	/*shift results to the right and remove one unit to adjust to
		keyboard values*/
	mov 	r2, r2, lsr #9
	mov 	r3, r3, lsr #5
	mov 	r0,#0
	mov 	r1,#0
W1:
	cmp 	r2, #0
	beq 	W2
	add 	r0, r0, #1
	mov 	r2, r2, lsr #1
	b 		W1
W2:
	cmp 	r3, #0
	beq 	CONT
	add 	r1, r1, #1
	mov 	r3, r3, lsr #1
	b 		W2
CONT:
	mov 	r0, r0, lsl #2
	orr 	r0, r0, r1
	mov 	pc, lr


/*	LAST_KEY_ADDR: .word LAST_KEY*/
	
LED_BLINK:

	/* PIN Function Selection Register */
	ldr 	r1, =PINSEL0
	eor 	r2, r2, r2
	str 	r2, [r1]

	/*Activate Led Pin output*/
    ldr 	r1, =IODIR
	ldr 	r2, =LED_MASK
    str 	r2, [r1]
	/*make sure the led is off*/
	ldr 	r1, =IOCLR
	str 	r2, [r1]
	
BLINK:	
	cmp 	r0, #0 
	moveq 	PC, LR
	
	/*LED ON*/
	ldr 	r1, =IOSET
	str 	r2, [r1]
	
	ldr 	r3, =SLEEP_MASK
SLEEP:
	subs 	r3, r3, #1
	bne 	SLEEP 
	
	/*LED OFF*/		
	ldr 	r1, =IOCLR
	str 	r2, [r1]

	ldr 	r3, =SLEEP_MASK
SLEEP1:
	subs 	r3, r3, #1
	bne 	SLEEP1
	sub 	r0, r0, #1
	b 		BLINK

MAIN:
	bl 	KEYBOARD_READ
	bl 	LED_BLINK
	b 	MAIN
