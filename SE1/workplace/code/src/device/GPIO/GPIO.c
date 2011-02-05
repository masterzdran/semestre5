/**
#=======================================================================
# SE1   - Sistemas Embebidos 1
#-----------------------------------------------------------------------
# Turma:	LI51N
# Semestre:	Inverno 2010/2011
# Data:		Novembro/2010
#-----------------------------------------------------------------------
# Nome: 	Nuno Cancelo
# Numero:	31401
#-----------------------------------------------------------------------
# Nome:		Nuno Sousa
# Numero:	33595
#-----------------------------------------------------------------------
# LEIC  - Licenciatura em Engenharia Informática e Computadores
# DEETC - Dep. de Eng. Electrónica e Telecomunicações e Computadores
# ISEL  - Instituto Superior de Engenharia de Lisboa
#=======================================================================
**/
#include "GPIO.h"
/**
 * Iniciação dos portos de GPIO com a operação definida pela 'mask', definindo o comportamento desse porto de GPIO (0-15)
 **/
void gpio_init_PINSEL0(U32 mask){ 
 __PINSEL0__ &= ~mask; 
}

/**
 * Iniciação dos portos de GPIO com a operação definida pela 'mask', definindo o comportamento desse porto de GPIO (16-31)
 **/
void gpio_init_PINSEL1(U32 mask){   
  __PINSEL1__ &= ~mask;
}
/**
 * Iniciação dos portos de GPIO com a(s) operação(ões) definidas pelas mascaras  'pinsel0_mask' e 'pinsel0_mask'
 **/
void gpio_init(U32 pinsel0_mask,U32 pinsel1_mask){
  __PINSEL0__ = pinsel0_mask;
  __PINSEL1__ = pinsel1_mask;
} 
/**
 * Escreve nos pinos definidos por 'mask' o valor de 'value'.
 * O valor de 'value' tem que estar definido dentro da mascara, caso contrário não é garantido o comportamento desejado.
 **/ 
void gpio_write(U32 mask, U32 value){
  pGPIO->IOCLR |= mask ;
  pGPIO->IOSET |= mask & value;    
}
/**
 * Define a direcção dos bits indicados pela 'mask'.
 * Com o parametro direction = GPIO_IN os são definidos como entrada
 * Com o parametro direction = GPIO_OUT os são definidos como saída
 **/ 
void gpio_set_direction(U32 mask, U8 direction){
  if (direction)
    pGPIO->IODIR |= mask;
  else
    pGPIO->IODIR &= ~mask;
}
/**
 * Activa os bits definidos pela 'mask'
 **/ 
void gpio_set(U32 mask){
  pGPIO->IOSET |= mask;
}
/**
 * Limpa os bits definidos pela 'mask'
 **/ 
void gpio_clear(U32 mask){
  pGPIO->IOCLR |= mask ;
}
/**
 * Lê o o porto GPIO definido pela 'mask' e devolve o respectivo valor
 **/
U32 gpio_read(U32 mask){
    return  pGPIO->IOPIN & mask;
}
