/********************************************************************************
* adc.h: Contains macro definitions and function declarations relevant to
*		 AD-conversion.
********************************************************************************/

#ifndef ADC_H_
#define ADC_H_

/* Include directives */
#include "global_header.h"

/* Macro definitions */
#define VREF 3.3							// Voltage at the AREF pin.
#define ADC_MAX 1023.0						// Highest value in 10-bits.
#define ADC_RESOLUTION 0.0032				// 3.3 V divided into 1024 steps, 3.2 mV resolution.

/* External function declarations */
uint16_t adc_read(uint8_t pin);
uint16_t adc_read_avg_4(uint8_t pin);
uint16_t adc_read_avg_8(uint8_t pin);
double adc_read_voltage(uint8_t pin);

#endif /* ADC_H_ */