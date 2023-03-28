/********************************************************************************
* motor_controller.c:
*********************************************************************************/

/* Include directives */
#include "motor_controller.h"

/* External Function Definitions */
/********************************************************************************
* motor_controller_set_pwm_value:
*********************************************************************************/
void motor_controller_set_pwm_value(void)
{	
	if (current_direction == MOTOR_DIRECTION_FORWARD)
	{
		if (current_M1A_pwm_value < target_M1A_pwm_value)
		{
			current_M1A_pwm_value++;
		}
		else if (current_M1A_pwm_value > target_M1A_pwm_value)
		{
			current_M1A_pwm_value--;
		}
		
		OCR0A = current_M1A_pwm_value;
	}
	else if (current_direction == MOTOR_DIRECTION_BACKWARD)
	{
		if (current_M1B_pwm_value < target_M1B_pwm_value)
		{
			current_M1B_pwm_value++;
		}
		else if (current_M1B_pwm_value > target_M1B_pwm_value)
		{
			current_M1B_pwm_value--;
		}
		
		OCR0B = current_M1B_pwm_value;
	}
	
	return;
}

/********************************************************************************
* motor_controller_set_speed:
*********************************************************************************/
void motor_controller_set_speed(const uint8_t speed)
{
	if (current_M1A_pwm_value != target_M1A_pwm_value || current_M1B_pwm_value != target_M1B_pwm_value) return;
	
	if (current_direction == MOTOR_DIRECTION_FORWARD)
	{
		target_M1A_pwm_value = speed;
	}
	else if (current_direction == MOTOR_DIRECTION_BACKWARD)
	{
		target_M1B_pwm_value = speed;
	}
	
	return;
}

/********************************************************************************
* motor_controller_set_direction:
*********************************************************************************/
void motor_controller_set_direction(const enum motor_direction new_direction)
{
	if (current_M1A_pwm_value > 0 || current_M1B_pwm_value > 0) return;
	
	if (new_direction == MOTOR_DIRECTION_FORWARD)
	{
		M1A_ENABLE;
		M1B_DISABLE;
		PORTD &= ~(1 << M1B);
	}
	else if (new_direction == MOTOR_DIRECTION_BACKWARD)
	{
		M1A_DISABLE;
		M1B_ENABLE;
		PORTD &= ~(1 << M1A);
	}
	current_direction = new_direction;
	
	return;
}