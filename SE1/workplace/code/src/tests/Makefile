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
#															LCD TEST
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
PCOMPILE			= $(SOURCE)/tests/
#=======================================================================
MYLIB			= $(SOURCE)/lib
PROGRAM		= $(SOURCE)/program
INCLUDE		= $(SOURCE)/include
SEARCHLIB		= -I $(INCLUDE) -I $(MYLIB)
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

all: 
	@echo "=================================="
	@echo "Compiling the Program"
	@echo "=================================="	
#$(MAKE) -C lcd-test/
	$(MAKE) -C Tacografo/

	
clean:
	@echo "=================================="
	@echo "Cleaning the Program"
	@echo "=================================="	
#$(MAKE) -C lcd-test/ clean	
	$(MAKE) -C Tacografo/ clean	
	
clear:
	clear
