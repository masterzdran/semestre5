.global KEYBOARD_READ

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


HAS_KEY:
	/*load column and row masks*/
	/*r12 - COL*/
	/*r0  - ROW*/
	ldr 	r12, =COL_MASK
	ldr		r0, =ROW_MASK
	
	/*Set Output to Column*/
	ldr 	r1, =IODIR
    str 	r12, [r1] 
	
	/*Set column to 0*/
	ldr 	r1, =IOCLR
	str 	r12,[r1]

	/*Read row status*/
	ldr 	r1, =IOPIN
	ldr 	r2, [r1]
	and 	r2, r2, r0

	/*Clear Col Output*/
	ldr 	r1, =IOCLR
    str 	r12, [r1]
	
	/*Set Output to Row*/
    ldr 	r1, =IODIR
    str 	r0, [r1]
	
	/*Set row to 0*/
	ldr 	r1, =IOCLR
	str 	r0, [r1]

	/*Read col status*/
	ldr 	r1, =IOPIN
	ldr 	r3, [r1]
	and 	r3, r3, r12
	
	/* R2 = ROW BITMAP and R3 = COL BITMAP*/
	/* Join bitmaps: 0x<ROW><COL>*/
SHIFT_LOOP1:
	cmp		r0, #0xF0
	beq		SHIFT_LOOP2
	mov		r0, r0, lsr #1
	mov 	r2, r2, lsr #1
	b		SHIFT_LOOP1

SHIFT_LOOP2:
	cmp		r12, #0xF
	beq		SHIFT_LOOP_END
	mov		r12, r12, lsr #1
	mov 	r3, r3, lsr #1
	b		SHIFT_LOOP2

SHIFT_LOOP_END:
	eor		r0, r0, r0
	mov		r0, r2
	orr		r0, r0, r3

	mov 	pc, lr
		

GET_KEY:
	/*receive bitmap to decode in R0, split ir to R2 and R3*/
	and		r2, r0, #0xF0
	and		r3, r3, #0xF

	/*Bitmap decoding*/
	eor 	r2, r2, #0xF0
	eor 	r3, r3, #0xF
	orr 	r0, r2, r3
		
	/*shift results to the right and remove one unit to adjust to
		keyboard values 0-15*/
	mov 	r2, r2, lsr #5
	mov 	r3, r3, lsr #1
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

KEYBOARD_READ:
	
	mov		ip, sp
	stmfd	sp!,{FP, IP, LR, PC}
	sub		fp, ip, #4

	/* Set LPC to read from keyboard   */
	/* PIN Function Selection Register */
	
	ldr 	r1, =PINSEL0
	ldr 	r0, =0
	str 	r0, [r1]
	
	/* PIN Direction Control Register */
	/* 0-INPUT 1-OUTPUT */
_KEY:
	bl 		HAS_KEY
	/*if not has_key get key*/
/*	cmp		r0, #0xFF
	beq		_KEY*/
	bl		GET_KEY
	
	ldmdb	fp,{fp,sp,pc}
	
