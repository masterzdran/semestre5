/* LPC2606 INITIALIZATION */

.set  	MODE_SYS, 0x1F            		/* System Running Priviledged Operating System Tasks  Mode	*/
.set  	I_BIT, 0x80               		/* when I bit is set, IRQ is disabled (program status registers) */
.set  	F_BIT, 0x40               		/* when F bit is set, FIQ is disabled (program status registers) */

.section .startup
.text
.global _start

/* STARTUP SECTION - VECTORS INITIALIZATION*/

	ldr 	PC, RESET_ADDR
	ldr 	PC, UNDEF_INST_ADDR
	ldr 	PC, SOFT_INTER_ADDR
	ldr 	PC, INST_MEM_FAULT_ADDR
	ldr 	PC, DATA_MEM_FAULT_ADDR
			.word 0xB8A06F58
	ldr 	PC, IRQ_ADDR
	ldr 	PC, FIQ_ADDR

	RESET_ADDR: 			.word RESET
	UNDEF_INST_ADDR:		.word UNDEF_INST
	SOFT_INTER_ADDR:		.word SOFT_INTER
	INST_MEM_FAULT_ADDR:	.word INST_MEM_FAULT
	DATA_MEM_FAULT_ADDR:	.word DATA_MEM_FAULT
							.word 0x0
	IRQ_ADDR:				.word IRQ
	FIQ_ADDR:				.word FIQ

/* PROGRAM ENTRY POINT */
RESET:
_start:
		/*save top of stack address to sp*/
		ldr   	r0, =__stack_top__		
		msr   	CPSR_c, #MODE_SYS|I_BIT|F_BIT 	/* User Mode */
		mov   	sp, r0

		/* Clear .bss section */
		ldr   	r1, =__bss_start__
		ldr   	r2, =__bss_end__
		ldr   	r3, =0
bss_clear_loop:
		cmp   	r1, r2
	   	strne 	r3, [r1], #+4
	   	bne   	bss_clear_loop
		
		/* copy DATA from ROM to RAM */
		ldr		r1, =__data_start__
		ldr		r2, =__rom_data_start__
		ldr		r3, =__data_end__
		cmp		r1, r2
		beq		end_set_loop
set_loop:
		cmp		r1, r3
		ldr		r4, [r2], #4
		str		r4, [r1], #4
		bne		set_loop
end_set_loop:

		/*Configure oscilator - call StartOsc function*/
		ldr   	r10, =StartOsc
        mov   	lr, pc
        bx    	r10

		/*Call main program*/
       	ldr   	r10, =main
        mov   	lr, pc
        bx    	r10

/*reserve 4096 byte for Stack*/
.section .stack
		.space	1024 * 4
__stack_top__:

		
/***********************/	
/* EXCEPTIONS HANDLING */
/***********************/

UNDEF_INST:
		b UNDEF_INST
SOFT_INTER:
		b SOFT_INTER
INST_MEM_FAULT:
		b INST_MEM_FAULT
DATA_MEM_FAULT:
		b DATA_MEM_FAULT
IRQ:
		b IRQ
FIQ:
		b FIQ
.end
