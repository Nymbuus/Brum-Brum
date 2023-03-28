/********************************************************************************
* adc.c:
********************************************************************************/

/* Include directives */
#include "adc.h"

/* External function definitions */
uint16_t adc_read(uint8_t pin)
{
	ADMUX = (0b00 << REFS0) | pin;
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (0b111 << ADPS0);
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA = (1 << ADIF);
	
	return ADC;
}

uint16_t adc_read_avg_4(uint8_t pin)
{
	uint16_t temp_readings = 0;
	
	for (uint8_t i = 0; i < 4; i++)
	{
		temp_readings += adc_read(pin);
	}
	
	return (temp_readings >> 2);
}

uint16_t adc_read_avg_8(uint8_t pin)
{
		uint16_t temp_readings = 0;
		
		for (uint8_t i = 0; i < 8; i++)
		{
			temp_readings += adc_read(pin);
		}
		
		return (temp_readings >> 3);
}

double adc_read_voltage(uint8_t pin)
{
	double voltage = ADC_RESOLUTION * adc_read_avg_8(pin);
	
	return voltage;
}