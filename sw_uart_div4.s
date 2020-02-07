.nolist
#include <avr/io.h>
.list

; 4 MHz / 921600 baud

.global serial_putchar
.func serial_putchar
serial_putchar:
	cbi _SFR_IO_ADDR(PORTB), TX ; start bit, 2 clk
	in r25, _SFR_IO_ADDR(PORTB)
	bst r24, 0
	bld r25, TX
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 1
	bld r25, TX
	adiw r24, 0
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 2
	bld r25, TX
	nop
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 3
	bld r25, TX
	nop
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 4
	bld r25, TX
	adiw r24, 0
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 5
	bld r25, TX
	nop
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 6
	bld r25, TX
	nop
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 7
	bld r25, TX
	adiw r24, 0
	out _SFR_IO_ADDR(PORTB), r25
	sbr r25, 1 << TX
	nop
	nop
	out _SFR_IO_ADDR(PORTB), r25
	ret ; 4 clk
.endfunc

.global serial_puts
.func serial_puts
serial_puts:
	movw r30, r24
	and r22, r22
	breq exit
	in r25, _SFR_IO_ADDR(PORTB)
	cbr r25, 1 << TX
loop:
	ld	r24, Z+
	out _SFR_IO_ADDR(PORTB), r25
	nop
	bst r24, 0
	bld r25, TX
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 1
	bld r25, TX
	adiw r24, 0
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 2
	bld r25, TX
	nop
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 3
	bld r25, TX
	nop
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 4
	bld r25, TX
	adiw r24, 0
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 5
	bld r25, TX
	nop
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 6
	bld r25, TX
	nop
	out _SFR_IO_ADDR(PORTB), r25
	bst r24, 7
	bld r25, TX
	nop
	mov r24, r25
	out _SFR_IO_ADDR(PORTB), r25
	sbr r24, 1 << TX
	cbr r25, 1 << TX
	subi r22, 1
	out _SFR_IO_ADDR(PORTB), r24
	brne loop
exit:
	ret
.endfunc
