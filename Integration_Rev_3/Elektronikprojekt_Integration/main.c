/********************************************************************************
* main.c:
********************************************************************************/

/* Include directives */
#include "global_header.h"

/* Initiation of global variables */
struct pid servo_pid;

/********************************************************************************
* main:
********************************************************************************/
int main(void)
{
	pid_init(&servo_pid, SERVO_ANGLE_CENTER, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX, 1, 0.001, 0.01);
	setup();

	while (true)
	{
		// Some work still remains before this function can handle the operation of the FSM.
		//fsm_run();
		
		// Debugging code for distance sensors.
		/*
		serial_print_string("Left: ");
		serial_print_double(ir_sensor_get_distance_cm(SENSOR_LEFT_PIN));
		serial_print_new_line();
		
		serial_print_string("Center: ");
		serial_print_double(ir_sensor_get_distance_cm(SENSOR_CENTER_PIN));
		serial_print_new_line();
		
		serial_print_string("Right: ");
		serial_print_double(ir_sensor_get_distance_cm(SENSOR_RIGHT_PIN));
		serial_print_new_line();
		delay_ms(1000);
		*/
		
		// Temporary solution for basic control of the car.
		pid_regulate(&servo_pid, ir_sensor_get_servo_pid_input(SENSOR_LEFT_PIN, SENSOR_RIGHT_PIN));
		servo_set_angle((uint8_t)servo_pid.output);
		motor_controller_run(ir_sensor_get_distance_cm(SENSOR_CENTER_PIN));
	}
	
	return 0;
}

