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
DEVICE				= $(SOURCE)/peripherical

#=======================================================================
MYLIB			= $(SOURCE)/lib
INCLUDE		= $(SOURCE)/include
SEARCHLIB		= -I $(MYLIB) -I $(INCLUDE)
#Executables
CC 				= arm-eabi-gcc
AS				= arm-eabi-as
LD				= arm-eabi-ld
AR				= arm-eabi-ar rcs
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
.PHONY					= all
#MAKEPATHS				= LCD  KEYBOARD EEPROM Clock Menu
MAKEPATHS				= LCD  KEYBOARD EEPROM
#=======================================================================
#															Base Make PERIPHERICAL
#=======================================================================
all: 
	@echo "=================================="
	@echo "Compiling the Peripherical Library"
	@echo "=================================="	
	$(foreach MPATH, $(MAKEPATHS), $(MAKE) -C $(DEVICE)/$(MPATH);)
	$(AR) $(MYLIB)/libPeripherical.a $(MYLIB)/*.o
	rm -rf $(MYLIB)/*.o

clean:
	@echo "=================================="
	@echo "Cleaning the Peripherical Library"
	@echo "=================================="	
	$(foreach MPATH, $(MAKEPATHS), $(MAKE) -C $(DEVICE)/$(MPATH) clean;)
	rm -rf $(MYLIB)/libPeripherical.a
	
clear:
	clear

