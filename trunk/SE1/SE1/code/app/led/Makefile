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
# $^ : The names of all the prerequisites, with spaces between them.
# $@ : The file name of the target of the rule.
# $< : The name of the first prerequisite.
# $+ : This is like ‘$^’, but prerequisites listed more than once are duplicated in the order they were listed in the makefile.
# $* : The stem with which an implicit rule matches (see Section 10.5.4 [How Patterns Match], page 100)
# $% : The target member name, when the target is an archive member.
# $? : The names of all the prerequisites that are newer than the target, with spaces between them.
# (10.5.3 Automatic Variables, page 98, gnu-make.pdf)
#=======================================================================
#Shell Path
SHELL			= /bin/sh
#Environmental Paths
SVN_PATH		= /home/masterzdran/ISEL/semestre5/SE1
PROJECT_PATH	= $(SVN_PATH)/SE1/code
APP				= $(PROJECT_PATH)/app
MYLIB			= $(PROJECT_PATH)/mylib
#Executables
CC 				= arm-eabi-gcc
AS				= arm-eabi-as
LD				= arm-eabi-ld
#Debugger
DEBUGGER		= arm-eabi-insight
#Commom Options
OUTPUT 			= -o
LDSCRIPT		= -T 
DEBUGSTABS		= --gstabs
#Phony Target
.PHONY 			= clean
.PHONY			= clear
#=======================================================================
#Set the Correct LdScript
ifdef ROM
LDSCRIPT_FILE	= $(MYLIB)/ldscript_rom
END_EXEC		= main_rom.elf
else
ifdef RAM
LDSCRIPT_FILE	= $(MYLIB)/ldscript_ram
END_EXEC		= main_ram.elf
else
LDSCRIPT_FILE	= $(MYLIB)/ldscript_rom
END_EXEC		= main.elf
endif
endif
#=======================================================================
	
$(END_EXEC): init.o main.o  
	$(LD) $(LDSCRIPT) $(LDSCRIPT_FILE) $(OUTPUT) $@ $^

init.o: $(MYLIB)/init.S
	$(AS) $(DEBUGSTABS) $(OUTPUT) $@  $^

main.o: main.S
	$(AS) $(DEBUGSTABS) $(OUTPUT) $@  $^

debug: $(END_EXEC)
	$(DEBUGGER) $(END_EXEC)

clean:
	rm *.o $(END_EXEC)

clear:
	clear
