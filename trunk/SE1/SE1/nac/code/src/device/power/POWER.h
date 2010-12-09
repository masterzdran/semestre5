#ifndef POWER_H
#define POWER_H

#define pPower    ((pLPC_POWER) 0xE01FC0C0)

typedef struct _POWER{
    U32 POWER_CONTROL;
    U32 POWER_CONTROL_PERIPHERICAL;
}LPC_POWER,*pLPC_POWER;

#define __PCTIM0_ENABLE__     0x000002
#define __PCTIM1_ENABLE__     0x000004
#define __PCUART0_ENABLE__    0x000008
#define __PCUART1_ENABLE__    0x000010
#define __PCPWM0_ENABLE__     0x000020
#define __PCI2C_ENABLE__      0x000080
#define __PCSPI_ENABLE__      0x000100
#define __PCRTC_ENABLE__      0x000200
#define __PCSSP_ENABLE__      0x200000
#define __POWER_MASK__        0x2003BE
#endif POWER_H
