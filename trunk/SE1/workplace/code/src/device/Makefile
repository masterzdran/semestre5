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
#Shell Path
SHELL			= /bin/sh
#Environmental Paths
SVN_PATH		= ./../../..
#=======================================================================
PROJECT_PATH	= $(SVN_PATH)/code
SOURCE				= $(PROJECT_PATH)/src
DEVICE				= $(SOURCE)/device
TARGET				= $(PROJECT_PATH)/target
TEST					= $(PROJECT_PATH)/test
#=======================================================================
MYLIB			= $(SOURCE)/lib
INCLUDE		= $(SOURCE)/include
HEADER			= $(SOURCE)/device/LPC2106 
SEARCHLIB		= -I $(HEADER) -I $(INCLUDE)
#Executables
CC 				= arm-eabi-gcc
AS				= arm-eabi-as
LD				= arm-eabi-ld
#Debugger
DEBUGGER		= arm-eabi-insight
#Commom Options
OUTPUT 					= -o
LDSCRIPT				= -T 
DEBUGSTABS			= --gstabs
DEBUGSYMBOLS		= -g
COPTIONS 				= -Wall -pedantic
COMPILE_ONLY 		= -c 
#Phony Target
.PHONY 					= clean
.PHONY					= clear
#=======================================================================
#															Base Make
#=======================================================================
all: LPC2106.h TYPES.h SCB.h START.o TIMER.o GPIO.o 

LPC2106.h: 
	$(MAKE) -C $(DEVICE)/LPC2106
	
TYPES.h: 
	$(MAKE) -C $(DEVICE)/TYPES
	
SCB.h: 
	$(MAKE)	-C $(DEVICE)/SCB

START.o:
	$(MAKE) -C $(DEVICE)/startup

RTC.o: 
	$(MAKE)	-C $(DEVICE)/rtc
	
TIMER.o: 
	$(MAKE)	-C $(DEVICE)/timer
	
GPIO.o: 
	$(MAKE)	-C $(DEVICE)/GPIO

clean:
	$(MAKE) -C $(DEVICE)/LPC2106 clean
	$(MAKE) -C $(DEVICE)/TYPES  clean
	$(MAKE) -C $(DEVICE)/SCB  clean
	$(MAKE) -C $(DEVICE)/startup  clean
	$(MAKE) -C $(DEVICE)/GPIO clean
	$(MAKE) -C $(DEVICE)/timer clean
	$(MAKE) -C $(DEVICE)/rtc clean
	
clear:
	clear

