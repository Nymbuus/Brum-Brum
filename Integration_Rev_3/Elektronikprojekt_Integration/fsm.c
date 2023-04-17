/********************************************************************************
* fsm.c: Contains function definitions and static variables related to the
*        implementation of a finite state machine.
********************************************************************************/

/* Include directives */
#include "fsm.h"

/* Static variables */
static enum STATE current_state = STATE_STANDBY;

/* External function definitions */

/********************************************************************************
* fsm_run: Determines the actions to be taken based on the current state.
********************************************************************************/
void fsm_run(void)
{
	switch (current_state)
	{
		case STATE_STANDBY:
		{
			// Actions to be taken during the current state.
			break;
		}
		case STATE_DRIVE:
		{
			// Actions to be taken during the current state.
			break;
		}
		case STATE_STOP:
		{
			// Actions to be taken during the current state.
			break;
		}
		case STATE_REVERSE:
		{
			// Actions to be taken during the current state.
			break;
		}
		default:
		{
			break;
		}
	}
	
	return;
}

/********************************************************************************
* fsm_set_state: Sets the state machine to a new state and takes actions
*                based on which states the transition is between.
********************************************************************************/
void fsm_set_state(const enum STATE new_state)
{
	switch (current_state)
	{
		case STATE_STANDBY:
		{
			if (new_state == STATE_DRIVE)
			{
				// Actions to be taken when transitioning from this state.
				break;
			}
			else
			{
				break;
			}
		}
		case STATE_DRIVE:
		{
			if (new_state == STATE_STOP)
			{
				// Actions to be taken when transitioning from this state.
				break;
			}
			else if (new_state == STATE_STANDBY)
			{
				// Actions to be taken when transitioning from this state.
				break;
			}
			else
			{
				break;
			}
		}
		case STATE_STOP:
		{
			if (new_state == STATE_DRIVE)
			{
				// Actions to be taken when transitioning from this state.
				break;
			}
			else if (new_state == STATE_REVERSE)
			{
				// Actions to be taken when transitioning from this state.
				break;
			}
			else if (new_state == STATE_STANDBY)
			{
				// Actions to be taken when transitioning from this state.
				break;
			}
			else
			{
				break;
			}
		}
		case STATE_REVERSE:
		{
			if (new_state == STATE_STOP)
			{
				// Actions to be taken when transitioning from this state.
				break;
			}
			else if (new_state == STATE_STANDBY)
			{
				// Actions to be taken when transitioning from this state.
				break;
			}
			else
			{
				break;
			}
		}
		default:
		{
			break;
		}
	}
	
	current_state = new_state;
	return;	
}
