/********************************************************************************
* motor_controller.c: Contains static variables and function definitions
*                     related to control of a DC-motor using the 
*                     motor controller MDD3A.
*********************************************************************************/

/* Include directives */
#include "motor_controller.h"

/* Static variables */
static enum motor_direction current_direction = MOTOR_DIRECTION_FORWARD;
static uint8_t current_speed = 0;
static bool motor_stopped = true;

/* External Function Definitions */

/********************************************************************************
* motor_controller_set_speed: Sets the duty cycle of the PWM-signal controlling
*                             the speed of the motor.
*********************************************************************************/
void motor_controller_set_speed(uint8_t motor_speed)
{
	if (current_direction == MOTOR_DIRECTION_FORWARD)
	{
		OCR0A = motor_controller_get_pwm_value(motor_speed);
	}
	else if (current_direction == MOTOR_DIRECTION_BACKWARD)
	{
		OCR0B = motor_controller_get_pwm_value(motor_speed);
	}

	current_speed = motor_speed;
	if (motor_speed > 0) motor_stopped = false;
	
	return;
}

/********************************************************************************
* motor_controller_set_direction: Sets the direction of the motor.
*********************************************************************************/
void motor_controller_set_direction(const enum motor_direction new_direction)
{
	if (new_direction == current_direction) return;

	motor_controller_stop();
	current_direction = new_direction;
	
	return;
}

/********************************************************************************
* motor_controller_stop: Stops the motor immediately.
*********************************************************************************/
void motor_controller_stop(void)
{
	motor_controller_set_speed(0);
	motor_stopped = true;
	
	return;
}

/********************************************************************************
* motor_controller_check_speed: Compares a given duty cycle against defined
*                               minimum and maximum duty cycles.
*                               Adjusts values out of the range given by these
*                               constraints back into the allowed range.
*********************************************************************************/
uint8_t motor_controller_check_speed(uint8_t speed)
{
	if (speed > MOTOR_SPEED_MAX)
	{
		speed = MOTOR_SPEED_MAX;
	}
	else if (speed < MOTOR_SPEED_MIN && speed > 0)
	{
		speed = MOTOR_SPEED_MIN;
	}

	return speed;
}

/********************************************************************************
* motor_controller_run: Sets the speed of the motor based on the distance to
*                       the nearest detected object by the front-facing sensor.
*********************************************************************************/
void motor_controller_run(const double center_distance_cm)
{
	if (center_distance_cm < DISTANCE_STOP_THRESHOLD)
	{
		motor_controller_stop();
	}
	else
	{	
		double speed_rescaled = (center_distance_cm - DISTANCE_STOP_THRESHOLD) / (DISTANCE_MAX - DISTANCE_STOP_THRESHOLD);
		uint8_t new_speed = (uint8_t)(MOTOR_SPEED_MAX * speed_rescaled);
		new_speed = motor_controller_check_speed(new_speed);
		motor_controller_set_speed(new_speed);
	}
	
	return;
}

/********************************************************************************
* motor_controller_get_motor_direction: Returns the current motor direction.
*********************************************************************************/
enum motor_direction motor_controller_get_motor_direction(void)
{
	return current_direction;
}

/********************************************************************************
* motor_controller_get_current_speed: Returns the current speed.
*********************************************************************************/
uint8_t motor_controller_get_current_speed(void)
{
	return current_speed;
}

/********************************************************************************
* motor_controller_get_motor_stopped: Returns true if the motor is stopped, 
*                                     returns false otherwise.
*********************************************************************************/
bool motor_controller_get_motor_stopped(void)
{
	return motor_stopped;
}

