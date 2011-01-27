/*
    FROM:       http://www.keil.com/dd/chip/3483.htm
    FROM:       http://www.nxp.com/#/pip/pip=[pip=LPC2104_2105_2106]|pp=[t=pip,i=LPC2104_2105_2106]
    FROM:       http://www.nxp.com/#/page/content=[f=/dynamic/supportportal/tid-50809_sid-45994/applicationnotes.xml]
    DOCUMENT:   AN10404     Initialization code/hints for the LPC2000 family	300 kB	2005-11-01
    DOCUMENT:   AN10255     Philips LPC210x microcontroller family	135 kB	2004-10-25
*/

The application note has been divided into the following sections:

1. Initialization guidelines
    Most ARM applications begin by executing an assembly startup file. This file could be
    linked to the bottom of the on-chip memory (Flash (0x0) or SRAM (0x400 0000)) or Bank
    0 (for devices with an external memory interface) depending from where the application is
    targeted to run. The following should be covered in this startup file:
    1. Interrupt Vector table
    2. Stack pointers
    3. Branch to Main
    
    After the above basic assembly initialization code is executed, a branch is done to C main(). 
    The following steps could be carried out in C code:
        
        1. Enable the Memory Accelerator Module (MAM) if the application is run from on-chip
            Flash. It provides accelerated execution at higher frequencies and also helps in
            reducing power consumption. The MAM is only available in devices with on-chip
            Flash.
        2. Set the System clock and peripheral clock. The system clock can be boosted using
            the PLL to 60 MHz or 75 MHz (for LPC2220) depending upon the input frequency.
            The peripheral clock can be set using the VPB Divider register (VPBDIV at address
            0xE01F C100). Please refer to Application note AN10331 to get detailed information
            about the PLL.
        3. Set the Memory Mapping Control register (MEMMAP at address 0xE01F C040)
            accordingly. The MEMMAP register gives the application the flexibility of executing
            interrupts from different memory regions. For instance, if MEMAP is set to 0x2, the
            interrupt vectors would be mapped to 0x4000 0000 (bottom of on-chip SRAM).
        4. Disable unused peripherals using the Power Control for Peripherals register (PCONP
            at address 0xE01F C0C4).
        5. Configure GPIO’s using the respective IODIR, IOSET and IOCLR registers. On the
            LPC2000, there are certain pins that should not be held low on reset. For instance, by
            driving P0.14 low on reset would make the on-chip bootloader to take control of the
            part after reset (Please refer to the Flash Memory System and Programming Chapter
            in the User Manual for detailed information). There could also be an additional pin in
            certain devices which should not be held low on reset. If low on reset, then the device
            behavior is not guaranteed. The following are the pins in various devices:
                a. In LPC213x and LPC214x devices, P0.31 should not held low on reset
                b. In LPC2114/2124/2212/2214/2119/2129/2194/2290/2292/2294/2210 and 2220
                    devices, P0.26 should not be held low on reset.
        6. Depending upon the peripherals being used set the port functions accordingly using
            the appropriate Pin Function Select register (PINSELx).
        7. Initialize the peripherals which are still enabled in PCONP and enable interrupts for
            them if needed.
        8. Configure the Vectored Interrupt Controller (VIC) to handle the different interrupt
            sources and classify them as IRQ and FIQ. It is recommended that only one interrupt
            source should be classified as an FIQ. For more detailed information on Interrupt
            handling please refer to Application notes AN10254 (Handling Interrupts using IRQ
            and FIQ) and AN10381 (Nesting of interrupts in the LPC2000).
        9. It is always safe to program the Default Vector Address Register (VICDefVectAddr at
            address 0xFFFF F034) with a dummy ISR address wherein the VIC would be updated
            (by performing a write operation on the VIC Vector Address register (VICVectAddr at
            address 0xFFFF F030) to avoid any spurious interrupts.

2. Notes on the On-chip Bootloader
3. Reducing power consumption
4. Code examples
5. Software Tool Support
6. Additional Resources
