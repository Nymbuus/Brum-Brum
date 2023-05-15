/********************************************************************************
* gpio.h: Contains include directives for various libraries and function
*         declarations for the functions setup, delay_ms and delay_us. 
*         Also contains hardware specific macro definitions for the
*         various GPIO-pins of the MCU.
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

#define SERVO_CONTROL_PIN PORTB1

#define MOTOR_PWM_PIN PORTD6
#define MOTOR_DIRECTION_PIN PORTD4

#define STATUS_LED_R_PIN PORTB2
#define STATUS_LED_G_PIN PORTB3
#define STATUS_LED_B_PIN PORTB4

#define START_SIGNAL_PIN PORTD2

/* External function declarations */
void setup(void);
void delay_ms(const uint16_t delay_time_ms);
void delay_us(const uint16_t delay_time_us);

#endif /* GPIO_H_ */