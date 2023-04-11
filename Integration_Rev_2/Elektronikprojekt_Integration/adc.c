/********************************************************************************
* adc.c: Contains function definitions relevant to AD-conversion.
********************************************************************************/

/* Include directives */
#include "adc.h"

/* External function definitions */

/********************************************************************************
* adc_read: Performs an AD-conversion on the desired pin and returns
*			the result.
********************************************************************************/
uint16_t adc_read(uint8_t pin)
{
	ADMUX = (0b00 << REFS0) | pin;
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (0b111 << ADPS0);
	while ((ADCSRA & (1 << ADIF)) == 0);
	ADCSRA = (1 << ADIF);
	
	return ADC;
}

/********************************************************************************
* adc_read_avg_4: Performs four AD-conversions on the desired pin and returns
*			      the result as an average value.
********************************************************************************/
uint16_t adc_read_avg_4(uint8_t pin)
{
	uint16_t temp_readings = 0;
	
	for (uint8_t i = 0; i < 4; i++)
	{
		temp_readings += adc_read(pin);
	}
	
	return (temp_readings >> 2);
}

/********************************************************************************
* adc_read_avg_8: Performs eight AD-conversions on the desired pin and returns
*			      the result as an average value.
********************************************************************************/
uint16_t adc_read_avg_8(uint8_t pin)
{
	uint16_t temp_readings = 0;
	
	for (uint8_t i = 0; i < 8; i++)
	{
		temp_readings += adc_read(pin);
	}
	
	return (temp_readings >> 3);
}

/********************************************************************************
* adc_read_voltage: Performs eight AD-conversions on the desired pin and returns
*			        the result calculated into a voltage level.
********************************************************************************/
double adc_read_voltage(uint8_t pin)
{
	double voltage = ADC_RESOLUTION * adc_read_avg_8(pin);
	
	return voltage;
}