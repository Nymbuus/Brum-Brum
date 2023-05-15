/********************************************************************************
* status_led.c: Contains function definitions related to using a RGB LED.
********************************************************************************/

/* Include directives */
#include "status_led.h"

/* External function definitions */

/********************************************************************************
* status_led_display_color: Sets the RBG LED to the chosen color.
********************************************************************************/
void status_led_display_color(const enum LED_COLOR color)
{
	PORTB &= ~((1 << STATUS_LED_R_PIN) | (1 << STATUS_LED_G_PIN) | (1 << STATUS_LED_B_PIN));
	
	switch (color)
	{
		case LED_RED:
		{
			PORTB |= (1 << STATUS_LED_R_PIN);
			break;
		}
		case LED_GREEN:
		{
			PORTB |= (1 << STATUS_LED_G_PIN);
			break;
		}
		case LED_BLUE:
		{
			PORTB |= (1 << STATUS_LED_B_PIN);
			break;
		}
		case LED_ORANGE:
		{
			PORTB |= (1 << STATUS_LED_R_PIN) | (1 << STATUS_LED_G_PIN);
			break;
		}
		case LED_PURPLE:
		{
			PORTB |= (1 << STATUS_LED_R_PIN) | (1 << STATUS_LED_B_PIN) | (1 << STATUS_LED_B_PIN);
			break;
		}
		default:
		{
			break;
		}
	}

	return;	
}