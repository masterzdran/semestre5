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
SVN_PATH		= /mnt/hgfs/Semestre5/SE1
PROJECT_PATH	= $(SVN_PATH)/SE1/code
APP				= $(PROJECT_PATH)/app
MYLIB			= .
#Executables
CC 				= arm-eabi-gcc
AS				= arm-eabi-as
LD				= arm-eabi-ld
AR				= arm-eabi-ar rcs
#Debugger
DEBUGGER		= arm-eabi-insight
#Commom Options
OUTPUT 			= -o
LDSCRIPT		= -T 
DEBUGSTABS		= --gstabs
#Phony Target
.PHONY 			= clean
.PHONY			= clear
#=======================================================================
all: *.o
	$(AR) $@ $^
	
clean:
	rm  $(MYLIB)/main.o

clear:
	clear
