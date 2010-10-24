valor1: .word	20
valor2: .word	21
menor: .word	0

	.global	_start

_start:
	ldr r0, valor1
	ldr r1, valor2
	cmp r0,r1
	ble 1f
	str r1, menor
	b 2f
1:
	str r0, menor
2:
	b .
