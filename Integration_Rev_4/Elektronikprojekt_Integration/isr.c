/********************************************************************************
* isr.c: Contains the various Interrupt Service Routines used in the program.
********************************************************************************/

/* Include directives */
#include "global_header.h"

/* Interrupt service routines */

/********************************************************************************
* INT0_vect: Trigger condition: Any logical change on START_SIGNAL_PIN (PORTD2).
*            Status of START_SIGNAL_PIN is read, if the bit is set the start 
*            module has been issued a start-command. 
*            If the bit is cleared a stop-signal has been sent.
********************************************************************************/
ISR (INT0_vect)
{
	if ((PIND & (1 << START_SIGNAL_PIN)) != 0)
	{
		fsm_set_state(STATE_DRIVE);
	}
	else 
	{
		fsm_set_state(STATE_STANDBY);
	}
	
	return;
}

/********************************************************************************
* TIMER0_OVF_vect: Trigger condition: Executed every 255 us.
*                  Controls accelaration and deceleration of the motor by
*                  adjusting the motor speed towards the current target speed
*                  every 5 ms.
********************************************************************************/
ISR (TIMER0_OVF_vect)
{
	static volatile uint8_t speed_adjustment_counter = 0;
	
	if (++speed_adjustment_counter >= 20)
	{
		if (motor_controller_get_target_speed() > motor_controller_get_current_speed())
		{
			motor_controller_set_speed(motor_controller_get_current_speed() + 1);
		}
		else if (motor_controller_get_target_speed() < motor_controller_get_current_speed())
		{
			motor_controller_set_speed(motor_controller_get_current_speed() - 1);
		}
		else
		{
			
		}
		
		speed_adjustment_counter = 0;
	}
	
	return;
}

/********************************************************************************
* TIMER1_OVF_vect: Trigger condition: Executed every 20 ms.
*                  Enables the motor after 1 second has passed if the motor is
*                  stopped.
********************************************************************************/
ISR (TIMER1_OVF_vect)
{	
	static volatile uint8_t motor_stop_counter = 0;
	
	if (motor_controller_get_motor_stopped() && fsm_get_current_state() == STATE_STANDBY)
	{
		return;
	}
	else if (motor_controller_get_motor_stopped())
	{
		if (++motor_stop_counter >= 50)
		{
			motor_controller_set_motor_stopped(false);
			motor_stop_counter = 0;
		}
		else
		{
			return;
		}
	}
	else return;
}

/********************************************************************************
* TIMER2_COMPA_vect: Trigger condition: Executed every 1 ms. Every 10 ms data
*                    from the sensors is gathered and control signals for
*                    servo and motor is calculated.
********************************************************************************/
ISR (TIMER2_COMPA_vect)
{
	static volatile uint8_t systick_counter = 0;
	
	if (++systick_counter >= 10)
	{
		// Get sensor data.
		ir_sensor_read_all();
		
		// Calculate regulated control signals.
		pid_regulate(&servo_pid, ir_sensor_get_servo_pid_input(ir_sensor_get_distance_reading(INDEX_SENSOR_LEFT), ir_sensor_get_distance_reading(INDEX_SENSOR_RIGHT)));
		//servo_calculate_speed_comp_factor();
		motor_controller_regulate(ir_sensor_get_distance_reading(INDEX_SENSOR_CENTER));
		
		systick_counter = 0;
	}
	
	return;
}