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
#								STARTUP
#=======================================================================
#Shell Path
SHELL			= /bin/sh
MYLIB			= ../../lib
MYINCLUDE		= ../../include
#Executables
CC 				= arm-eabi-gcc 
COPY			= cp 
AS				= arm-eabi-as
#Commom Options
OUTPUT 			= -o
DEBUGSTABS		= --gstabs
DEBUGGER		= -g
COPTIONS 		= -Wall -pedantic
COMPILE_ONLY 	= -c 
#Phony Target
.PHONY 			= clean
.PHONY			= clear
#=======================================================================
all: startosc.o init.o

startosc.o: startosc.c startosc.h
	$(CC) $(DEBUGGER) $(COMPILE_ONLY) $(COPTIONS) $(OUTPUT) $(MYLIB)/$@  $<
	$(COPY) startosc.h $(MYINCLUDE)/startosc.h
	
init.o: init.S 
	$(AS) $(DEBUGSTABS) $(OUTPUT) $(MYLIB)/$@  $<
	
clean:
	rm  $(MYLIB)/startosc.o 
	rm	$(MYLIB)/init.o 
	rm	$(MYINCLUDE)/startosc.h

clear:
	clear
