/********************************************************************************
* status_led.h: Contains enumerations and function declarations related
*				to using a RGB LED.
********************************************************************************/

#ifndef STATUS_LED_H_
#define STATUS_LED_H_

/* Include directives */
#include "global_header.h"

/* Enumerations */
enum LED_COLOR
{
	LED_RED,
	LED_GREEN,
	LED_BLUE,
	LED_ORANGE,
	LED_PURPLE
};

/* External function declarations */
void status_led_display_color(const enum LED_COLOR color);

#endif /* STATUS_LED_H_ */