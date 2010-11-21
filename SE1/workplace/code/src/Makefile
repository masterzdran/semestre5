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
PROJECT_PATH	= /mnt/hgfs/Semestre5/SE1/workplace/code
#HOME 
HOME			= $(PROJECT_PATH)/src
#Target Path
TARGET			= $(PROJECT_PATH)/target
DEVICE			=  $(HOME)/device
MYLIB			=  $(HOME)/lib
LDS_PATH		=  $(HOME)/deploy/ldscript
#Virtual Paths
vpath 	%.h 		$(HOME)/include
vpath  	%.o			$(MYLIB)

#Library
LYBRARY			= $(MYLIB)/library.ar
#=======================================================================
#Executables
CC 				= arm-eabi-gcc 
AS				= arm-eabi-as
LD				= arm-eabi-ld 

#=======================================================================
#Debugger
DEBUGGER		= arm-eabi-insight
#=======================================================================
#Commom Options
OUTPUT 			= -o
LDSCRIPT		= -T 
DEBUGSTABS		= --gstabs
DEBUGGER		= -g
COPTIONS 		= -Wall -pedantic
COMPILE_ONLY 	= -c 
#=======================================================================
#Phony Target
.PHONY 			= clean
.PHONY			= clear
#=======================================================================
#Set the Correct LdScript
ifdef ROM
LDSCRIPT_FILE	= $(LDS_PATH)/ldscript_rom
END_EXEC		= $(TARGET)/main_rom.elf
else
LDSCRIPT_FILE	= $(LDS_PATH)/ldscript_ram
END_EXEC		= $(TARGET)/main.elf
endif
#=======================================================================
OBJECT			= init.o startosc.o led.o keyboard.o main.o
#=======================================================================
all: $(END_EXEC)

#Generate the executable
$(END_EXEC): $(LYBRARY)
	$(LD) $(LDSCRIPT) $(LDSCRIPT_FILE) $(OUTPUT) $@ $^

#Create the device library
$(LYBRARY): $(OBJECT)
	$(MAKE) -C $(MYLIB)
	


#Generate Object

init.o:

LPC2106.o:	
	$(MAKE) -C $(DEVICE)/LPC2106/
startosc.o:
	$(MAKE) -C $(DEVICE)/startup/
keyboard.o:
	$(MAKE) -C $(DEVICE)/keyboard/
led.o:
	$(MAKE) -C $(DEVICE)/led/
main.o:	
	$(MAKE) -C $(DEVICE)/main/
	

#Start the Debugger	
debug: $(END_EXEC)
	$(DEBUGGER) $(END_EXEC)

#clean files
clean:
	$(MAKE) -C $(DEVICE)/startup/ clean
	$(MAKE) -C $(DEVICE)/keyboard/ clean
	$(MAKE) -C $(DEVICE)/led/ clean
	$(MAKE) -C $(DEVICE)/main/ clean
	
clear:
	clear
