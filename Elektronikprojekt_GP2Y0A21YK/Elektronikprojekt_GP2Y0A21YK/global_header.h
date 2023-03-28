/********************************************************************************
* global_header.h: Header file containing include directives to every 
*				   header file in the project.
********************************************************************************/

#ifndef GLOBAL_HEADER_H_
#define GLOBAL_HEADER_H_

/* Include directives */
#include "gpio.h"
#include "usart.h"
#include "adc.h"
#include "ir_sensor.h"


/* Global variable declarations */
extern volatile double left_distance;
extern volatile double center_distance;
extern volatile double right_distance;
#endif /* GLOBAL_HEADER_H_ */