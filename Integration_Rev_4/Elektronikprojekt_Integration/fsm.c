/********************************************************************************
* fsm.c: Contains function definitions and static variables related to the
*        implementation of a finite state machine.
********************************************************************************/

/* Include directives */
#include "fsm.h"

/* Static variables */
static enum STATE current_state = STATE_STANDBY;

/* External function definitions */

/********************************************************************************
* fsm_run: Determines the actions to be taken based on the current state.
********************************************************************************/
void fsm_run(void)
{
	switch (current_state)
	{
		case STATE_STANDBY:
		{	
			break;
		}
		case STATE_DRIVE:
		{
			if (ir_sensor_check_stop_condition())
			{
				fsm_set_state(STATE_STOP);
			}
			else
			{
				servo_set_angle((uint8_t)servo_pid.output);
				motor_controller_set_target_speed(motor_controller_get_regulator_output());		
			}

			break;
		}
		case STATE_STOP:
		{
			if (!motor_controller_get_motor_stopped() && ir_sensor_check_obstacle_cleared())
			{
				fsm_set_state(STATE_DRIVE);
			}
			else if (!motor_controller_get_motor_stopped() && !ir_sensor_check_obstacle_cleared())
			{
				fsm_set_state(STATE_REVERSE);
			}
			else break;
			
			break;
		}
		case STATE_REVERSE:
		{				
			if (ir_sensor_check_obstacle_cleared())
			{
				fsm_set_state(STATE_STOP);
			}
			else
			{
				motor_controller_set_target_speed(MOTOR_SPEED_MIN);
				servo_set_angle((SERVO_ANGLE_RANGE - (uint8_t)servo_pid.output));		
			}

			break;
		}
		default:
		{
			break;
		}
	}
	
	return;
}

/********************************************************************************
* fsm_set_state: Sets the state machine to a new state and takes actions
*                based on which states the transition is between.
********************************************************************************/
void fsm_set_state(const enum STATE new_state)
{
	switch (current_state)
	{
		case STATE_STANDBY:
		{
			if (new_state == STATE_DRIVE)
			{
				status_led_display_color(LED_GREEN);
				motor_controller_set_direction(MOTOR_DIRECTION_FORWARD);
				current_state = new_state;
				
				break;
			}
			else
			{
				break;
			}
		}
		case STATE_DRIVE:
		{
			if (new_state == STATE_STOP)
			{
				status_led_display_color(LED_RED);
				motor_controller_stop();
				current_state = new_state;
				
				break;
			}
			else if (new_state == STATE_STANDBY)
			{
				status_led_display_color(LED_PURPLE);
				motor_controller_stop();
				asm("CLI");
				current_state = new_state;
				
				break;
			}
			else
			{
				break;
			}
		}
		case STATE_STOP:
		{
			if (new_state == STATE_DRIVE)
			{
				status_led_display_color(LED_GREEN);
				motor_controller_set_direction(MOTOR_DIRECTION_FORWARD);
				current_state = new_state;
				
				break;
			}
			else if (new_state == STATE_REVERSE)
			{
				status_led_display_color(LED_ORANGE);
				motor_controller_set_direction(MOTOR_DIRECTION_BACKWARD);
				current_state = new_state;
				
				break;
			}
			else if (new_state == STATE_STANDBY)
			{
				status_led_display_color(LED_PURPLE);
				motor_controller_stop();
				asm("CLI");
				current_state = new_state;
				
				break;
			}
			else
			{
				break;
			}
		}
		case STATE_REVERSE:
		{
			if (new_state == STATE_STOP)
			{
				status_led_display_color(LED_RED);
				motor_controller_stop();
				current_state = new_state;
				
				break;
			}
			else if (new_state == STATE_STANDBY)
			{
				status_led_display_color(LED_PURPLE);
				motor_controller_stop();
				asm("CLI");
				current_state = new_state;
				
				break;
			}
			else
			{
				break;
			}
		}
		default:
		{
			break;
		}
	}

	return;	
}

/********************************************************************************
* fsm_get_current_state: Returns the current state.
********************************************************************************/
enum STATE fsm_get_current_state(void)
{
	return current_state;	
}