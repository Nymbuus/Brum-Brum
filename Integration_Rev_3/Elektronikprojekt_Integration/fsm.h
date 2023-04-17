/********************************************************************************
* fsm.h: Contains enumerations and function declarations related to the
*        implementation of a finite state machine.
********************************************************************************/

#ifndef FSM_H_
#define FSM_H_

/* Include directives */
#include "global_header.h"

/* Enumerations */
enum STATE
{
	STATE_STANDBY,
	STATE_DRIVE,
	STATE_STOP,
	STATE_REVERSE	
};

/* External function declarations */
void fsm_run(void);
void fsm_set_state(const enum STATE new_state);



#endif /* FSM_H_ */