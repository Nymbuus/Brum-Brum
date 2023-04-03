/********************************************************************************
* pid.h: 
********************************************************************************/ 

#ifndef PID_REGULATOR_H_
#define PID_REGULATOR_H_

/* Include directives */
#include "global_header.h"

/* Structs */
struct pid
{
	double target;
	double output;
	double input;
	double output_min;
	double output_max;
	double last_error;
	double integrate;
	double derivate;
	double kp;
	double ki;
	double kd;
};

/* External function declarations */

/********************************************************************************
* pid_init:
********************************************************************************/
void pid_init(struct pid* self, const double target,
			  const double output_min, const double output_max,
			  const double kp, const double ki, const double kd);
			  
/********************************************************************************
* pid_check_output:
********************************************************************************/
void pid_check_output(struct pid* self);

/********************************************************************************
* pid_regulate:
********************************************************************************/
void pid_regulate(struct pid* self, const double pid_input);

#endif /* PID_REGULATOR_H_ */