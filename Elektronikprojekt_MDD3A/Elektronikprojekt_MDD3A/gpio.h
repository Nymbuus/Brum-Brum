/********************************************************************************
* gpio.h:
*********************************************************************************/
#ifndef GPIO_H_
#define GPIO_H_

/* Definition of CPU clock frequency */
#define F_CPU 16000000UL

/* Include directives */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <util/delay.h>

/* Macro definitions */
#define M1A PORTD6
#define M1B PORTD5
#define M1A_ENABLE TCCR0A |= (0b10 << COM0A0)
#define M1A_DISABLE TCCR0A &= ~(0b10 << COM0A0)
#define M1B_ENABLE TCCR0A |= (0b10 << COM0B0)
#define M1B_DISABLE TCCR0A &= ~(0b10 << COM0B0)

/* External function declarations */
void setup(void);
void delay_ms(uint16_t const delay_time_ms);
void delay_us(const uint16_t delay_time_us);

#endif /* GPIO_H_ */