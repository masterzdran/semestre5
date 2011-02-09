/*
    The following should be covered in this startup file:
    1. Interrupt Vector table
    2. Stack pointers
    3. Branch to Main
*/
/*****************************************************************
	Module includes the interrupt vectors and start-up code.
******************************************************************/
.equ __USER_MODE__ ,           0x10  /* System Running Priviledged Operating USER Tasks  Mode */
.equ __FIQ_MODE__  ,           0x11  /* System Running Priviledged Operating FIQ Tasks  Mode */
.equ __IRQ_MODE__   ,          0x12  /* System Running Priviledged Operating IRQ Tasks  Mode */
.equ __SUPERVISOR_MODE__ ,     0x13  /* System Running Priviledged Operating SUPERVISOR Tasks  Mode */
.equ __ABORT_MODE__ ,          0x17  /* System Running Priviledged Operating ABORT Tasks  Mode */
.equ __UNDEF_MODE__  ,         0x1B  /* System Running Priviledged Operating UNDEF Tasks  Mode */
.equ __SYSTEM_MODE__  ,        0x1F  /* System Running Priviledged Operating SYSTEM Tasks  Mode */
.equ __FIQ_STACK_SIZE__        ,    3*4
.equ __IRQ_STACK_SIZE__        ,    16*8*4
.equ __ABORT_STACK_SIZE__      ,    1*4
.equ __UNDEF_STACK_SIZE__      ,    1*4
.equ __SUPERVISOR_STACK_SIZE__ ,    1*4

.equ  	I_BIT,      0x80   		/* when I bit is set, IRQ is disabled (program status registers) */
.equ  	F_BIT,      0x40   		/* when F bit is set, FIQ is disabled (program status registers) */

/******************************************************************
	Module includes the interrupt vectors and startup code.
******************************************************************/
.section .startup, "ax"
.global _start
.global _CPU_IRQ_RESET
.global _CPU_IRQ_ENABLE

/* Exception Vectors */
_vectors:
      ldr     pc, ResetAddr
    	ldr     pc, UndefAddr
    	ldr     pc, SWIAddr
    	ldr     pc, PAbtAddr
    	ldr     pc, DAbtAddr
		.word	  0xB9205F80                      /*0xB8A06F58*/
		ldr     pc,[pc,#-0xFF0]                   /*pc, IRQAddr*/
    	ldr     pc, FIQAddr

ResetAddr:	    .word   ResetHandler
UndefAddr:     	.word   UndefHandler
SWIAddr:       	.word   SWIHandler
PAbtAddr:      	.word   PAbortHandler
DAbtAddr:      	.word   DAbortHandler
                .word	  0x0
                .word	  0x0
FIQAddr:       	.word   FIQHandler

ResetHandler:
_start:
  
  ldr   	r0, =__stack_top__
  /*Stack FIQ*/
	msr   	cpsr_c, #__FIQ_MODE__|I_BIT|F_BIT
	mov   	sp, r0
  sub     r0,#__FIQ_STACK_SIZE__
  
  /*Stack IRQ*/
	msr   	cpsr_c, #__IRQ_MODE__|I_BIT|F_BIT
	mov   	sp, r0
  sub     r0,#__IRQ_STACK_SIZE__
  
  /*Stack SUPERVISOR*/
	msr   	cpsr_c, #__SUPERVISOR_MODE__|I_BIT|F_BIT
	mov   	sp, r0
  sub     r0,#__SUPERVISOR_STACK_SIZE__
  
  /*Stack ABORT*/
	msr   	cpsr_c, #__ABORT_MODE__|I_BIT|F_BIT 	
	mov   	sp, r0
  sub     r0,#__ABORT_STACK_SIZE__
  
  /*Stack of UNDEFINED*/
	msr   	cpsr_c, #__UNDEF_MODE__|I_BIT|F_BIT 	
	mov   	sp, r0
  sub     r0,#__UNDEF_STACK_SIZE__
  
  /*Stack of SYSTEM_MODE*/
	msr   	cpsr_c, #__SYSTEM_MODE__|I_BIT|F_BIT 	
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

	/*Enable IRQ*/
  mrs		r0, cpsr
  and		r0,r0, #~(1<<7)
  msr		cpsr_c,r0

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
