#ifndef POWER_H
#define POWER_H

#define pPower    ((pLPC_POWER) 0xE01FC0C0)

typedef struct _POWER{
    U32 POWER_CONTROL;
    U32 POWER_CONTROL_PERIPHERICAL;
}LPC_POWER,*pLPC_POWER;



#endif POWER_H
