/********************************************************************************
* motor_controller.c: Contains static variables and function definitions
*                     related to control of a DC-motor using the 
*                     motor controller MD13S.
*********************************************************************************/

/* Include directives */
#include "motor_controller.h"

/* Static variables */
static enum motor_direction current_direction = MOTOR_DIRECTION_FORWARD;
static uint8_t target_speed = 0;
static uint8_t current_speed = 0;
static bool motor_stopped = false;
static uint8_t motor_regulator_output = 0;

/* External Function Definitions */

/********************************************************************************
* motor_controller_set_speed: Sets the duty cycle of the PWM-signal controlling
*                             the speed of the motor.
*********************************************************************************/
void motor_controller_set_speed(uint8_t motor_speed)
{
	if (motor_stopped)
	{
		return;
	}
	else
	{
		OCR0A = motor_controller_get_pwm_value(motor_speed);
		current_speed = motor_speed;
	}
	
	return;
}

/********************************************************************************
* motor_controller_set_target_speed: Sets the target speed to be used in the
*                                    ISR controlling acceleration and
*                                    deceleration of the motor.
*********************************************************************************/
void motor_controller_set_target_speed(const uint8_t target)
{
	target_speed = target;
	
	return;
}

/********************************************************************************
* motor_controller_get_target_speed: Returns the static variable target_speed.
*********************************************************************************/
uint8_t motor_controller_get_target_speed(void)
{
	return target_speed;
}

/********************************************************************************
* motor_controller_set_direction: Sets the direction of the motor.
*********************************************************************************/
void motor_controller_set_direction(const enum motor_direction new_direction)
{
	if (new_direction == MOTOR_DIRECTION_FORWARD)
	{
		PORTD &= ~(1 << MOTOR_DIRECTION_PIN);
	}
	else
	{
		PORTD |= (1 << MOTOR_DIRECTION_PIN);
	}	
	
	current_direction = new_direction;
	return;
}

/********************************************************************************
* motor_controller_stop: Stops the motor immediately.
*********************************************************************************/
void motor_controller_stop(void)
{
	motor_controller_set_target_speed(0);
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
* motor_controller_regulate: Sets the speed of the motor based on the distance to
*                            the nearest detected object by the front-facing
*                            sensor and the current angle of the servo.
*********************************************************************************/
void motor_controller_regulate(const double center_distance_cm)
{	
	uint8_t new_speed = 0;
	
	double speed_rescaled = (center_distance_cm - STOP_THRESHOLD) / (DISTANCE_MAX - STOP_THRESHOLD);
	new_speed = (uint8_t)(MOTOR_SPEED_MAX * speed_rescaled);
	//new_speed = (uint8_t)(new_speed * servo_get_speed_comp_factor());
	new_speed = motor_controller_check_speed(new_speed);
	
	motor_regulator_output = new_speed;
	return;
}

/********************************************************************************
* motor_controller_get_regulator_output: Returns the regulated output calculated
*                                        by the regulating function.
*********************************************************************************/
uint8_t motor_controller_get_regulator_output(void)
{
	return motor_regulator_output;
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

/********************************************************************************
* motor_controller_set_motor_stopped: Function used to enable manipulation of
*                                     the static variable motor_stopped outside
*                                     of motor_controller.c.
*********************************************************************************/
void motor_controller_set_motor_stopped(const bool new_value)
{
	motor_stopped = new_value;
	
	return;
}

