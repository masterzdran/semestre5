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
#											Base Dir MakeFile
#=======================================================================
#Shell Path
SHELL			= /bin/sh
#Environmental Paths
SVN_PATH		= ./..
#=======================================================================
PROJECT_PATH	= $(SVN_PATH)/code
SOURCE				= $(PROJECT_PATH)/src
DEVICE				= $(SOURCE)/device
PERIPHERICAL	= $(SOURCE)/peripherical
TODEPLOY			= $(SOURCE)/deploy
PROGRAM				= $(SOURCE)/program
PCOMPILE			= $(SOURCE)/tests
TARGET				= $(PROJECT_PATH)/target
TEST					= $(PROJECT_PATH)/test
#=======================================================================
MYLIB				= $(SOURCE)/lib
INCLUDE			= $(SOURCE)/include
CLIB				= $(SOURCE)/clib/lib
CINCLUDE		= $(SOURCE)/clib/inc
HEADER			= 
SEARCHLIB		= -I$(MYLIB)
#Executables
CC 				= arm-eabi-gcc
AS				= arm-eabi-as
LD				= arm-eabi-ld
OPENOCD		= openocd
#Debugger
DEBUGGER		= arm-eabi-insight
#Commom Options
OUTPUT 				= -o
LDSCRIPT			= -T  
DEBUGSTABS			= --gstabs
DEBUGSYMBOLS		= -g
COPTIONS 			= -Wall -pedantic
COMPILE_ONLY 		= -c 
#Phony Target
.PHONY 				= clean
.PHONY				= clear
.PHONY				= peripherical
.PHONY				= device
.PHONY				= program
.PHONY				= deploy
#=======================================================================
LDS_PATH		=  	$(TODEPLOY)/ldscript
OPENOCD_FILE	=	$(TODEPLOY)/openocd/openocd_lpc2106.cfg
#Set the Correct LdScript
ifdef ROM
LDSCRIPT_FILE	= $(LDS_PATH)/ldscript_rom
END_EXEC		= $(TARGET)/rom.elf
else
LDSCRIPT_FILE	= $(LDS_PATH)/ldscript_ram
END_EXEC		= $(TARGET)/ram.elf
endif

VPATH 			= $(MYLIB):$(CLIB):$(libdir)
#VPATH 			= $(MYLIB)
#=======================================================================
#OBJECT =		start.o startosc.o TIMER.o GPIO.o LCD.o keyboard.o libc.a libgcc.a libLPC2106.a
OBJECT =		libc.a libgcc.a  libLPC2106.a libPeripherical.a
#=======================================================================
all: $(END_EXEC) 

#Generate the executable
#$(OBJECT)
$(END_EXEC): program 
	cp src/device/STARTUP/start.o src/lib/start.o
	$(LD) $(LDSCRIPT) $(LDSCRIPT_FILE) $(OUTPUT) $@  $(MYLIB)/start.o $(PROGRAM)/lcd_test.o -L$(MYLIB) -lPeripherical -lLPC2106 -lc -lgcc

peripherical: device
	@echo "----------------------------------------------------------------------"
	$(MAKE) -C $(PERIPHERICAL)

device:
	@echo "----------------------------------------------------------------------"
	$(MAKE) -C $(DEVICE)
	
program: peripherical device
	@echo "----------------------------------------------------------------------"
	$(MAKE) -C $(PCOMPILE)

#Start the Debugger	
debug: $(END_EXEC)
	@echo "----------------------------------------------------------------------"
	$(DEBUGGER) $(END_EXEC)

#clean files
clean:
	@echo "----------------------------------------------------------------------"
	$(MAKE) -C $(PERIPHERICAL) clean
	$(MAKE) -C $(DEVICE) clean	
	$(MAKE) -C $(PCOMPILE) clean

deploy: $(END_EXEC)
	$(OPENOCD) -f $(OPENOCD_FILE) -c "flash write_image erase $^" -c "sleep 100" -c "reset run" -c "shutdown"

clear:
	clear
