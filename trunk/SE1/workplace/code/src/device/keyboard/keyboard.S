.global KEYBOARD_READ
.global HAS_KEY
.global GET_KEY

.data
	last_key_bitmap:	.word	0x0
	
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

/* Check for a pressed key. Save key bitmap into last_key_bitmap	*/
/* return 1 if key present, 0 if no key								*/

HAS_KEY:
	/*load column and row masks*/
	/*r12 - COL ------ r0 - ROW*/
	ldr 	r12, =COL_MASK
	ldr		r0, =ROW_MASK
	
	ldr 	r1, =IODIR	/*Set Output to Column*/
    str 	r12, [r1]
	
	mov		r4, #20		/*delay para garantir sinais*/
	subs	r4, r4, #1
	subne	pc, pc, #3*4
		
	ldr 	r1, =IOCLR	/*Set column to 0*/
	str 	r12,[r1]	

	ldr 	r1, =IOPIN	/*Read row status*/
	ldr 	r2, [r1]	
	and 	r2, r2, r0
	
	/*if key not present return 0*/
	cmp		r2, r0
	bne		CONT
	ldr		r1, =last_key_bitmap
	mov		r2, #0xFF
	str		r2, [r1]
	mov		r0, #0
	mov		pc, lr
CONT:
	ldr 	r1, =IOCLR	/*Clear Col Output*/
    str 	r12, [r1]
	
    ldr 	r1, =IODIR	/*Set Output to Row*/
    str 	r0, [r1]
	
	mov		r4, #20		/*delay para garantir sinais*/
	subs	r4, r4, #1
	subne	pc, pc, #3*4
	
	ldr 	r1, =IOCLR	/*Set row to 0*/
	str 	r0, [r1]

	ldr 	r1, =IOPIN	/*Read col status*/
	ldr 	r3, [r1]
	and 	r3, r3, r12
	
	/* R2 = ROW BITMAP and R3 = COL BITMAP*/
	/* Join bitmaps: 0x<ROW><COL>         */
	cmp		r0, #0xF0
	movne	r0, r0, lsr #1
	movne 	r2, r2, lsr #1
	subne	pc, pc, #5*4

	cmp		r12, #0xF
	movne	r12, r12, lsr #1
	movne	r3, r3, lsr #1
	subne	pc, pc, #5*4

	mov		r0, r2
	orr		r0, r0, r3
	ldr		r1, =last_key_bitmap
	streq	r0, [r1]
	mov		r0, #1
	mov 	pc, lr



/* Decode bitmap present at last_key_bitmap */
/* return decoded key					 	*/
/* return -1 if no key present				*/

GET_KEY:
	/*get bitmap to decode from last_key_bitmap, split it to R2 and R3*/
	ldr		r1, =last_key_bitmap
	ldr		r0, [r1]
	eors	r0, r0, #0xFF
	moveq	r0,	#-1
	moveq 	pc, lr
	and		r2, r0, #0xF0
	and		r3, r0, #0xF
	
	/*shift results to the right and remove one unit to adjust to
		keyboard values 0-15*/
	mov 	r2, r2, lsr #5
	mov 	r3, r3, lsr #1
	mov 	r0,#0
	mov 	r1,#0

	cmp 	r2, #0
	addne 	r0, r0, #1
	movne 	r2, r2, lsr #1
	subne	pc, pc, #5*4

	cmp 	r3, #0
	addne 	r1, r1, #1
	movne 	r3, r3, lsr #1
	subne	pc, pc, #5*4

	orr		r0, r1, r0, lsl #2
	mov 	pc, lr

KEYBOARD_READ:
	
	mov		ip, sp
	stmfd	sp!,{r4, FP, IP, LR, PC}
	sub		fp, ip, #4

	/* Set LPC to read from keyboard   */
	/* PIN Function Selection Register */
	
	ldr 	r1, =PINSEL0
	ldr 	r0, =0
	str 	r0, [r1]

	bl 		HAS_KEY
/*	cmp		r0, #0xFF
	beq		_KEY*/
	bl		GET_KEY
	
	ldmdb	fp,{r4, fp,sp,pc}
	
