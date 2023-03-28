/********************************************************************************
* setup.c:
********************************************************************************/

/* Include directives */
#include "global_header.h"

/* Local function declarations */

static inline void init_adc(void);

/* External function definitions */

void setup(void)
{
	init_adc();
	serial_init(9600);
	
	return;
}

/* Local function definitions */

/********************************************************************************
* init_adc: Performs an AD-conversion to initialize the hardware in order
*			to reduce conversion time of consequent conversions.
********************************************************************************/
static inline void init_adc(void)
{
	(void)adc_read(SENSOR_CENTER_PIN);
	
	return;
}