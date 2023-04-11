/********************************************************************************
* servo.h: Contains macro definitions and function declarations related to
*		   controlling a servo motor.
********************************************************************************/

#ifndef SERVO_H_
#define SERVO_H_

/* Include directives */
#include "global_header.h"

/* Macro definitions */
#define SERVO_CENTER 375
#define SERVO_MAX_LEFT 250
#define SERVO_MAX_RIGHT 500

#define SERVO_ANGLE_MIN 0
#define SERVO_ANGLE_CENTER 90
#define SERVO_ANGLE_MAX 180
#define SERVO_ANGLE_RANGE 180

/* External function declarations */
void servo_set_angle(const uint8_t angle);
uint8_t servo_get_current_angle(void);

#endif /* SERVO_H_ */