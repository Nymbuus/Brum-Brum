/********************************************************************************
* ir_sensor.h: Contains macro definitions and function declarations relevant to
*			   analog IR distance sensor GP2Y0A21YK.
********************************************************************************/

#ifndef IR_SENSOR_H_
#define IR_SENSOR_H_

/* Include directives */
#include "global_header.h"

/* Macro definitions */
#define DISTANCE_MAX 70
#define DISTANCE_MIN 7.5
#define STOP_THRESHOLD 10
#define OBSTACLE_CLEARED_THRESHOLD 25
#define OBSTACLE_CLEARED_CENTER_THRESHOLD 35

#define NUMBER_OF_SENSORS 3
#define INDEX_SENSOR_RIGHT 0
#define INDEX_SENSOR_CENTER 1
#define INDEX_SENSOR_LEFT 2

/* External function declarations */
double ir_sensor_get_servo_pid_input(const double val_1, const double val_2);
double ir_sensor_get_distance_cm(uint8_t pin);
double ir_sensor_check_distance(double val);
double ir_sensor_get_input_difference(const double val_1, const double val_2);
void ir_sensor_read_all(void);
double ir_sensor_get_distance_reading(const uint8_t index);
bool ir_sensor_check_obstacle_cleared(void);
bool ir_sensor_check_stop_condition(void);

#endif /* IR_SENSOR_H_ */