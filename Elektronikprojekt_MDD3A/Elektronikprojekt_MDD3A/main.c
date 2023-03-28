/********************************************************************************
* main.c:
*********************************************************************************/

/* Include directives */
#include "gpio.h"
#include "motor_controller.h"

int main(void)
{
    setup();
	
	motor_controller_set_direction(MOTOR_DIRECTION_FORWARD);
	motor_controller_set_speed(100);
	//delay_ms(2000);
	//motor_controller_set_speed(0);
		
	while (true) 
    {

    }
	
	return 0;
}

