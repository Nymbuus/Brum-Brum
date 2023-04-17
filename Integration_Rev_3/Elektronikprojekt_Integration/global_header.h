/********************************************************************************
* global_header.h: Header file containing include directives to every
*				   header file in the project. Also contains declarations of
*				   variables with a global scope.
********************************************************************************/

#ifndef GLOBAL_HEADER_H_
#define GLOBAL_HEADER_H_

/* Include directives */
#include "gpio.h"
#include "usart.h"
#include "adc.h"
#include "ir_sensor.h"
#include "servo.h"
#include "motor_controller.h"
#include "pid.h"
#include "status_led.h"
#include "fsm.h"

/* Global variable declarations */
extern struct pid servo_pid;

#endif /* GLOBAL_HEADER_H_ */