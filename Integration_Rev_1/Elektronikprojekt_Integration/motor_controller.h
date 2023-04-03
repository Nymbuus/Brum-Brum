/********************************************************************************
* motor_controller.h:
*********************************************************************************/
#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_

/* Include directives */
#include "global_header.h"

/* Enumerations */
enum motor_direction
{
	MOTOR_DIRECTION_FORWARD,
	MOTOR_DIRECTION_BACKWARD
};

/* Macro definitions */
#define MOTOR_SPEED_MAX 40
#define MOTOR_SPEED_MIN 20

/* Internal function declarations */
static inline uint8_t motor_controller_get_pwm_value(uint8_t motor_speed);

/* External function declarations */
void motor_controller_set_speed(uint8_t motor_speed);
void motor_controller_set_direction(const enum motor_direction new_direction);
void motor_controller_stop(void);
void motor_controller_run(const double center_distance_cm);
bool motor_controller_check_motor_direction(void);

/* Internal function definitions */

/********************************************************************************
* motor_controller_get_pwm_value: Converts a value in the range 0 - 100 to
*								  a value in the range 0 - 255.
*********************************************************************************/
static inline uint8_t motor_controller_get_pwm_value(uint8_t motor_speed)
{
	return (uint8_t)(motor_speed * 2.55);
}

#endif /* MOTOR_CONTROLLER_H_ */