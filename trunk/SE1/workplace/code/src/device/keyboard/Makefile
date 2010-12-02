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
#								KEYBOARD
#=======================================================================
#Shell Path
SHELL			= /bin/sh
MYLIB			= ../../lib
MYINCLUDE		= ../../include
#Executables
AS				= arm-eabi-as
COPY			= cp 
#Commom Options
OUTPUT 			= -o
DEBUGSTABS		= --gstabs
#Phony Target
.PHONY 			= clean
.PHONY			= clear
#=======================================================================
keyboard.o: keyboard.S keyboard.h
	$(AS) $(DEBUGSTABS) $(OUTPUT) $(MYLIB)/$@  $<
	$(COPY) keyboard.h $(MYINCLUDE)/keyboard.h
	
clean:
	rm  $(MYLIB)/keyboard.o
	rm 	$(MYINCLUDE)/keyboard.h

clear:
	clear
