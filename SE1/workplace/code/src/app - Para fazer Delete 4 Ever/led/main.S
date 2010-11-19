.global MAIN

.text
	

MAIN:
	bl 		KEYBOARD_READ
	bl 		LED_BLINK
	b 		MAIN
