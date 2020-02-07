#ifndef _AVR_CONST_
#define _AVR_CONST_

enum
{
	CLKPR_DIV1   = 0,
	CLKPR_DIV2   = 1,
	CLKPR_DIV4   = 2,
	CLKPR_DIV8   = 3,
	CLKPR_DIV16  = 4,
	CLKPR_DIV32  = 5,
	CLKPR_DIV64  = 6,
	CLKPR_DIV128 = 7,
	CLKPR_DIV256 = 8,

	MCUCR_SM_IDLE       = 0 << SM1 | 0 << SM0,
	MCUCR_SM_ADC_NR     = 0 << SM1 | 1 << SM0,
	MCUCR_SM_POWER_DOWN = 1 << SM1 | 0 << SM0,

	ADMUX_REFS_2V56     = 1 << REFS2 | 1 << REFS1 | 1 << REFS0,
	ADMUX_REFS_1V1      = 0 << REFS2 | 1 << REFS1 | 0 << REFS0,
	ADMUX_REFS_VCC      = 0 << REFS2 | 0 << REFS1 | 0 << REFS0,

	ADMUX_MUX_ADC0      = 0 << MUX3 | 0 << MUX2 | 0 << MUX1 | 0 << MUX0,
	ADMUX_MUX_ADC1      = 0 << MUX3 | 0 << MUX2 | 0 << MUX1 | 1 << MUX0,
	ADMUX_MUX_ADC2      = 0 << MUX0 | 0 << MUX2 | 1 << MUX1 | 0 << MUX0,
	ADMUX_MUX_ADC3      = 0 << MUX3 | 0 << MUX2 | 1 << MUX1 | 1 << MUX0,
	ADMUX_MUX_ADC22     = 0 << MUX3 | 1 << MUX2 | 0 << MUX1 | 0 << MUX0,
	ADMUX_MUX_ADC22_20x = 0 << MUX3 | 1 << MUX2 | 0 << MUX1 | 1 << MUX0,
	ADMUX_MUX_ADC23     = 0 << MUX3 | 1 << MUX2 | 1 << MUX1 | 0 << MUX0,
	ADMUX_MUX_ADC23_20x = 0 << MUX3 | 1 << MUX2 | 1 << MUX1 | 1 << MUX0,
	ADMUX_MUX_VBG       = 1 << MUX3 | 1 << MUX2 | 0 << MUX1 | 0 << MUX0,
	ADMUX_MUX_GND       = 1 << MUX3 | 1 << MUX2 | 0 << MUX1 | 1 << MUX0,
	ADMUX_MUX_TEMP      = 1 << MUX3 | 1 << MUX2 | 1 << MUX1 | 1 << MUX0,

	ADCSRA_ADPS_DIV_2         = 0 << ADPS2 | 0 << ADPS1 | 1 << ADPS0,
	ADCSRA_ADPS_DIV_4         = 0 << ADPS2 | 1 << ADPS1 | 0 << ADPS0,
	ADCSRA_ADPS_DIV_8         = 0 << ADPS2 | 1 << ADPS1 | 1 << ADPS0,
	ADCSRA_ADPS_DIV_16        = 1 << ADPS2 | 0 << ADPS1 | 0 << ADPS0,
	ADCSRA_ADPS_DIV_32        = 1 << ADPS2 | 0 << ADPS1 | 1 << ADPS0,
	ADCSRA_ADPS_DIV_64        = 1 << ADPS2 | 1 << ADPS1 | 0 << ADPS0,
	ADCSRA_ADPS_DIV_128       = 1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0,

	ADCSRB_ADTS_FREE_RUNNING  = 0 << ADTS2 | 0 << ADTS1 | 0 << ADTS0,
	ADCSRB_ADTS_ANALOG_COMP   = 0 << ADTS2 | 0 << ADTS1 | 1 << ADTS0,
	ADCSRB_ADTS_EXT_INT0      = 0 << ADTS2 | 1 << ADTS1 | 0 << ADTS0,
	ADCSRB_ADTS_TIM0_OCA      = 0 << ADTS2 | 1 << ADTS1 | 1 << ADTS0,
	ADCSRB_ADTS_TIM0_OVF      = 1 << ADTS2 | 0 << ADTS1 | 0 << ADTS0,
	ADCSRB_ADTS_TIM0_OCB      = 1 << ADTS2 | 0 << ADTS1 | 1 << ADTS0,
	ADCSRB_ADTS_PIN_CNG_INT   = 1 << ADTS2 | 1 << ADTS1 | 0 << ADTS0,
};

#endif
