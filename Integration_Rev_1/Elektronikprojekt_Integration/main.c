/********************************************************************************
* main.c:
********************************************************************************/

/* Include directives */
#include "global_header.h"

/* Static variables */
static struct pid servo_pid;

/********************************************************************************
* main:
********************************************************************************/
int main(void)
{
	setup();
	pid_init(&servo_pid, SERVO_ANGLE_CENTER, SERVO_ANGLE_MIN, SERVO_ANGLE_MAX, 1, 0.1, 0.01);

	while (true)
	{
		pid_regulate(&servo_pid, ir_sensor_get_servo_pid_input(SENSOR_LEFT_PIN, SENSOR_RIGHT_PIN));
		servo_set_angle((uint8_t)servo_pid.output);
		motor_controller_run(ir_sensor_get_distance_cm(SENSOR_CENTER_PIN));
	}
	
	return 0;
}

