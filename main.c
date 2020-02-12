#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <assert.h>

#include "serial.h"
#include "avr_const.h"

// ADC is constantly running, even when MCU is active, otherwise, use a low-noise mode
#define FREE_RUNNING
//#define DIFFERENTIAL
#define SWITCH_INPUTS

const uint8_t next_admux[4] =
{
	ADMUX_REFS_1V1 | ADMUX_MUX_ADC23_20x, // input
	ADMUX_REFS_1V1 | ADMUX_MUX_ADC22_20x, // zero
	ADMUX_REFS_1V1 | ADMUX_MUX_TEMP, // temp
	ADMUX_REFS_1V1 | ADMUX_MUX_ADC23_20x, // input
};

int16_t read_adc(void)
{
	uint8_t l = ADCL;
	uint8_t h = ADCH;
#ifdef DIFFERENTIAL
	if (h & 2)
		h |= 0xfc;
#endif
	return ((uint16_t)h << 8) | l;
}

__inline unsigned bits(unsigned n)
{
	return (1u << n) - 1u;
}

void print(char x)
{
	serial_putchar(x);
}

char hex(uint8_t digit)
{
	char c = '0' + digit;
	if (digit >= 10)
		c += 'a' - '0' - 10;
	return c;
}

void print_hex4(uint8_t x)
{
	print(hex(x & 0xf));
}

void print_hex(uint8_t x)
{
	print_hex4(x >> 4);
	print_hex4(x & 0xf);
}

void print_hex16(uint16_t x)
{
	print_hex((x >> 8) & 0xffu);
	print_hex(x & 0xffu);
}

// AVR needs interrupts enabled to exit sleep
void __attribute__((naked)) ADC_vect(void)
{
	asm("reti");
}

int main (void)
{
	CLKPR = 1 << CLKPCE;
	CLKPR = CLKPR_DIV2; // 4 MHz
	PRR = 1 << PRUSI | 1 << PRTIM0 | 1 << PRTIM1;

	// UART TX
	PORTB = 1 << TX;
	DDRB  = 1 << TX;

	// ADC
	DIDR0 |= 1 << ADC2D | 1 << ADC3D;
	ADCSRA |= 1 << ADEN | ADCSRA_ADPS_DIV_32; // 125 kHz at 4 MHz
	ADMUX = next_admux[3];

#ifdef DIFFERENTIAL
	ADCSRB |= BIN;
#endif

#ifdef FREE_RUNNING
	ADCSRB |= ADCSRB_ADTS_FREE_RUNNING;
	ADCSRA |= 1 << ADATE | 1 << ADSC; // start the first conversion in the free running mode
#else
	ADCSRA |= 1 << ADIE;
	MCUCR |= 1 << SE | MCUCR_SM_IDLE; // low noise mode
	sei();
#endif

	// Note: the first millisecond of samples after ADC is turned on should be discarded
	uint8_t i;
	for (i = 0; ; ++i)
	{
		assert(!(ADCSRA & (1 << ADIF)));
#ifdef FREE_RUNNING
		while (!(ADCSRA & (1 << ADIF)));
		ADCSRA |= 1 << ADIF;
#else
		assert(!(ADCSRA & (1 << ADSC)));
		ADCSRA |= 1 << ADSC;
		__asm volatile ("sleep");
		assert(!(ADCSRA & (1 << ADSC))); // have to check this if there are other interrupts
#endif
		int16_t val = read_adc();
		print_hex(i);
		print_hex4((val >> 8) & 0xf);
		print_hex(val & 0xff);
		print('\n');

		// may need time to settle after changing ADMUX or only after changing Vref?
#ifdef SWITCH_INPUTS
		if ((i & bits(6)) == bits(6)
#ifdef FREE_RUNNING
				- 1
#endif
				)
		{
			ADMUX = next_admux[(i >> 6) & 0x3];
		}
#endif
	}
}
