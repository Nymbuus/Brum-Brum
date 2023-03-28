/********************************************************************************
* gpio.h:
********************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

/* Definition of CPU clock frequency 16 MHz */
#define F_CPU 16000000UL

/* Include directives */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Macro definitions */
#define SENSOR_RIGHT_PIN PORTC0
#define SENSOR_CENTER_PIN PORTC1
#define SENSOR_LEFT_PIN PORTC2

/* External function declarations */
void setup(void);


#endif /* GPIO_H_ */