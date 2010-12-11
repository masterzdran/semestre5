/*
    The following should be covered in this startup file:
    1. Interrupt Vector table
    2. Stack pointers
    3. Branch to Main
*/
/*****************************************************************
	Module includes the interrupt vectors and start-up code.
******************************************************************/

.set  	MODE_SYS,   0x1F  		/* System Running Priviledged Operating System Tasks  Mode */
.set  	I_BIT,      0x80   		/* when I bit is set, IRQ is disabled (program status registers) */
.set  	F_BIT,      0x40   		/* when F bit is set, FIQ is disabled (program status registers) */

/******************************************************************
	Module includes the interrupt vectors and startup code.
******************************************************************/
.section .startup, "ax"
.global _start

/* Exception Vectors */
_vectors:
      ldr     pc, ResetAddr
    	ldr     pc, UndefAddr
    	ldr     pc, SWIAddr
    	ldr     pc, PAbtAddr
    	ldr     pc, DAbtAddr
      .word	  0xB8A06F58
    	ldr     pc, IRQAddr
    	ldr     pc, FIQAddr

ResetAddr:	    .word   ResetHandler
UndefAddr:     	.word   UndefHandler
SWIAddr:       	.word   SWIHandler
PAbtAddr:      	.word   PAbortHandler
DAbtAddr:      	.word   DAbortHandler
                .word	  0
IRQAddr:	      .word	  IRQHandler
FIQAddr:       	.word   FIQHandler

ResetHandler:
_start:
  /*save top of stack address to sp*/
	ldr   	r0, =__stack_top__
	msr   	cpsr_c, #MODE_SYS|I_BIT|F_BIT 	/* System Mode */
	mov   	sp, r0

	/* Clear .bss section */
	ldr   	r1, =__bss_start__
	ldr   	r2, =__bss_end__
	ldr   	r3, =0
bss_clear_loop:
	cmp   	r1, r2
	strne 	r3, [r1], #+4
	bne   	bss_clear_loop

	/* Initialise .data section */
	ldr	r1, =__data_start__		/* Start of memory block */
	ldr	r2, = __rom_data_start__	/* End of memory block */
	ldr	r3, =__data_end__
	cmp	r1, r2
	beq	end_set_loop
set_loop:
	cmp	r1, r3
	ldrne	r4, [r2], #4
	strne	r4, [r1], #4
	bne	set_loop
end_set_loop:

       	ldr   	r10, =StartOsc
        mov   	lr, pc
        bx    	r10

       	ldr   	r10, =main
        mov   	lr, pc
        bx    	r10                       /* enter main() */


.section .stack
		.space	1024 * 4
__stack_top__:

/****************************************************************************/
/*                         Default interrupt handler                        */
/****************************************************************************/

UndefHandler:
   b UndefHandler

SWIHandler:
   b SWIHandler

PAbortHandler:
   b PAbortHandler

DAbortHandler:
   b DAbortHandler

IRQHandler:
   b IRQHandler
FIQHandler:
   b FIQHandler

.end
