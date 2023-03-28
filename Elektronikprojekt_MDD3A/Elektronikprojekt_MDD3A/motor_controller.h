/********************************************************************************
* motor_controller.h:
*********************************************************************************/
#ifndef MOTOR_CONTROLLER_H_
#define MOTOR_CONTROLLER_H_

/* Include directives */
#include "gpio.h"

/* Enumerations */
enum motor_direction
{
	MOTOR_DIRECTION_FORWARD,
	MOTOR_DIRECTION_BACKWARD
};

/* Static variables */
//static volatile uint8_t current_motor_pwm_value = 0;
//static volatile uint8_t target_motor_pwm_value = 0;
static volatile uint8_t current_M1A_pwm_value = 0;
static volatile uint8_t target_M1A_pwm_value = 0;
static volatile uint8_t current_M1B_pwm_value = 0;
static volatile uint8_t target_M1B_pwm_value = 0;
static enum motor_direction current_direction = MOTOR_DIRECTION_FORWARD;

/* External function declarations */
/********************************************************************************
* motor_controller_set_pwm_value:
*********************************************************************************/
void motor_controller_set_pwm_value(void);

/********************************************************************************
* motor_controller_set_speed:
*********************************************************************************/
void motor_controller_set_speed(const uint8_t speed);

/********************************************************************************
* motor_controller_set_direction:
*********************************************************************************/
void motor_controller_set_direction(const enum motor_direction new_direction);



#endif /* MOTOR_CONTROLLER_H_ */