/********************************************************************************
* pid.c:
********************************************************************************/

/* Include directives */
#include "pid.h"

/* External function definitions */

/********************************************************************************
* pid_init:
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
* pid_check_output:
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
* pid_regulate:
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