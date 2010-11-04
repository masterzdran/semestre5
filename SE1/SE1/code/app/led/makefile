rom: main

ram: init.o main.o ldscript_rom 
	arm-eabi-ld -T ldscript_ram ../../mylib/init.o main.o -o main

main: init.o main.o ldscript_rom 
	arm-eabi-ld -T ldscript_rom ../../mylib/init.o main.o -o main

init.o:
	arm-eabi-as --gstabs ../../mylib/init.S -o ../../mylib/init.o

main.o: main.S
	arm-eabi-as --gstabs main.S -o main.o

debug:
	arm-eabi-insight main
