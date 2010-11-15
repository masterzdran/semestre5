/* Memory Accelerator Module (MAM) */
#define MAMCR          (*((volatile unsigned char *) 0xE01FC000))
#define MAMTIM         (*((volatile unsigned char *) 0xE01FC004))
/* Phase Locked Loop (PLL) */
#define PLLCON         (*((volatile unsigned char *) 0xE01FC080))
#define PLLCFG         (*((volatile unsigned char *) 0xE01FC084))
#define PLLSTAT        (*((volatile unsigned short*) 0xE01FC088))
#define PLLFEED        (*((volatile unsigned char *) 0xE01FC08C))
/* VPB Divider */
#define VPBDIV         (*((volatile unsigned char *) 0xE01FC100))

#define PLOCK 		0x400

void StartOsc(void) {
    PLLCFG = 0x23;		// Setting M and P values
    PLLFEED = 0xAA; PLLFEED = 0x55;
    PLLCON = 0x1;		// Enabling the PLL 
    PLLFEED = 0xAA; PLLFEED = 0x55;
    while ( !(PLLSTAT & PLOCK) );   // Wait for the PLL to lock
    PLLCON = 0x3;		// Connect the PLL as the clock source
    PLLFEED = 0xAA; PLLFEED = 0x55;
    MAMCR = 0x2; 		// Enabling MAM and setting number 
    MAMTIM = 0x4; 		// of clocks used for Flash memory fetch
    VPBDIV = 0x1; 		// Setting pclk to cclk
}

