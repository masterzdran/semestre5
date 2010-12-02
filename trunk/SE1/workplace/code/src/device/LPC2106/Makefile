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
#								LPC2106
#=======================================================================
#Shell Path
SHELL			= /bin/sh
MYLIB			= ../../lib
MYINCLUDE		= ../../include
#Executables
CC 				= arm-eabi-gcc 
COPY			= cp 
#Commom Options
OUTPUT 			= -o
DEBUGGER		= -g
COPTIONS 		= -Wall -pedantic
COMPILE_ONLY 	= -c 
#Phony Target
.PHONY 			= clean
.PHONY			= clear
#=======================================================================
LPC2106.o: LPC2106.c LPC2106.h
	$(CC) $(DEBUGGER) $(COMPILE_ONLY) $(COPTIONS) $(OUTPUT) $(MYLIB)/$@  $<
	$(COPY) LPC2106.h $(MYINCLUDE)/LPC2106.h

clean:
	rm  $(MYLIB)/LPC2106.c
	rm  $(MYINCLUDE)/LPC2106.h

clear:
	clear
