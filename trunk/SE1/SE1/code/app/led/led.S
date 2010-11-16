
.global LED_BLINK

	PINSEL0=	0xE002C000
	IODIR=		0xE0028008
	IOSET=		0xE0028004
 	IOCLR=		0xE002800C

	LED_MASK=	0x00002000
	SLEEP_MASK=	100000

.text
	
LED_BLINK:

	cmp 	r0, #0
	movle 	PC, LR

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
	/*LED ON*/
	ldr 	r1, =IOSET
	str 	r2, [r1]
	
	ldr 	r3, =SLEEP_MASK
	subs 	r3, r3, #1
	subne	pc, pc, #3*4
	
	/*LED OFF*/		
	ldr 	r1, =IOCLR
	str 	r2, [r1]

	ldr 	r3, =SLEEP_MASK
	subs 	r3, r3, #1
	subne	pc, pc, #3*4
	
	subs 	r0, r0, #1
	bne		BLINK
	mov		pc, lr
