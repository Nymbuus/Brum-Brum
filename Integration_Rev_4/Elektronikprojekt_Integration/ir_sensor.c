/********************************************************************************
* adc.c: Contains static variables and function definitions relevant to 
*        analog IR distance sensor GP2Y0A21YK.
********************************************************************************/

/* Include directives */
#include "ir_sensor.h"

/* Static variables */
static double distance_readings[NUMBER_OF_SENSORS] = {0.0, 0.0, 0.0};
//static uint8_t previous_left_values[50];
//static uint8_t previous_right_values[50];

/********************************************************************************
* ir_sensor_get_servo_pid_input: Calculates the input to be sent to the PID-
*                                regulator based on readings from two
*                                side-facing distance sensors.
********************************************************************************/
double ir_sensor_get_servo_pid_input(const double val_1, const double val_2)
{
	const double input_difference = ir_sensor_get_input_difference(val_1, val_2);
	const double scaled_input = ((input_difference + DISTANCE_MAX) / (2 * DISTANCE_MAX));
	
	return (scaled_input * 180);
}

/********************************************************************************
* ir_sensor_get_input_difference: Calculates the difference in cm between 
*                                 two distance sensors.
********************************************************************************/
double ir_sensor_get_input_difference(const double val_1, const double val_2)
{		
	return (val_1 - val_2);
}

/********************************************************************************
* ir_sensor_check_distance: Matches a given distance in cm against defined
*                           minimum and maximum values. Corrects the value
*                           to the closest boundary if it is out of range.
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
*                            detected object by the chosen sensor.
********************************************************************************/
double ir_sensor_get_distance_cm(uint8_t pin)
{
	double distance_cm = 29.988 * pow(adc_read_voltage(pin), -1.173);
	distance_cm = ir_sensor_check_distance(distance_cm);

	return distance_cm;
}

/********************************************************************************
* ir_sensor_read_all: Gets distance readings from all the sensors
*                     and stores the data in the static array distance_readings.
********************************************************************************/
void ir_sensor_read_all(void)
{
	//static volatile uint8_t i = 0;
	
	distance_readings[INDEX_SENSOR_LEFT] = ir_sensor_get_distance_cm(SENSOR_LEFT_PIN);
	distance_readings[INDEX_SENSOR_CENTER] = ir_sensor_get_distance_cm(SENSOR_CENTER_PIN);
	distance_readings[INDEX_SENSOR_RIGHT] = ir_sensor_get_distance_cm(SENSOR_RIGHT_PIN);
	/*
	if (i < 50)
	{
		previous_left_values[i] = (uint8_t)distance_readings[INDEX_SENSOR_LEFT];
		previous_right_values[i] = (uint8_t)distance_readings[INDEX_SENSOR_RIGHT];
		i++;
	}
	else
	{
		i = 0;
		previous_left_values[i] = (uint8_t)distance_readings[INDEX_SENSOR_LEFT];
		previous_right_values[i] = (uint8_t)distance_readings[INDEX_SENSOR_RIGHT];
	}
	*/
	return;
}

/********************************************************************************
* ir_sensor_get_distance_reading: Returns the measured distance stored in the
*                                 static array distance_readings at the
*                                 given index.
********************************************************************************/
double ir_sensor_get_distance_reading(const uint8_t index)
{
	return distance_readings[index];
}

/********************************************************************************
* ir_sensor_check_obstacle_cleared: Returns true if no obstacle is detected
*                                   within 25 cm of either side-facing sensor
*                                   and within 35 cm of the front-facing sensor.
********************************************************************************/
bool ir_sensor_check_obstacle_cleared(void)
{
	if (distance_readings[INDEX_SENSOR_LEFT] > OBSTACLE_CLEARED_THRESHOLD && 
		distance_readings[INDEX_SENSOR_CENTER] > OBSTACLE_CLEARED_CENTER_THRESHOLD && 
		distance_readings[INDEX_SENSOR_RIGHT] > OBSTACLE_CLEARED_THRESHOLD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/********************************************************************************
* ir_sensor_check_stop_condition: Evaluates sensor data and returns
*                                 true if an obstacle is detected close to
*                                 either side of the car.
********************************************************************************/
bool ir_sensor_check_stop_condition(void)
{
	if (distance_readings[INDEX_SENSOR_CENTER] <= STOP_THRESHOLD && distance_readings[INDEX_SENSOR_LEFT] <= STOP_THRESHOLD)
	{
		return true;
	}
	else if (distance_readings[INDEX_SENSOR_CENTER] <= STOP_THRESHOLD && distance_readings[INDEX_SENSOR_RIGHT] <= STOP_THRESHOLD)
	{
		return true;
	}
	else
	{
		return false;
	}
}