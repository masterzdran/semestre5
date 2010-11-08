ram.elf: init.o gpio.o startosc.o
	arm-eabi-gcc -o ram.elf init.o gpio.o startosc.o -T ldscript_ram  -nostartfiles

rommable.elf: init.o gpio.o startosc.o
	arm-eabi-gcc -o rommable.elf init.o gpio.o startosc.o -T ldscript_rom  -nostartfiles

gpio.o: gpio.c
	arm-eabi-gcc -c -g -o gpio.o gpio.c

startosc.o: startosc.c
	arm-eabi-gcc -c -g -o startosc.o startosc.c

init.o: init.S
	arm-eabi-as --gstabs -o init.o init.S

clean:
	rm -f *.o *.elf
