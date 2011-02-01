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
#															Menu
#=======================================================================
#Shell Path
SHELL			= /bin/sh
#Environmental Paths
SVN_PATH		= ./../../../../..
#=======================================================================
PROJECT_PATH	= $(SVN_PATH)/code
SOURCE				= $(PROJECT_PATH)/src
TARGET				= $(PROJECT_PATH)/target
TEST					= $(PROJECT_PATH)/test
#=======================================================================
MYLIB			= $(SOURCE)/lib
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

	
Menu.o: Menu.c Menu.h MenuFunctions.o
	$(CC) $(SEARCHLIB) $(DEBUGSYMBOLS) $(COMPILE_ONLY) $(OUTPUT) $@  $< 
	cp $@ $(MYLIB)/$@
	cp Menu.h $(INCLUDE)/

MenuFunctions.o: MenuFunctions.c MenuFunctions.h
	$(CC) $(SEARCHLIB) $(DEBUGSYMBOLS) $(COMPILE_ONLY) $(OUTPUT) $@  $< 
	cp $@ $(MYLIB)/$@
	cp MenuFunctions.h $(INCLUDE)/

	
clean:
	rm  Menu.o
	rm  $(INCLUDE)/Menu.h
	rm  MenuFunctions.o
	rm  $(INCLUDE)/MenuFunctions.h

clear:
	clear
