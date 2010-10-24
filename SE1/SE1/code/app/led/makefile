all: main

main: main.o
	arm-eabi-ld -T ldscript_rom main.o -o main

main.o: main.S
	arm-eabi-as --gstabs main.S -o main.o
