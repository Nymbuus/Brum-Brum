/********************************************************************************
* servo.c:
********************************************************************************/

/* Include directives */
#include "servo.h"

/* External function definitions */
void servo_set_angle(const uint8_t angle)
{
	uint16_t ocr1a_val = 250 + angle * 1.389;
	OCR1A = ocr1a_val;
	
	return;
}
