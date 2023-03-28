#include "ir_sensor.h"

double ir_sensor_get_distance(const double voltage)
{
	
	double distance_cm = 29.988 * pow(voltage, -1.12);
	if (distance_cm >= DISTANCE_MAX) distance_cm = DISTANCE_MAX;
	
	return distance_cm;
}