.global main

.text
	

main:
	bl 		KEYBOARD_READ
	bl 		LED_BLINK
	b 		MAIN
