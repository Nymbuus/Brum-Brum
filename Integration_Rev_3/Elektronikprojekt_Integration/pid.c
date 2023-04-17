/********************************************************************************
* pid.c: Contains function definitions related to PID-regulation.
********************************************************************************/

/* Include directives */
#include "pid.h"

/* External function definitions */

/********************************************************************************
* pid_init: Initializes a struct used for PID-regulation.
********************************************************************************/
void pid_init(struct pid* self, const double target, 
			  const double output_min, const double output_max, 
			  const double kp, const double ki, const double kd)
{
	self->target = target;
	self->output_min = output_min;
	self->output_max = output_max;
	self->kp = kp;
	self->ki = ki;
	self->kd = kd;
	
	self->output = 0;
	self->input = 0;
	self->last_error = 0;
	self->integrate = 0;
	self->derivate = 0;
	
	return;
}

/********************************************************************************
* pid_check_output: Compares a given output against defined
*					minimum and maximum values.
*					Adjusts values out of the range given by these
*					constraints back into the allowed range.
********************************************************************************/
void pid_check_output(struct pid* self)
{
	if (self->output > self->output_max)
	{
		self->output = self->output_max;
	}
	else if (self->output < self->output_min)
	{
		self->output = self->output_min;
	}
	
	return;
}

/********************************************************************************
* pid_regulate: Calculates the output of the PID-regulator based on the input
*				and parameters set at initialization of the used struct.
********************************************************************************/
void pid_regulate(struct pid* self, const double pid_input)
{
	const double error = self->target - pid_input;
	self->input = pid_input;
	
	self->derivate = error - self->last_error;
	self->integrate += error;
	self->output = (self->target) + (self->kp * error) + (self->ki * self->integrate) + (self->kd * self->derivate);
	
	pid_check_output(self);
	self->last_error = error;
	
	return;	
}