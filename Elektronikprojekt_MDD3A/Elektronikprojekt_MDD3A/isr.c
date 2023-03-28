/********************************************************************************
* isr.c:
*********************************************************************************/

/* Include directives */
#include "motor_controller.h"

ISR (TIMER0_OVF_vect)
{
	static volatile uint8_t overflow_interrupt_counter = 0;
	
	if (++overflow_interrupt_counter >= 4)
	{
		motor_controller_set_pwm_value();
		overflow_interrupt_counter = 0;	
	}
	
	return;
}