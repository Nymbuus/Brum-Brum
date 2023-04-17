/********************************************************************************
* delay.c: Contains function definitions for functions used for
*		   generating delays.
*********************************************************************************/

/* Include directives */
#include "gpio.h"

/********************************************************************************
* delay_ms: Generates the desired delay in ms.
*********************************************************************************/
void delay_ms(uint16_t const delay_time_ms)
{
	for (uint16_t i = 0; i < delay_time_ms; i++)
	{
		_delay_ms(1);
	}
	
	return;
}

/********************************************************************************
* delay_us: Generates the desired delay in us.
*********************************************************************************/
void delay_us(const uint16_t delay_time_us)
{
	for (uint16_t i = 0; i < delay_time_us; i++)
	{
		_delay_us(1);
	}
	
	return;
}