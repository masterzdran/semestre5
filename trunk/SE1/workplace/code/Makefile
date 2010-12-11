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
SVN_PATH		= ./..
#=======================================================================
PROJECT_PATH	= $(SVN_PATH)/code
SOURCE				= $(PROJECT_PATH)/src
DEVICE				= $(SOURCE)/device
TODEPLOY			= $(SOURCE)/deploy
TARGET				= $(PROJECT_PATH)/target
TEST					= $(PROJECT_PATH)/test
#=======================================================================
MYLIB			= $(SOURCE)/lib
INCLUDE		= $(SOURCE)/include
HEADER			= 
SEARCHLIB		= -L$(MYLIB) 
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

VPATH 			= $(MYLIB)
#=======================================================================
OBJECT =		start.o startosc.o TIMER.o GPIO.o  LCD.o  lcd_test.o  
#=======================================================================
all: $(END_EXEC) 

#Generate the executable
$(END_EXEC): $(OBJECT) 
	$(LD)  $(LDSCRIPT) $(LDSCRIPT_FILE) $(OUTPUT) $@  $^ 
	
start.o:
startosc.o:
TIMER.o:
GPIO.o:
LCD.o:
	$(MAKE) -C $(DEVICE)

lcd_test.o:
	$(MAKE) -C $(SOURCE)/tests/lcd-test

#Start the Debugger	
debug: $(END_EXEC)
	$(DEBUGGER) $(END_EXEC)

#clean files
clean:
	$(MAKE) -C $(DEVICE) clean	
clear:
	clear
