/********************************************************************************
* main.c:
********************************************************************************/

/* Include directives */
#include "global_header.h"

/* Global variable definitions */
volatile double left_distance = 0;
volatile double center_distance = 0;
volatile double right_distance = 0;


int main(void)
{
	setup();

    while (true) 
    {
		left_distance = ir_sensor_get_distance(adc_read_voltage(SENSOR_LEFT_PIN)) - 3;
		center_distance = ir_sensor_get_distance(adc_read_voltage(SENSOR_CENTER_PIN)) - 2;
		right_distance = ir_sensor_get_distance(adc_read_voltage(SENSOR_RIGHT_PIN)) - 2;
		
		serial_print_string("Left: ");
		serial_print_double(left_distance);
		serial_print_char('\t');
		
		serial_print_string("Center: ");
		serial_print_double(center_distance);
		serial_print_char('\t');
		
		serial_print_string("Right: ");
		serial_print_double(right_distance);
		serial_print_new_line();
		
    }
	
	return 0;
}

