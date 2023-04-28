/********************************************************************************
* isr.c: Contains the various Interrupt Service Routines used in the program.
********************************************************************************/

/* Include directives */
#include "global_header.h"

/* Interrupt service routines */

/********************************************************************************
* INT0_vect: Trigger condition: Rising edge PORTD2.
********************************************************************************/
ISR (INT0_vect)
{
	return;
}

/********************************************************************************
* INT1_vect: Trigger condition: Rising edge PORTD3.
********************************************************************************/
ISR (INT1_vect)
{
	return;
}

/********************************************************************************
* TIMER0_OVF_vect: Trigger condition: Executed every 255 us.
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
	return;
}

/********************************************************************************
* TIMER1_OVF_vect: Trigger condition: Executed every 20 ms.
********************************************************************************/
ISR (TIMER1_OVF_vect)
{	
	return;
}