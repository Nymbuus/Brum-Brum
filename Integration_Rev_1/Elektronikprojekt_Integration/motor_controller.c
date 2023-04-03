/********************************************************************************
* motor_controller.c:
*********************************************************************************/

/* Include directives */
#include "motor_controller.h"

/* Static variables */
static enum motor_direction current_direction = MOTOR_DIRECTION_FORWARD;

/* External Function Definitions */

/********************************************************************************
* motor_controller_set_speed:
*********************************************************************************/
void motor_controller_set_speed(uint8_t motor_speed)
{
	if (motor_speed > MOTOR_SPEED_MAX) motor_speed = MOTOR_SPEED_MAX;
	if (motor_speed < MOTOR_SPEED_MIN && motor_speed > 0) motor_speed = MOTOR_SPEED_MIN;
	
	if (current_direction == MOTOR_DIRECTION_FORWARD)
	{
		OCR0A = motor_controller_get_pwm_value(motor_speed);
	}
	else if (current_direction == MOTOR_DIRECTION_BACKWARD)
	{
		OCR0B = motor_controller_get_pwm_value(motor_speed);
	}

	return;
}

/********************************************************************************
* motor_controller_set_direction:
*********************************************************************************/
void motor_controller_set_direction(const enum motor_direction new_direction)
{
	if (new_direction == current_direction) return;

	motor_controller_stop();
	current_direction = new_direction;
	
	return;
}

/********************************************************************************
* motor_controller_stop:
*********************************************************************************/
void motor_controller_stop(void)
{
	motor_controller_set_speed(0);
	
	return;
}

/********************************************************************************
* motor_controller_run:
*********************************************************************************/
void motor_controller_run(const double center_distance_cm)
{
	if (center_distance_cm < 15) motor_controller_stop();
		
	double speed_rescaled = (center_distance_cm - 15) * (100 / DISTANCE_MAX);
	double speed_percentage = speed_rescaled / 100;
	uint8_t new_speed = (uint8_t)(MOTOR_SPEED_MAX * speed_percentage);
	motor_controller_set_speed(new_speed);
	
	return;
}

/********************************************************************************
* motor_controller_check_motor_direction: Returns the current motor direction
*										  expressed as a boolean value where
*										  true = forwards, false = backwards.
*********************************************************************************/
bool motor_controller_check_motor_direction(void)
{
	if (current_direction == MOTOR_DIRECTION_FORWARD)
	{
		return true;
	}
	else
	{
		return false;
	}
}


