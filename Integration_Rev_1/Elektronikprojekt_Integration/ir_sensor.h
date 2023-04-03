/********************************************************************************
* ir_sensor.h: Contains macro definitions and function declarations relevant to
*			   analog IR distance sensor GP2Y0A21YK.
********************************************************************************/

#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

/* Include directives */
#include "global_header.h"

/* Macro definitions */
#define DISTANCE_MAX 50
#define DISTANCE_MIN 10

/* External function declarations */
double ir_sensor_get_servo_pid_input(const uint8_t left_pin, const uint8_t right_pin);
double ir_sensor_get_distance_cm(uint8_t pin);
double ir_sensor_check_distance(double val);
double ir_sensor_get_input_difference(const uint8_t left_pin, const uint8_t right_pin);

#endif /* IR_SENSOR_H_ */