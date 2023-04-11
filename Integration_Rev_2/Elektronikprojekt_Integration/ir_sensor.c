/********************************************************************************
* adc.c: Contains function definitions relevant to analog IR distance 
*		 sensor GP2Y0A21YK.
********************************************************************************/

/* Include directives */
#include "ir_sensor.h"

/********************************************************************************
* ir_sensor_get_servo_pid_input: Calculates the input to be sent to the PID-
*								 regulator based on readings from two
*								 side-facing distance sensors.
********************************************************************************/
double ir_sensor_get_servo_pid_input(const uint8_t left_pin, const uint8_t right_pin)
{
	const double input_difference = ir_sensor_get_input_difference(left_pin, right_pin);
	const double scaled_input = ((input_difference + DISTANCE_MAX) / (2 * DISTANCE_MAX));
	
	return (scaled_input * 180);
}

/********************************************************************************
* ir_sensor_get_input_difference: Calculates the difference in cm between 
*							      two side-facing distance sensors.
********************************************************************************/
double ir_sensor_get_input_difference(const uint8_t left_pin, const uint8_t right_pin)
{	
	const double left_val = ir_sensor_get_distance_cm(left_pin);
	const double right_val = ir_sensor_get_distance_cm(right_pin);
	
	return (left_val - right_val);
}

/********************************************************************************
* ir_sensor_check_distance: Matches a given distance in cm against defined
*							minimum and maximum values. Corrects the value
*							to the closest boundary if it is out of range.
********************************************************************************/
double ir_sensor_check_distance(double val)
{
	if (val > DISTANCE_MAX)
	{
		val = (double)DISTANCE_MAX;
		return val;
	}
	else if (val < DISTANCE_MIN)
	{
		val = (double)DISTANCE_MIN;
		return val;
	}
	else return val;
}

/********************************************************************************
* ir_sensor_get_distance_cm: Measures the distance in cm to the closest
*							 detected object by the chosen sensor.
********************************************************************************/
double ir_sensor_get_distance_cm(uint8_t pin)
{
	double distance_cm = 29.988 * pow(adc_read_voltage(pin), -1.173);
	distance_cm = ir_sensor_check_distance(distance_cm);

	return distance_cm;
}


