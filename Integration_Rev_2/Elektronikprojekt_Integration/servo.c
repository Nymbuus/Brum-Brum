/********************************************************************************
* servo.c: Contains static variables and function definitions related to
*		   controlling a servo motor.
********************************************************************************/

/* Include directives */
#include "servo.h"

/* Static variables */
static uint8_t current_angle = 90;

/* External function definitions */

/********************************************************************************
* servo_set_angle: Sets the servo to a given angle and updates the static
*				   variable current_angle with this value.
********************************************************************************/
void servo_set_angle(const uint8_t angle)
{
	uint16_t ocr1a_val = (uint16_t)(250 + ((SERVO_ANGLE_RANGE - angle) * 1.389));
	OCR1A = ocr1a_val;
	current_angle = angle;
	
	return;
}

/********************************************************************************
* servo_get_current_angle: Returns the current angle of the servo motor.
********************************************************************************/
uint8_t servo_get_current_angle(void)
{
	return current_angle;
}
