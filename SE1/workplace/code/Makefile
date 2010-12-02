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
#HOME 
HOME			= ./
#SOURCE
SOURCE			=	$(HOME)/src
#Target Path
TARGET			= 	$(HOME)/target
TODEPLOY		= 	$(SOURCE)/deploy
DEVICE			=  	$(SOURCE)/device
MYINCLUDE		=	$(SOURCE)/include
MYLIB			=  	$(SOURCE)/lib

LDS_PATH		=  	$(TODEPLOY)/ldscript
OPENOCD_FILE	=	$((TODEPLOY))/openocd/openocd_lpc2106.cfg

#Virtual Paths
VPATH			= $(MYINCLUDE):$(MYLIB)

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
END_EXEC		= $(TARGET)/rom.elf
else
LDSCRIPT_FILE	= $(LDS_PATH)/ldscript_ram
END_EXEC		= $(TARGET)/ram.elf
endif
#=======================================================================

#=======================================================================
all: $(END_EXEC)

#Generate the executable
$(END_EXEC): $(LYBRARY)
	$(LD) $(LDSCRIPT) $(LDSCRIPT_FILE) $(OUTPUT) $@ $^

#Create the device library
$(LYBRARY): $(MYLIB)/*.o
	$(MAKE) -C $(MYLIB)

init.o:
	$(MAKE) -C $(DEVICE)/startup/

LPC2106.o:	
	$(MAKE) -C $(DEVICE)/LPC2106/

startosc.o:
	$(MAKE) -C $(DEVICE)/startup/

keyboard.o:
	$(MAKE) -C $(DEVICE)/keyboard/

led.o:
	$(MAKE) -C $(DEVICE)/led/

LCD.o:
	$(MAKE) -C $(DEVICE)/LCD/

chrono.o:
	$(MAKE) -C $(DEVICE)/timer/	

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
